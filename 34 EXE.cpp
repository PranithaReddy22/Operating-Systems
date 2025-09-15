#include <stdio.h>
#include <stdlib.h>

// Structure to represent a record
struct Record {
    int recordNumber;
    char data[256]; // Adjust size as needed
};

int main() {
    FILE *file;
    struct Record record;
    int recordNumber;

    // Open or create a file in write mode (for writing records)
    file = fopen("sequential_file.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write records sequentially to the file
    printf("Enter records (Enter '0' as record number to stop):\n");
    while (1) {
        printf("Record Number: ");
        scanf("%d", &record.recordNumber);

        if (record.recordNumber == 0) {
            break; // Stop writing
        }

        // Input data for the record
        printf("Data: ");
        scanf(" %[^\n]", record.data);

        // Write the record to the file
        fwrite(&record, sizeof(struct Record), 1, file);
    }
    fclose(file);

    // Reopen the file in read mode (for reading records)
    file = fopen("sequential_file.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read specific records from the file
    while (1) {
        printf("\nEnter the record number to read (0 to exit): ");
        scanf("%d", &recordNumber);

        if (recordNumber == 0) {
            break; // Stop reading
        }

        // Reset file pointer before scanning
        rewind(file);

        // Read sequentially until the requested record is found
        while (fread(&record, sizeof(struct Record), 1, file)) {
            if (record.recordNumber == recordNumber) {
                printf("Record Found:\n");
                printf("Record Number: %d\n", record.recordNumber);
                printf("Data: %s\n", record.data);
                break;
            }
        }
    }

    fclose(file);
    return 0;
}

