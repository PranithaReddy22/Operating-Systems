#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek_time = 0;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    // Sort the request queue in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    // C-SCAN Scheduling
    printf("\nC-SCAN Disk Scheduling:\n");

    int i;
    // Service requests greater than or equal to head
    for (i = 0; i < n; i++) {
        if (request_queue[i] >= head) {
            seek_time += abs(head - request_queue[i]);
            head = request_queue[i];
        }
    }

    // Move head to the end of disk (assuming disk starts at 0 and max = request_queue[n-1])
    if (head != request_queue[n - 1]) {
        seek_time += abs(head - request_queue[n - 1]);
        head = request_queue[n - 1];
    }

    // Jump to the start of the disk (0)
    seek_time += abs(head - 0);
    head = 0;

    // Service remaining requests (those less than initial head)
    for (i = 0; i < n; i++) {
        if (request_queue[i] < head || request_queue[i] < head + 1) { // requests at start
            seek_time += abs(head - request_queue[i]);
            head = request_queue[i];
        }
    }

    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}

