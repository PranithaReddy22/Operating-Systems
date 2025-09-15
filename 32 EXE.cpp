#include <stdio.h>
#define MAX_FRAMES 3

// Function to print current frames
void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int main() {
    int frames[MAX_FRAMES];
    int usageHistory[MAX_FRAMES]; // Track usage count (higher = older use)

    // Initialize
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        usageHistory[i] = 0;
    }

    int pageFaults = 0;
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    printf("Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\n");

    printf("Page Replacement Order (LRU):\n");

    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        // Check if page is already in frames
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;

                // Update usage: increment all except this one
                for (int k = 0; k < MAX_FRAMES; k++) {
                    if (k != j && frames[k] != -1) {
                        usageHistory[k]++;
                    }
                }
                usageHistory[j] = 0; // recently used
                break;
            }
        }

        // If not found ? page fault
        if (!pageFound) {
            printf("Page %d -> ", page);

            // Find the frame with maximum usage counter (LRU)
            int lruPage = 0;
            for (int j = 1; j < MAX_FRAMES; j++) {
                if (usageHistory[j] > usageHistory[lruPage]) {
                    lruPage = j;
                }
            }

            int replacedPage = frames[lruPage];
            frames[lruPage] = page;
            usageHistory[lruPage] = 0;

            // Increment all other counters
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (j != lruPage && frames[j] != -1) {
                    usageHistory[j]++;
                }
            }

            if (replacedPage != -1) {
                printf("Replace %d with %d: ", replacedPage, page);
            } else {
                printf("Load into empty frame: ");
            }

            printFrames(frames, MAX_FRAMES);
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}

