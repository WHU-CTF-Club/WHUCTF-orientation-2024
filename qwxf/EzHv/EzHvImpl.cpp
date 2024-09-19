#include "EzHvImpl.h"

#include "whpx.h"
#include "generator.h"

#include <cstdlib>
#include <iostream>
#include <print>
#include <array>

void* CSMEMORY = nullptr;
static std::string input;

UINT64 EzHvGetRip(WHV_PARTITION_HANDLE hPartition)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRip;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    HRESULT hr = whpx_dispatcher.WHvGetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvGetVirtualProcessorRegisters/WHvX64RegisterRip failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
    return rValue.Reg64;
};

void EzHvSetRip(WHV_PARTITION_HANDLE hPartition, UINT64 rip)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRip;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    rValue.Reg64 = rip;
    HRESULT hr = whpx_dispatcher.WHvSetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvSetVirtualProcessorRegisters/WHvX64RegisterRip failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
}

UINT64 EzHvGetRax(WHV_PARTITION_HANDLE hPartition)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRax;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    HRESULT hr = whpx_dispatcher.WHvGetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvGetVirtualProcessorRegisters/WHvX64RegisterRax failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
    return rValue.Reg64;
};

void EzHvSetRax(WHV_PARTITION_HANDLE hPartition, UINT64 rax)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRax;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    rValue.Reg64 = rax;
    HRESULT hr = whpx_dispatcher.WHvSetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvSetVirtualProcessorRegisters/WHvX64RegisterRax failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
}

UINT64 EzHvGetRbx(WHV_PARTITION_HANDLE hPartition)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRbx;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    HRESULT hr = whpx_dispatcher.WHvGetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvGetVirtualProcessorRegisters/WHvX64RegisterRbx failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
    return rValue.Reg64;
};

void EzHvSetRbx(WHV_PARTITION_HANDLE hPartition, UINT64 rbx)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRbx;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    rValue.Reg64 = rbx;
    HRESULT hr = whpx_dispatcher.WHvSetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvSetVirtualProcessorRegisters/WHvX64RegisterRbx failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
}

UINT64 EzHvGetRcx(WHV_PARTITION_HANDLE hPartition)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRcx;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    HRESULT hr = whpx_dispatcher.WHvGetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvGetVirtualProcessorRegisters/WHvX64RegisterRcx failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
    return rValue.Reg64;
};

void EzHvSetRcx(WHV_PARTITION_HANDLE hPartition, UINT64 rcx)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRcx;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    rValue.Reg64 = rcx;
    HRESULT hr = whpx_dispatcher.WHvSetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvSetVirtualProcessorRegisters/WHvX64RegisterRcx failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
}

UINT64 EzHvGetRdx(WHV_PARTITION_HANDLE hPartition)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRdx;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    HRESULT hr = whpx_dispatcher.WHvGetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvGetVirtualProcessorRegisters/WHvX64RegisterRdx failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
    return rValue.Reg64;
};

