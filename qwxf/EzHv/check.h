#pragma once

enum class CpuVendor
{
    GenuineIntel,
    AuthenticAMD,
    Unknown,
};
CpuVendor GetCpuVendor();

bool IsVtEnabled();
bool IsHyperVEnabled();