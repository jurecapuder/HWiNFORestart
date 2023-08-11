#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

bool is_hwinfo_running() {
#ifdef _WIN32
    DWORD processIds[1024];
    DWORD bytesReturned;
    if (EnumProcesses(processIds, sizeof(processIds), &bytesReturned)) {
        DWORD numProcesses = bytesReturned / sizeof(DWORD);
        for (DWORD i = 0; i < numProcesses; i++) {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIds[i]);
            if (hProcess != NULL) {
                char processName[MAX_PATH];
                if (GetModuleBaseNameA(hProcess, NULL, processName, sizeof(processName))) {
                    if (std::string(processName) == "HWiNFO64.EXE") {
                        CloseHandle(hProcess);
                        return true;
                    }
                }
                CloseHandle(hProcess);
            }
        }
    }
#endif
    return false;
}

void open_hwinfo() {
#ifdef _WIN32
    if (!is_hwinfo_running()) {
        std::string hwinfoPath = "C:\\Program Files\\HWiNFO64\\HWiNFO64.EXE";
        ShellExecuteA(NULL, "open", hwinfoPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
        std::cout << "HWiNFO64.EXE is opened." << std::endl;
    } else {
        std::cout << "HWiNFO64.EXE is already running." << std::endl;
    }
#endif
}

void kill_hwinfo() {
#ifdef _WIN32
    DWORD processIds[1024];
    DWORD bytesReturned;
    if (EnumProcesses(processIds, sizeof(processIds), &bytesReturned)) {
        DWORD numProcesses = bytesReturned / sizeof(DWORD);
        for (DWORD i = 0; i < numProcesses; i++) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processIds[i]);
            if (hProcess != NULL) {
                char processName[MAX_PATH];
                if (GetModuleBaseNameA(hProcess, NULL, processName, sizeof(processName))) {
                    if (std::string(processName) == "HWiNFO64.EXE") {
                        TerminateProcess(hProcess, 0);
                        CloseHandle(hProcess);
                        std::cout << "HWiNFO64.EXE process terminated." << std::endl;
                        return;
                    }
                }
                CloseHandle(hProcess);
            }
        }
        std::cout << "HWiNFO64.EXE process is not running." << std::endl;
    }
#endif
}

int main() {
    // First, kill the HWiNFO64 process if it's running
    kill_hwinfo();

    // Add a small delay (in seconds)
    Sleep(1000);  // You can adjust the duration as needed

    // Then, open the HWiNFO64 process
    open_hwinfo();

    return 0;
}
