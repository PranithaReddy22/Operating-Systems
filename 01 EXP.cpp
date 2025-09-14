#include <stdio.h>
#include <windows.h>

int main() {
    DWORD pid = GetCurrentProcessId();
    DWORD ppid = GetCurrentProcessId(); 

    printf("Process ID: %lu\n", pid);
    printf("Parent Process ID (not directly available in Windows API): %lu\n", ppid);

    return 0;
}

