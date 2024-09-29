#include "check.h"
#include "handle.h"
#include "whpx.h"

#include <WinHvPlatform.h>

#include <intrin.h>

CpuVendor GetCpuVendor()
{
    int cpuid[4];
    __cpuid(cpuid, 0);
    if (cpuid[1] == 0x756e6547 && cpuid[2] == 0x6c65746e && cpuid[3] == 0x49656e69)
        return CpuVendor::GenuineIntel;
    else if (cpuid[1] == 0x68747541 && cpuid[2] == 0x444d4163 && cpuid[3] == 0x69746e65)
        return CpuVendor::AuthenticAMD;
    else
        return CpuVendor::Unknown;
}

bool IsVtEnabled()
{
    int cpuid[4];
    switch (GetCpuVendor())
    {
    case CpuVendor::GenuineIntel:
        __cpuid(cpuid, 1);
        return cpuid[2] & (1 << 5); // CPUID.01h.ECX:5: VMX
    case CpuVendor::AuthenticAMD:
        __cpuid(cpuid, 0x80000001);
        return cpuid[2] & (1 << 2); // CPUID.080000001h.ECX:2: SVM
    default:
        return false;
    }
}

bool IsHyperVEnabled()
{
    do {
        // Since Windows 10 1803 (build 17134), Windows Hypervisor Platform API is part of the system.
        // https://learn.microsoft.com/en-us/virtualization/api/hypervisor-platform/hypervisor-platform
        // We will try to use the WHPX API if possible
        if (!whpx_dispatcher.WHvGetCapability) {
            break;
        }

        BOOL bHyperVPresent = false;
        UINT32 uBytesReturned = 0;
        HRESULT hr = whpx_dispatcher.WHvGetCapability(WHvCapabilityCodeHypervisorPresent, &bHyperVPresent, sizeof(bHyperVPresent),
            &uBytesReturned);
        bool result = SUCCEEDED(hr) && uBytesReturned == sizeof(bHyperVPresent) && bHyperVPresent;
        return result;
    } while (false);

    // For older Windows version, we try to detect the Hyper-V status by gathering information from cpuid
    // https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/feature-discovery

    // The following checks is mostly reverse-engineered from WinHvPlatform.dll WHvGetCapability
    int cpuid[4];

    // CPUID.01h.ECX:31: if set, virtualization present
    __cpuid(cpuid, 1);
    if (!(cpuid[2] & (1 << 31))) {
        return false;
    }

    // Hypervisor CPUID Leaf Range
    __cpuid(cpuid, 0x40000000);
    const int hv_leaf_max = cpuid[0];
    if (hv_leaf_max < 0x40000005) {  // On Microsoft hypervisors, this will be at least 0x40000005.
        return false;
    }
    if (cpuid[1] != 0x7263694D || cpuid[2] != 0x666F736F || cpuid[3] != 0x76482074) {  // "Microsoft Hv"
        return false;
    }

    // Hypervisor Vendor-Neutral Interface Identification
    __cpuid(cpuid, 0x40000001);
    if (cpuid[0] != 0x31237648) {  // EAX contains the hypervisor interface identification signature. "Hv#1"
        return false;                // This determines the semantics of the leaves from 0x40000002 through 0x400000FF.
    }

    // Hypervisor Feature Identification - EBX Bit 11: HV_PARTITION_PRIVILEGE_MASK::CpuManagement
    __cpuid(cpuid, 0x40000003);
    if (!(cpuid[1] & (1 << 11))) {
        return false;
    }

    // Implementation Hardware Features - EAX Bit 17: Support for Unrestricted Guest is present.
    if (hv_leaf_max >= 0x40000006) {
        __cpuid(cpuid, 0x40000006);
        if (!(cpuid[0] & (1 << 17))) {
            return false;
        }
    }

    return true;
}
