#include <stdio.h>
#include <windows.h>

int main() {
    // Create a named shared memory object
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use paging file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // Maximum object size (high-order DWORD)
        1024,                    // Maximum object size (low-order DWORD)
        "MySharedMemory"         // Name of mapping object
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    // Map a view of the file into the address space
    LPVOID pBuf = MapViewOfFile(
        hMapFile,                // Handle to map object
        FILE_MAP_ALL_ACCESS,     // Read/write permission
        0,
        0,
        1024
    );

    if (pBuf == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write message to shared memory
    const char *message = "Hello, shared memory (Windows)!";
    sprintf((char*)pBuf, "%s", message);

    printf("Data written to shared memory: %s\n", (char*)pBuf);

    // Cleanup
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

