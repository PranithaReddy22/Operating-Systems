#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>  // For _mkdir()

int main() {
    char mainDirectory[] = "C:\\Users\\itssk\\OneDrive\\Desktop";  // Use double backslashes
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char filePath[300];
    char mainDirPath[300];

    // Build the subdirectory path
    snprintf(mainDirPath, sizeof(mainDirPath), "%s\\%s", mainDirectory, subDirectory);

    // Create the subdirectory if it does not exist
    if (_mkdir(mainDirPath) == 0) {
        printf("Directory created: %s\n", mainDirPath);
    } else {
        printf("Directory may already exist: %s\n", mainDirPath);
    }

    // Build full file path
    snprintf(filePath, sizeof(filePath), "%s\\%s", mainDirPath, fileName);

    // Create file
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("fopen");  // Show real system error
        printf("Error creating file at: %s\n", filePath);
        return 1;
    }

    fprintf(file, "This is an example file content.");
    fclose(file);

    printf("File created successfully: %s\n", filePath);

    return 0;
}

