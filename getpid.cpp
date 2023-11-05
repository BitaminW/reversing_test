#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

int GetProcessIDByName(const std::string& processName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return -1;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &pe32)) {
        do {
            if (_stricmp((const char*)pe32.szExeFile, processName.c_str()) == 0) {
                CloseHandle(snapshot);
                return pe32.th32ProcessID;
            }
        } while (Process32Next(snapshot, &pe32));
    }

    CloseHandle(snapshot);
    return -1;
}

int main() {
    std::string processName = "notepad.exe";  // 대상 프로세스 이름
    DWORD pid = GetProcessIDByName(processName);

    if (pid != 0) {
        std::cout << "PID of " << processName << " is " << pid << std::endl;
    }
    else {
        std::cout << "Process not found." << std::endl;
    }

    return 0;
}