void EzHvSetRdx(WHV_PARTITION_HANDLE hPartition, UINT64 rdx)
{
    WHV_REGISTER_NAME rName = WHvX64RegisterRdx;
    WHV_REGISTER_VALUE rValue;
    ZeroMemory(&rValue, sizeof(rValue));
    rValue.Reg64 = rdx;
    HRESULT hr = whpx_dispatcher.WHvSetVirtualProcessorRegisters(hPartition, 0, &rName, 1, &rValue);
    if (FAILED(hr))
    {
        std::println("WHvSetVirtualProcessorRegisters/WHvX64RegisterRdx failed: 0x{:08X}", hr);
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
}

void EzHvNextInst(WHV_PARTITION_HANDLE hPartition, const WHV_RUN_VP_EXIT_CONTEXT& ctx)
{
    EzHvSetRip(hPartition, EzHvGetRip(hPartition) + ctx.VpContext.InstructionLength);
}

bool EzHvHandleHvExit(WHV_PARTITION_HANDLE hPartition, const WHV_RUN_VP_EXIT_CONTEXT& ctx)
{
    switch (ctx.ExitReason)
    {
    case WHvRunVpExitReasonX64IoPortAccess:
        EzHvHandleX64IoPortAccess(hPartition, ctx);
        return true;

    case WHvRunVpExitReasonX64Cpuid:
        EzHvHandleX64Cpuid(hPartition, ctx);
        return true;

    case WHvRunVpExitReasonX64Halt:
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        return false;

    default:
        std::println("Unexpected WHV_RUN_VP_EXIT_CONTEXT/ExitReason: 0x{:08X}", static_cast<HRESULT>(ctx.ExitReason));
        whpx_dispatcher.WHvDeleteVirtualProcessor(hPartition, 0);
        whpx_dispatcher.WHvDeletePartition(hPartition);
        std::exit(1);
    }
}

void EzHvHandleX64Cpuid(WHV_PARTITION_HANDLE hPartition, const WHV_RUN_VP_EXIT_CONTEXT& ctx)
{
    const auto& access = ctx.CpuidAccess;

    const auto eCpuidLeaf = static_cast<CpuidCommand>(access.Rax);

    if (eCpuidLeaf == CpuidCommand::GETRC4KEY)
    {
        // Get RC4 Key
        EzHvSetRax(hPartition, 'Ez');
        EzHvSetRbx(hPartition, 'Hv');
        EzHvSetRcx(hPartition, '_K');
        EzHvSetRdx(hPartition, 'ey');
    }
    else if (eCpuidLeaf == CpuidCommand::READSTRING)
    {
        // Read string
        std::cin >> input;
        if (input.length() > access.Rbx)
            input.resize(access.Rbx);

        EzHvSetRax(hPartition, input.length());
    }
    else if (eCpuidLeaf == CpuidCommand::FORMATCHECK)
    {
        if (!input.starts_with("flag{") || !input.ends_with("}"))
            EzHvSetRax(hPartition, 0);
        else
            EzHvSetRax(hPartition, 1);
    }
    else if (eCpuidLeaf == CpuidCommand::RC4EXTRAXOR)
    {
        constexpr std::array<UINT8, 2> cpuid_extra_rc4_xor{ 0xADu, 0xEFu };
        UINT8 value = static_cast<UINT8>(access.Rdx);
        const UINT8 index = static_cast<UINT8>(access.Rdx >> 8);
        if (index >= 0 && index < cpuid_extra_rc4_xor.size())
            value ^= cpuid_extra_rc4_xor[index];
        EzHvSetRdx(hPartition, value | (index << 8));
    }

    EzHvNextInst(hPartition, ctx);
}

static Generator<unsigned char> answer()
{
    constexpr unsigned char table[] =
    {
        0x24, 0x8D, 0xFC, 0x91, 0x1E, 0x85, 0x32, 0xF9,
        0x95, 0xC1, 0x13, 0x02, 0x71, 0xCB, 0x1C, 0x87,
        0x0E, 0xED, 0xCB, 0x37, 0x39, 0x5B, 0xB6, 0xC6,
        0x42, 0x51, 0x52, 0x13, 0xC4, 0xE5, 0xE2, 0x4F,
    };
    for (const auto& x : table)
        co_yield x;
}

void EzHvHandleX64IoPortAccess(WHV_PARTITION_HANDLE hPartition, const WHV_RUN_VP_EXIT_CONTEXT& ctx)
{
    const auto& access = ctx.IoPortAccess;
    const auto& info = access.AccessInfo;

    if (info.IsWrite && info.AccessSize == 1 && !info.StringOp)
    {
        const auto eIOPortCommand = static_cast<IOPortWriteCommand>(access.PortNumber);
        if (eIOPortCommand == IOPortWriteCommand::PUTCHAR)
        {
            std::print("{}", static_cast<char>(access.Rax));
        }
        else if (eIOPortCommand == IOPortWriteCommand::READROM)
        {
            constexpr UINT16 rom_crypt_key = static_cast<UINT16>('HV');

            auto create_rom = [rom_crypt_key]() consteval
                {
                    std::array<UINT16, 0x100> ROM{};

                    UINT8 i = 0;
                    ROM[i++] = 0;
                    ROM[i++] = 'W'; ROM[i++] = 'e'; ROM[i++] = 'l'; ROM[i++] = 'c'; ROM[i++] = 'o'; ROM[i++] = 'm'; ROM[i++] = 'e';
                    ROM[i++] = ' '; ROM[i++] = 't'; ROM[i++] = 'o'; ROM[i++] = ' '; ROM[i++] = 'E'; ROM[i++] = 'z'; ROM[i++] = 'H';
                    ROM[i++] = 'v'; ROM[i++] = '!'; ROM[i++] = '\n'; ROM[i++] = 'F'; ROM[i++] = 'e'; ROM[i++] = 'e'; ROM[i++] = 'l';
                    ROM[i++] = ' '; ROM[i++] = 'f'; ROM[i++] = 'r'; ROM[i++] = 'e'; ROM[i++] = 'e'; ROM[i++] = ' '; ROM[i++] = 't';
                    ROM[i++] = 'o'; ROM[i++] = ' '; ROM[i++] = 'e'; ROM[i++] = 'x'; ROM[i++] = 'p'; ROM[i++] = 'l'; ROM[i++] = 'o';
                    ROM[i++] = 'r'; ROM[i++] = 'e'; ROM[i++] = ' '; ROM[i++] = 'm'; ROM[i++] = 'e'; ROM[i++] = '!'; ROM[i++] = '\n';
                    ROM[i++] = 'P'; ROM[i++] = 'l'; ROM[i++] = 'e'; ROM[i++] = 'a'; ROM[i++] = 's'; ROM[i++] = 'e'; ROM[i++] = ' ';
                    ROM[i++] = 'i'; ROM[i++] = 'n'; ROM[i++] = 'p'; ROM[i++] = 'u'; ROM[i++] = 't';
                    ROM[i++] = ':'; ROM[i++] = ' '; ROM[0] = i - 1;

                    ROM[128] = 0x7F72u; ROM[129] = 0x9E14u; ROM[130] = 0x8D12u; ROM[131] = 0x74FCu; ROM[132] = 0x51EDu; ROM[133] = 0x81F4u; ROM[134] = 0x770Au; ROM[135] = 0x75ACu;
                    ROM[136] = 0x2E15u; ROM[137] = 0x2617u; ROM[138] = 0xC96Bu; ROM[139] = 0xB096u; ROM[140] = 0x4003u; ROM[141] = 0xB80Fu; ROM[142] = 0x5671u; ROM[143] = 0xE7A5u;
                    ROM[144] = 0xABE4u; ROM[145] = 0xD85Eu; ROM[146] = 0x1E5Du; ROM[147] = 0xF00Bu; ROM[148] = 0xE58Eu; ROM[149] = 0xCD83u; ROM[150] = 0x9759u; ROM[151] = 0x579Du;
                    ROM[152] = 0x5F36u; ROM[153] = 0x44D9u; ROM[154] = 0xA4F7u; ROM[155] = 0x5B21u; ROM[156] = 0xDE7Du; ROM[157] = 0x8655u; ROM[158] = 0x9FD0u; ROM[159] = 0xF2FEu;
                    ROM[160] = 0x5409u; ROM[161] = 0x60CAu; ROM[162] = 0xD685u; ROM[163] = 0x2B70u; ROM[164] = 0x9289u; ROM[165] = 0xB4B9u; ROM[166] = 0xFB69u; ROM[167] = 0x2F35u;
                    ROM[168] = 0x68B6u; ROM[169] = 0x2A94u; ROM[170] = 0xDFC4u; ROM[171] = 0x7B65u; ROM[172] = 0xC1F6u; ROM[173] = 0x4933u; ROM[174] = 0xC59Cu; ROM[175] = 0xAE95u;
                    ROM[176] = 0xB7E3u; ROM[177] = 0x8288u; ROM[178] = 0x1602u; ROM[179] = 0x8BDBu; ROM[180] = 0x0E45u; ROM[181] = 0x1F39u; ROM[182] = 0x8A43u; ROM[183] = 0x6C7Eu;
                    ROM[184] = 0xC727u; ROM[185] = 0x4F18u; ROM[186] = 0xF5C6u; ROM[187] = 0xE824u; ROM[188] = 0x059Bu; ROM[189] = 0x3FEBu; ROM[190] = 0x67EAu; ROM[191] = 0x6D52u;
                    ROM[192] = 0x2530u; ROM[193] = 0xCE34u; ROM[194] = 0xBE01u; ROM[195] = 0x1D76u; ROM[196] = 0xDDB3u; ROM[197] = 0x73DCu; ROM[198] = 0xAFBDu; ROM[199] = 0x0484u;
                    ROM[200] = 0x37A3u; ROM[201] = 0xA7E6u; ROM[202] = 0x13CBu; ROM[203] = 0xF990u; ROM[204] = 0xD2C2u; ROM[205] = 0xBBA0u; ROM[206] = 0x5864u; ROM[207] = 0xB25Cu;
                    ROM[208] = 0x8F91u; ROM[209] = 0xB5A2u; ROM[210] = 0xA900u; ROM[211] = 0x66B1u; ROM[212] = 0x1CECu; ROM[213] = 0x6AFDu; ROM[214] = 0x479Au; ROM[215] = 0x226Eu;
                    ROM[216] = 0x3E38u; ROM[217] = 0x1B61u; ROM[218] = 0xA1FFu; ROM[219] = 0x4693u; ROM[220] = 0xF33Cu; ROM[221] = 0x53BFu; ROM[222] = 0x19CCu; ROM[223] = 0x4E63u;
                    ROM[224] = 0xF832u; ROM[225] = 0x06EEu; ROM[226] = 0x075Au; ROM[227] = 0x423Bu; ROM[228] = 0xAAD3u; ROM[229] = 0x31BCu; ROM[230] = 0x4BA6u; ROM[231] = 0x1008u;
                    ROM[232] = 0x8C3Au; ROM[233] = 0xD120u; ROM[234] = 0xCFD7u; ROM[235] = 0xE27Cu; ROM[236] = 0xFA23u; ROM[237] = 0x6F28u; ROM[238] = 0x3DA8u; ROM[239] = 0xC062u;
                    ROM[240] = 0x4AE1u; ROM[241] = 0x0D78u; ROM[242] = 0x994Du; ROM[243] = 0x41BAu; ROM[244] = 0x8779u; ROM[245] = 0x2CDAu; ROM[246] = 0xF1C8u; ROM[247] = 0x11ADu;
                    ROM[248] = 0xE0C3u; ROM[249] = 0x4C50u; ROM[250] = 0x1A0Cu; ROM[251] = 0x48EFu; ROM[252] = 0x2D80u; ROM[253] = 0xE929u; ROM[254] = 0xD5D4u; ROM[255] = 0x987Au;

                    for (auto& value : ROM)
                        value ^= rom_crypt_key;

                    return ROM;
                };

            static constexpr auto ROM = create_rom();

            UINT8 index = static_cast<UINT8>(access.Rax);
            if (index >= 0 && index < ROM.size())
                EzHvSetRax(hPartition, ROM[index] ^ rom_crypt_key);
        }
        else if (eIOPortCommand == IOPortWriteCommand::GETCHAR)
        {
            UINT16 index = static_cast<UINT16>(access.Rax);
            if (index >= 0 && index < input.length())
                EzHvSetRax(hPartition, input[index]);
        }
        else if (eIOPortCommand == IOPortWriteCommand::HEXDBG)
        {
            const UINT8 value = static_cast<UINT8>(access.Rax);
            std::print("0x{:02x}, ", value);
        }
        else if (eIOPortCommand == IOPortWriteCommand::VERIFY)
        {
            static auto generator = answer();
            static auto iter = generator.begin();

            if (iter == generator.end())
                EzHvSetRax(hPartition, false);
            else
            {
                EzHvSetRax(hPartition, static_cast<UINT8>(EzHvGetRax(hPartition)) == *iter);
                ++iter;
            }
        }
    }

    EzHvNextInst(hPartition, ctx);
}