#include "check.h"
#include "handle.h"
#include "win32util.h"
#include "whpx.h"

#include <WinHvPlatform.h>
#include <VersionHelpers.h>

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
    const auto version = GetWindowsVersion();
    if (!version.has_value()) // Failed to fetch windows version, this should not happen in any case!
        return false;

    if (version->dwMajorVersion > 10 || version->dwMajorVersion == 10 && version->dwBuildNumber >= 17134)
    {
        // Since Windows 10 1803 (build 17134), Windows Hypervisor Platform API is part of the system.
        // https://learn.microsoft.com/en-us/virtualization/api/hypervisor-platform/hypervisor-platform
        if (!whpx_dispatcher.WHvGetCapability)
            return false;
        
        BOOL bHyperVPresent = false;
        UINT32 uBytesReturned = 0;
        HRESULT hr = whpx_dispatcher.WHvGetCapability(WHvCapabilityCodeHypervisorPresent, &bHyperVPresent, sizeof(bHyperVPresent), &uBytesReturned);
        
        return SUCCEEDED(hr) && uBytesReturned == sizeof(bHyperVPresent) && bHyperVPresent;
    }

    // For older Windows version, we try to detect the Hyper-V status by gathering information from cpuid
    // https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/feature-discovery
    int cpuid[4];

    // CPUID.01h.ECX:31: if set, virtualization present 
    __cpuid(cpuid, 1);
    if (!(cpuid[2] & (1 << 31)))
        return false;

    // On hypervisors conforming to the Microsoft hypervisor CPUID interface,
    // the 0x40000000 and 0x40000001 leaf registers will have the following values.
    __cpuid(cpuid, 0x40000000);
    if (cpuid[0] < 0x40000005) // The maximum input value for hypervisor CPUID information. 
        return false;          // On Microsoft hypervisors, this will be at least 0x40000005.
    if (cpuid[1] != 0x7263694D || cpuid[2] != 0x666F736F || cpuid[3] != 0x76482074) // "Microsoft Hv"
        return false;

    __cpuid(cpuid, 0x40000001);
    if (cpuid[1] != 0x31237648) // EAX contains the hypervisor interface identification signature. "Hv#1"
        return false;           // This determines the semantics of the leaves from 0x40000002 through 0x400000FF.

    // Hypervisor System Identity
    // EAX: Build Number
    // EBX: Bits 31-16: Major Version, Bits 15-0: Minor Version
    __cpuid(cpuid, 0x40000002);
    // On most Hypervisors, such as KVM, VirtualBox and VMWare, these values should be 0
    if (cpuid[0] == cpuid[1] == cpuid[2] == cpuid[3] == 0)
        return false;
    else // On Hyper-V enabled Windows, these values should be the same as Windows's version
    {
        DWORD dwBuildNumber = cpuid[0];
        WORD wMajorVersion = cpuid[1] >> 16;
        WORD wMinorVersion = cpuid[1] & 0xffff;

        if (dwBuildNumber != version->dwBuildNumber || wMajorVersion != version->dwMajorVersion || wMinorVersion != version->dwMinorVersion)
            return false;
    }

    // All checks passed, Hyper-V is enabled on this machine!
    return true;
}
