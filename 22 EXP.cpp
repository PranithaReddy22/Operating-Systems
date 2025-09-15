#include <stdio.h>
#define MAX_MEMORY 1000

int memory[MAX_MEMORY];  

// Initialize memory
void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; // -1 means unallocated
    }
}

// Display memory free blocks
void displayMemory() {
    int i, j;
    int found = 0;
    printf("\nMemory Status:\n");
    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            found = 1;
            j = i;
            while (j < MAX_MEMORY && memory[j] == -1) {
                j++;
            }
            printf("Free memory block %d-%d (size=%d)\n", i, j - 1, j - i);
            i = j - 1; // Skip scanned part
        }
    }
    if (!found) {
        printf("No free memory available.\n");
    }
}

// Allocate memory using Best-Fit
void allocateMemory(int processId, int size) {
    int start = -1;
    int blockSize = 0;
    int bestStart = -1;
    int bestSize = MAX_MEMORY + 1; // Large number

    for (int i = 0; i <= MAX_MEMORY; i++) {
        if (i < MAX_MEMORY && memory[i] == -1) {
            if (blockSize == 0) start = i; // Start of free block
            blockSize++;
        } else {
            if (blockSize >= size && blockSize < bestSize) {
                bestSize = blockSize;
                bestStart = start;
            }
            blockSize = 0;
        }
    }

    if (bestStart != -1) {
        for (int i = bestStart; i < bestStart + size; i++) {
            memory[i] = processId;
        }
        printf("\nAllocated memory block %d-%d to Process %d\n",
               bestStart, bestStart + size - 1, processId);
    } else {
        printf("\nMemory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

// Deallocate memory
void deallocateMemory(int processId) {
    int released = 0;
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
            released = 1;
        }
    }
    if (released)
        printf("\nMemory released by Process %d\n", processId);
    else
        printf("\nNo memory found for Process %d\n", processId);
}

// Driver
int main() {
    initializeMemory();
    displayMemory();

    allocateMemory(1, 200);
    displayMemory();

    allocateMemory(2, 300);
    displayMemory();

    deallocateMemory(1);
    displayMemory();

    allocateMemory(3, 400);
    displayMemory();

    return 0;
}

