#include <stdio.h>
#include <conio.h>   // for getch(), optional

int main() {
    int i, NOP, sum = 0, count = 0, y, quant;
    int wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;

    printf("Total number of processes in the system: ");
    scanf("%d", &NOP);

    y = NOP; // number of processes left

    for(i = 0; i < NOP; i++) {
        printf("\nEnter Arrival Time of Process[%d]: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of Process[%d]: ", i+1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; // store burst time in temp array
    }

    printf("\nEnter the Time Quantum: ");
    scanf("%d", &quant);

    printf("\nProcess\tBurst Time\tTurnaround Time\tWaiting Time\n");

    i = 0;
    while(y != 0) {
        if(temp[i] <= quant && temp[i] > 0) {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if(temp[i] > 0) {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }

        if(temp[i] == 0 && count == 1) {
            y--;  // one process finished
            printf("P[%d]\t%d\t\t%d\t\t%d\n", i+1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt = wt + sum - at[i] - bt[i];
            tat = tat + sum - at[i];
            count = 0;
        }

        if(i == NOP - 1)
            i = 0;
        else if(at[i+1] <= sum)
            i++;
        else
            i = 0;
    }

    avg_wt = wt * 1.0 / NOP;
    avg_tat = tat * 1.0 / NOP;

    printf("\nAverage Waiting Time:\t%.2f", avg_wt);
    printf("\nAverage Turnaround Time:\t%.2f", avg_tat);

    getch(); // optional
    return 0;
}

