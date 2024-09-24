#include "des.h"

#pragma comment(lib, "ntdll.lib")
extern "C" unsigned long __cdecl DbgPrint(const char* Format, ...);
extern "C" long __stdcall NtTerminateProcess(void* ProcessHandle, long ExitStatus);
#define NtCurrentProcess() ((void*)(long long)-1)

// WHUCTF{e25ff8d8-e7be-42b7-9aec-7fe7eb5c93fa}
// encrypted with key: "EzNative"

void zero(void* ptr, size_t length)
{
    auto p = reinterpret_cast<unsigned char*>(ptr);
    for (size_t i = 0; i < length; ++i)
        p[i] = 0;
}

void foo(unsigned char* result)
{
    unsigned char des_key[8] = { 'E', 'z', 'N','a','t','i','v','e' };
    key_set keys[17];
    zero(keys, sizeof(keys));
    generate_sub_keys(des_key, keys);

    unsigned char data_block[48] =
    {
        0xC5, 0x08, 0x81, 0x64, 0xBA, 0x4B, 0x7B, 0x81,
        0xD8, 0xBA, 0x11, 0x97, 0x41, 0x3E, 0x14, 0x15,
        0xF5, 0xAD, 0x31, 0x90, 0x8D, 0xC7, 0x4B, 0x43,
        0x38, 0xC7, 0xA8, 0xB5, 0xC0, 0x44, 0x79, 0xEB,
        0x90, 0xDD, 0x06, 0x8F, 0x90, 0x34, 0x6A, 0x81,
        0x71, 0x41, 0x8C, 0x37, 0xAA, 0x2A, 0x5F, 0x73,
    };
    for (int i = 0; i < 48; i += 8)
        process_message(data_block + i, result + i, keys, DECRYPTION_MODE);

    return;
}

void NtProcessStartup()
{
    unsigned char result[48] = { 0 };
    foo(result);
    result[45] = '\n';
    result[46] = 0;
    DbgPrint("Your flag is: %s\n", result);
    NtTerminateProcess(NtCurrentProcess(), 0);
}
