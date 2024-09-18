#pragma once

#include <Windows.h>

#include <optional>

std::optional<OSVERSIONINFOEXW> GetWindowsVersion();

void AdjustPrivilege(const wchar_t* privilege, bool enable);

bool LoadDriver(const wchar_t* driver, const wchar_t* path);
bool UnloadDriver(const wchar_t* driver);
