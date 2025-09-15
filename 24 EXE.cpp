#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char buffer[100];

    // 1. Creating a new file
    fd = creat("sample.txt", S_IRWXU);  // user has read/write/execute permission
    if (fd == -1) {
        perror("create");
        exit(1);
    } else {
        printf("File 'sample.txt' created successfully.\n");
        close(fd);
    }

    // 2. Opening an existing file for writing
    fd = open("sample.txt", O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for writing.\n");
    }

    // 3. Writing data to the file
    if (write(fd, "Hello, World!\n", 14) == -1) {
        perror("write");
        exit(1);
    }
    printf("Data written to 'sample.txt'.\n");
    close(fd);

    // 4. Opening the file for reading
    fd = open("sample.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for reading.\n");
    }

    // 5. Reading data from the file
    int bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read");
        exit(1);
    } else {
        printf("Data read from 'sample.txt':\n");
        write(STDOUT_FILENO, buffer, bytesRead); // print to terminal
    }
    close(fd);

    // 6. Deleting the file
    if (remove("sample.txt") == -1) {
        perror("remove");
        exit(1);
    } else {
        printf("\nFile 'sample.txt' deleted.\n");
    }

    return 0;
}

