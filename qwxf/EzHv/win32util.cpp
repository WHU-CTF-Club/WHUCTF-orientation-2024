#include "win32util.h"

#include "handle.h"

#include <fstream>
#include "check.h"

std::optional<OSVERSIONINFOEXW> GetWindowsVersion()
{
    using fn_RtlGetVersion_t = LONG(WINAPI*)(OSVERSIONINFOEXW*);
    HMODULE hModule = GetModuleHandleW(L"ntdll.dll");
    if (hModule)
    {
        fn_RtlGetVersion_t fn_RtlGetVersion =
            reinterpret_cast<fn_RtlGetVersion_t>(GetProcAddress(hModule, "RtlGetVersion"));
        if (fn_RtlGetVersion)
        {
            OSVERSIONINFOEXW info;
            info.dwOSVersionInfoSize = sizeof(info);
            if (fn_RtlGetVersion(&info) >= 0) // NT_SUCCESS
                return info;
        }
    }
    return std::nullopt;
}

void AdjustPrivilege(const wchar_t* privilege, bool enable)
{
    PrivilegeTokenHandle token;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token.get()) == FALSE)
        return;

    TOKEN_PRIVILEGES priv{ 0 };
    if (LookupPrivilegeValueW(nullptr, privilege, &priv.Privileges[0].Luid) == FALSE)
        return;

    priv.PrivilegeCount = 1;
    priv.Privileges->Attributes = enable ? SE_PRIVILEGE_ENABLED : 0;

    AdjustTokenPrivileges(token, false, &priv, sizeof(priv), nullptr, nullptr);
}

bool UnloadDriver(const wchar_t* driver)
{
    ServiceHandle manager{ OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS) };
    if (!manager)
        return false;

    ServiceHandle service{ OpenServiceW(manager, driver, SERVICE_ALL_ACCESS) };
    if (!service)
        return false;

    SERVICE_STATUS status;
    ControlService(service, SERVICE_CONTROL_STOP, &status);
    DeleteService(service);

    return true;
}

bool LoadDriver(const wchar_t* driver, const wchar_t* path)
{
    ServiceHandle manager{ OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS) };
    if (!manager)
        return false;

    ServiceHandle service{
        CreateServiceW(manager, driver, driver, SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER,
        SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, path, nullptr, nullptr,
        nullptr, nullptr, nullptr)
    };

    if (!service)
    {
        const DWORD dwError = GetLastError();
        if (dwError != ERROR_IO_PENDING && dwError != ERROR_SERVICE_EXISTS)
            return false;

        service.reset(OpenServiceW(manager, driver, SERVICE_ALL_ACCESS));
        if (!service)
            return false;
    }

    if (StartServiceW(service, 0, nullptr))
        return true;

    return GetLastError() == ERROR_SERVICE_ALREADY_RUNNING;
}