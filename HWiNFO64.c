#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <tlhelp32.h>

int is_hwinfo_running() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return 0;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hProcessSnap, &pe32)) {
        do {
            if (strcmp(pe32.szExeFile, "HWiNFO64.EXE") == 0) {
                CloseHandle(hProcessSnap);
                return 1;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);
    return 0;
}

void open_hwinfo() {
    if (!is_hwinfo_running()) {
        char path[] = "C:\\Program Files\\HWiNFO64\\HWiNFO64.EXE";
        ShellExecute(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);
        printf("HWiNFO64.EXE is opened.\n");
    } else {
        printf("HWiNFO64.EXE is already running.\n");
    }
}

void kill_hwinfo() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hProcessSnap, &pe32)) {
        do {
            if (strcmp(pe32.szExeFile, "HWiNFO64.EXE") == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
                printf("HWiNFO64.EXE process terminated.\n");
                break;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);
}

int main() {
    // First, kill the HWiNFO64 process if it's running
    kill_hwinfo();

    // Add a small delay (in milliseconds)
    Sleep(1000);  // You can adjust the duration as needed

    // Then, open the HWiNFO64 process
    open_hwinfo();

    return 0;
}
