#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, disk_size;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the total disk size (e.g., 200): ");
    scanf("%d", &disk_size);

    // Sort the request queue
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    // SCAN algorithm (moving right first)
    int seek_time = 0;
    printf("\nSCAN (Elevator) Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);

    // Find position of head in sorted array
    int pos = 0;
    while (pos < n && request_queue[pos] < head) {
        pos++;
    }

    // Move right (towards higher cylinder numbers)
    for (int i = pos; i < n; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    // Go to end of disk
    if (head != disk_size - 1) {
        seek_time += abs(head - (disk_size - 1));
        head = disk_size - 1;
        printf(" -> %d", head);
    }

    // Move left (towards lower cylinder numbers)
    for (int i = pos - 1; i >= 0; i--) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}

