#include <stdio.h>
#include <stdlib.h>

// Structure to represent a block
struct Block {
    int blockNumber;
    char data[256]; // Adjust the size as needed
};

int main() {
    FILE *file;
    struct Block block;
    int blockNumber;

    // Create an index block that contains pointers to data blocks
    long indexBlock[100] = {0}; // Store file offsets of each block

    // Open or create a file in write mode (for writing blocks)
    file = fopen("indexed_file.txt", "w+b"); // "w+b" allows write+read
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write blocks and update the index block
    printf("Enter blocks (Enter '0' as block number to stop):\n");
    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);

        if (block.blockNumber == 0) {
            break; // stop writing
        }

        // Input data for the block
        printf("Data: ");
        scanf(" %[^\n]", block.data);

        // Record current position (before writing)
        long pos = ftell(file);

        // Write the block to the file
        fwrite(&block, sizeof(struct Block), 1, file);

        // Update the index block with the file offset of the block
        indexBlock[block.blockNumber] = pos;
    }

    // Reading part
    while (1) {
        printf("\nEnter the block number to read (0 to exit): ");
        scanf("%d", &blockNumber);

        if (blockNumber == 0) {
            break; // stop reading
        }

        if (indexBlock[blockNumber] == 0) {
            printf("Block not found.\n");
        } else {
            // Seek to the data block using the index block
            fseek(file, indexBlock[blockNumber], SEEK_SET);
            fread(&block, sizeof(struct Block), 1, file);

            printf("Block Found:\n");
            printf("Block Number: %d\n", block.blockNumber);
            printf("Data: %s\n", block.data);
        }
    }

    fclose(file);
    return 0;
}

