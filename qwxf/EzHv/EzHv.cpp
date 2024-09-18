#include "handle.h"
#include "check.h"
#include "win32util.h"
#include "whpx.h"
#include "EzHvImpl.h"

#include <Windows.h>
#include <WinHvPlatform.h>
#include <VersionHelpers.h>

#include <cstdlib>
#include <print>
#include <array>

#include "hv_code.h"

// flag{S1mple_W1nd0Ws_Hyper5is0r!}

consteval auto get_code()
{
    std::array<unsigned char, ARRAYSIZE(code)> encrypted_code;
    for (size_t i = 0; i < encrypted_code.size(); ++i)
        encrypted_code[i] = code[i] ^ 0xCC;
    return encrypted_code;
};
 
int main()
{
    if (whpx_dispatcher.WHvGetVirtualProcessorCounters == nullptr)
    {
        std::println("Failed to retrieve whpx interfaces!");
        return 1;
    }

    if (!IsWindows8OrGreater())
    {
        std::println("This program requires Windows 8 or later!");
        return 1;
    }

    if (!IsHyperVEnabled())
    {
        std::println("This program requires HyperV to run!");
        return 1;
    }

    HRESULT hr;
    WHV_PARTITION_HANDLE hPartition;
    hr = whpx_dispatcher.WHvCreatePartition(&hPartition);
    if (FAILED(hr))
    {
        std::println("WHvCreatePartition failed: 0x{:08X}", hr);
        return 1;
    }

    WHV_PARTITION_PROPERTY Property;
    ZeroMemory(&Property, sizeof(Property));
    Property.ProcessorCount = 1;
    hr = whpx_dispatcher.WHvSetPartitionProperty(hPartition, WHvPartitionPropertyCodeProcessorCount, &Property, sizeof(Property));
    if (FAILED(hr))
    {
        std::println("WHvSetPartitionProperty/WHvPartitionPropertyCodeProcessorCount failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        return 1;
    }

    ZeroMemory(&Property, sizeof(Property));
    Property.ExtendedVmExits.X64CpuidExit = true;
    hr = whpx_dispatcher.WHvSetPartitionProperty(hPartition, WHvPartitionPropertyCodeExtendedVmExits, &Property, sizeof(Property));
    if (FAILED(hr))
    {
        std::println("WHvSetPartitionProperty/WHvPartitionPropertyCodeExtendedVmExits failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        return 1;
    }

    hr = whpx_dispatcher.WHvSetupPartition(hPartition);
    if (FAILED(hr))
    {
        std::println("WHvSetupPartition failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        return 1;
    }

    hr = whpx_dispatcher.WHvCreateVirtualProcessor(hPartition, 0, 0);
    if (FAILED(hr))
    {
        std::println("WHvCreateVirtualProcessor failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        return 1;
    }

    CSMEMORY = VirtualAlloc(nullptr, kMemorySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (CSMEMORY == nullptr)
    {
        std::println("VirtualAlloc failed: 0x{:08X}", GetLastError());
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        return 1;
    }

    std::memset(CSMEMORY, 0xF4, kMemorySize); // HALT
    
    auto data = get_code();
    for (auto& x : data)
        x ^= 0xCC;
    std::memcpy(CSMEMORY, data.data(), data.size());

    hr = whpx_dispatcher.WHvMapGpaRange(hPartition, CSMEMORY, kMemoryOffset, kMemorySize, WHvMapGpaRangeFlagRead | WHvMapGpaRangeFlagWrite | WHvMapGpaRangeFlagExecute);
    if (FAILED(hr))
    {
        std::println("WHvMapGpaRange failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        return 1;
    }

    WHV_REGISTER_NAME rName;
    WHV_REGISTER_VALUE rValue;

    rName = WHvX64RegisterCs;
    ZeroMemory(&rValue, sizeof(rValue));
    rValue.Segment.Base = 0x00000000;
    rValue.Segment.Limit = 0x0000FFFF;
    rValue.Segment.Selector = 0x0000;
    rValue.Segment.Attributes = 0x009B;
    hr = whpx_dispatcher.WHvSetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvSetVirtualProcessorRegisters/WHvX64RegisterCs failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        return 1;
    }

    EzHvSetRip(hPartition, kMemoryOffset);

    bool bIsRunning = true;
    do
    {
        WHV_RUN_VP_EXIT_CONTEXT ctx;
        ZeroMemory(&ctx, sizeof(ctx));
        hr = whpx_dispatcher.WHvRunVirtualProcessor(hPartition, 0, &ctx, sizeof(ctx));
        if (FAILED(hr))
        {
            std::println("WHvRunVirtualProcessor failed: 0x{:08X}", hr);
            whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
            whpx_dispatcher.WHvDeletePartition(hPartition);
            return 1;
        }

        bIsRunning = EzHvHandleHvExit(hPartition, ctx);
    } while (bIsRunning);

    return 0;
}