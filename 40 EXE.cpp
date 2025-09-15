#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// Define permission constants if not available
#ifndef S_IRUSR
#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRGRP 0040
#define S_IWGRP 0020
#define S_IXGRP 0010
#define S_IROTH 0004
#define S_IWOTH 0002
#define S_IXOTH 0001
#endif

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main() {
    const char *filename = "demo.txt";
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File creation failed");
        return 1;
    }
    fprintf(fp, "Hello, world!\n");
    fclose(fp);

    chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    struct stat fileStat;
    stat(filename, &fileStat);
    print_permissions(fileStat.st_mode);

    return 0;
}

