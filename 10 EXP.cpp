#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hPipe;
    char buffer[128];
    DWORD dwWritten, dwRead;

    // Create a named pipe (acts like a queue)
    hPipe = CreateNamedPipe(
        "\\\\.\\pipe\\MyPipe",        // pipe name
        PIPE_ACCESS_DUPLEX,           // read/write access
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,                            // max instances
        128, 128, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("CreateNamedPipe failed.\n");
        return 1;
    }

    printf("Waiting for client to connect...\n");
    ConnectNamedPipe(hPipe, NULL);

    // Producer: write a message
    strcpy(buffer, "Hello, message queue!");
    WriteFile(hPipe, buffer, strlen(buffer) + 1, &dwWritten, NULL);
    printf("Producer sent: %s\n", buffer);

    // Consumer: read the message
    ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL);
    printf("Consumer received: %s\n", buffer);

    CloseHandle(hPipe);
    return 0;
}

