#pragma once

#include <Windows.h>
#include <WinHvPlatform.h>

#define WHPX_FUNC(func) decltype(&func) func {nullptr}
#define WHPX_FUNC_INIT(func) this->func = reinterpret_cast<decltype(func)>(GetProcAddress(this->hDll, #func)); if (this->func == nullptr) return
#define WHPX_FUNC_UNINIT(func) this->func = nullptr

extern struct whpx_dispatcher_t
{
private:
    HMODULE hDll;
public:

    whpx_dispatcher_t()
    {
        hDll = LoadLibraryA("WinHvPlatform.dll");
        if (!hDll)
            return;
        
        WHPX_FUNC_INIT(WHvGetCapability);
        WHPX_FUNC_INIT(WHvCreatePartition);
        WHPX_FUNC_INIT(WHvSetupPartition);
        WHPX_FUNC_INIT(WHvDeletePartition);
        WHPX_FUNC_INIT(WHvGetPartitionProperty);
        WHPX_FUNC_INIT(WHvSetPartitionProperty);
        WHPX_FUNC_INIT(WHvMapGpaRange);
        WHPX_FUNC_INIT(WHvUnmapGpaRange);
        WHPX_FUNC_INIT(WHvTranslateGva);
        WHPX_FUNC_INIT(WHvQueryGpaRangeDirtyBitmap);
        WHPX_FUNC_INIT(WHvCreateVirtualProcessor);
        WHPX_FUNC_INIT(WHvDeleteVirtualProcessor);
        WHPX_FUNC_INIT(WHvRunVirtualProcessor);
        WHPX_FUNC_INIT(WHvCancelRunVirtualProcessor);
        WHPX_FUNC_INIT(WHvGetVirtualProcessorRegisters);
        WHPX_FUNC_INIT(WHvGetVirtualProcessorXsaveState);
        WHPX_FUNC_INIT(WHvSetVirtualProcessorRegisters);
        WHPX_FUNC_INIT(WHvSetVirtualProcessorXsaveState);
        WHPX_FUNC_INIT(WHvGetVirtualProcessorInterruptControllerState2);
        WHPX_FUNC_INIT(WHvRequestInterrupt);
        WHPX_FUNC_INIT(WHvSetVirtualProcessorInterruptControllerState2);
        WHPX_FUNC_INIT(WHvGetPartitionCounters);
        WHPX_FUNC_INIT(WHvReadGpaRange);
        WHPX_FUNC_INIT(WHvWriteGpaRange);
        WHPX_FUNC_INIT(WHvGetVirtualProcessorCounters);
    }

    ~whpx_dispatcher_t()
    {
        WHPX_FUNC_UNINIT(WHvGetCapability);
        WHPX_FUNC_UNINIT(WHvCreatePartition);
        WHPX_FUNC_UNINIT(WHvSetupPartition);
        WHPX_FUNC_UNINIT(WHvDeletePartition);
        WHPX_FUNC_UNINIT(WHvGetPartitionProperty);
        WHPX_FUNC_UNINIT(WHvSetPartitionProperty);
        WHPX_FUNC_UNINIT(WHvMapGpaRange);
        WHPX_FUNC_UNINIT(WHvUnmapGpaRange);
        WHPX_FUNC_UNINIT(WHvTranslateGva);
        WHPX_FUNC_UNINIT(WHvQueryGpaRangeDirtyBitmap);
        WHPX_FUNC_UNINIT(WHvCreateVirtualProcessor);
        WHPX_FUNC_UNINIT(WHvDeleteVirtualProcessor);
        WHPX_FUNC_UNINIT(WHvRunVirtualProcessor);
        WHPX_FUNC_UNINIT(WHvCancelRunVirtualProcessor);
        WHPX_FUNC_UNINIT(WHvGetVirtualProcessorRegisters);
        WHPX_FUNC_UNINIT(WHvGetVirtualProcessorXsaveState);
        WHPX_FUNC_UNINIT(WHvSetVirtualProcessorRegisters);
        WHPX_FUNC_UNINIT(WHvSetVirtualProcessorXsaveState);
        WHPX_FUNC_UNINIT(WHvGetVirtualProcessorInterruptControllerState2);
        WHPX_FUNC_UNINIT(WHvRequestInterrupt);
        WHPX_FUNC_UNINIT(WHvSetVirtualProcessorInterruptControllerState2);
        WHPX_FUNC_UNINIT(WHvGetPartitionCounters);
        WHPX_FUNC_UNINIT(WHvReadGpaRange);
        WHPX_FUNC_UNINIT(WHvWriteGpaRange);
        WHPX_FUNC_UNINIT(WHvGetVirtualProcessorCounters);
    }

    WHPX_FUNC(WHvGetCapability);
    WHPX_FUNC(WHvCreatePartition);
    WHPX_FUNC(WHvSetupPartition);
    WHPX_FUNC(WHvDeletePartition);
    WHPX_FUNC(WHvGetPartitionProperty);
    WHPX_FUNC(WHvSetPartitionProperty);
    WHPX_FUNC(WHvMapGpaRange);
    WHPX_FUNC(WHvUnmapGpaRange);
    WHPX_FUNC(WHvTranslateGva);
    WHPX_FUNC(WHvQueryGpaRangeDirtyBitmap);
    WHPX_FUNC(WHvCreateVirtualProcessor);
    WHPX_FUNC(WHvDeleteVirtualProcessor);
    WHPX_FUNC(WHvRunVirtualProcessor);
    WHPX_FUNC(WHvCancelRunVirtualProcessor);
    WHPX_FUNC(WHvGetVirtualProcessorRegisters);
    WHPX_FUNC(WHvGetVirtualProcessorXsaveState);
    WHPX_FUNC(WHvSetVirtualProcessorRegisters);
    WHPX_FUNC(WHvSetVirtualProcessorXsaveState);
    WHPX_FUNC(WHvGetVirtualProcessorInterruptControllerState2);
    WHPX_FUNC(WHvRequestInterrupt);
    WHPX_FUNC(WHvSetVirtualProcessorInterruptControllerState2);
    WHPX_FUNC(WHvGetPartitionCounters);
    WHPX_FUNC(WHvReadGpaRange);
    WHPX_FUNC(WHvWriteGpaRange);
    WHPX_FUNC(WHvGetVirtualProcessorCounters);
} whpx_dispatcher;

#undef WHPX_FUNC
