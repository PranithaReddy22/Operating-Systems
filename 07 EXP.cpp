#include <stdio.h>

int main() {
    int at[10], bt[10], pr[10];
    int n, i, j, temp, time = 0, over = 0;
    int sum_wait = 0, sum_turnaround = 0, start;
    float avgwait, avgturn;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter Arrival Time for Process %d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i+1);
        scanf("%d", &bt[i]);
        printf("Enter Priority for Process %d (higher = more priority): ", i+1);
        scanf("%d", &pr[i]);
    }

    // Sort by Arrival Time
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (at[i] > at[j]) {
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
            }
        }
    }

    printf("\n\nProcess\tArrival\tBurst\tPriority\tStart\tEnd\tWaiting\tTurnaround\n");

    // Scheduling loop
    while (over < n) {
        // find highest priority among available processes
        int pos = -1;
        int max_pr = -9999;

        for (i = over; i < n; i++) {
            if (at[i] <= time && pr[i] > max_pr) {
                max_pr = pr[i];
                pos = i;
            }
        }

        if (pos == -1) {
            time++; // no process has arrived yet
            continue;
        }

        // Swap to bring selected process to "over"
        if (pos != over) {
            temp = at[over]; at[over] = at[pos]; at[pos] = temp;
            temp = bt[over]; bt[over] = bt[pos]; bt[pos] = temp;
            temp = pr[over]; pr[over] = pr[pos]; pr[pos] = temp;
        }

        start = time;
        time += bt[over];

        int waiting = start - at[over];
        int turnaround = time - at[over];

        printf("P[%d]\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               over+1, at[over], bt[over], pr[over],
               start, time, waiting, turnaround);

        sum_wait += waiting;
        sum_turnaround += turnaround;

        over++;
    }

    avgwait = (float) sum_wait / n;
    avgturn = (float) sum_turnaround / n;

    printf("\nAverage Waiting Time: %.2f", avgwait);
    printf("\nAverage Turnaround Time: %.2f\n", avgturn);

    return 0;
}

