#pragma once

#include <Windows.h>
#include <WinHvPlatform.h>

extern void* CSMEMORY;
constexpr size_t kMemorySize = 0x00400000;      // 4MB
constexpr size_t kMemoryOffset = 0x00001000;

enum class IOPortWriteCommand : UINT16
{
    PUTCHAR = 11451,
    READROM = 19198,
    GETCHAR = 0x410,
    HEXDBG = 0xdead,
    VERIFY = 0xbeef,
};

enum class CpuidCommand : UINT16
{
    GETRC4KEY = 0x0123,
    READSTRING = 0x4567,
    FORMATCHECK = 0x89ab,
    RC4EXTRAXOR = 0xcdef,
};

UINT64 EzHvGetRip(WHV_PARTITION_HANDLE hPartition);
void EzHvSetRip(WHV_PARTITION_HANDLE hPartition, UINT64 rip);
UINT64 EzHvGetRax(WHV_PARTITION_HANDLE hPartition);
void EzHvSetRax(WHV_PARTITION_HANDLE hPartition, UINT64 rax);
UINT64 EzHvGetRbx(WHV_PARTITION_HANDLE hPartition);
void EzHvSetRbx(WHV_PARTITION_HANDLE hPartition, UINT64 rbx);
UINT64 EzHvGetRcx(WHV_PARTITION_HANDLE hPartition);
void EzHvSetRcx(WHV_PARTITION_HANDLE hPartition, UINT64 rcx);
UINT64 EzHvGetRdx(WHV_PARTITION_HANDLE hPartition);
void EzHvSetRdx(WHV_PARTITION_HANDLE hPartition, UINT64 rdx);

void EzHvNextInst(WHV_PARTITION_HANDLE hPartition, const WHV_RUN_VP_EXIT_CONTEXT& ctx);
bool EzHvHandleHvExit(WHV_PARTITION_HANDLE hPartition, const WHV_RUN_VP_EXIT_CONTEXT& ctx);
void EzHvHandleX64Cpuid(WHV_PARTITION_HANDLE hPartition, const WHV_RUN_VP_EXIT_CONTEXT& ctx);
void EzHvHandleX64IoPortAccess(WHV_PARTITION_HANDLE hPartition, const WHV_RUN_VP_EXIT_CONTEXT& ctx);