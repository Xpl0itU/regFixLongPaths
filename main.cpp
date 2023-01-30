#include <Windows.h>
#include <iostream>

int main() {
    HKEY hKey;
    DWORD dwValue = 1;
    DWORD dwType = REG_DWORD;
    DWORD dwSize = sizeof(dwValue);
    LONG lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                                  R"(SYSTEM\CurrentControlSet\Control\FileSystem)",
                                  0,
                                  nullptr,
                                  REG_OPTION_NON_VOLATILE,
                                  KEY_WRITE,
                                  nullptr,
                                  &hKey,
                                  nullptr);

    if (lResult == ERROR_SUCCESS) {
        lResult = RegSetValueEx(hKey,
                                "LongPathsEnabled",
                                0,
                                dwType,
                                (LPBYTE)&dwValue,
                                dwSize);

        if (lResult == ERROR_SUCCESS) {
            std::cout << "Registry key set successfully." << std::endl;
        } else {
            std::cout << "Failed to set registry key value. Error code: " << lResult << std::endl;
        }

        RegCloseKey(hKey);
    } else {
        std::cout << "Failed to create registry key. Error code: " << lResult << std::endl;
    }

    return 0;
}