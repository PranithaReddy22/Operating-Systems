#include <stdio.h>
#include <conio.h>

int main() {
    int i, NOP, sum = 0, count = 0, y, quant;
    int wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;

    printf("Total number of processes in the system: ");
    scanf("%d", &NOP);
    y = NOP; // process counter

    for(i = 0; i < NOP; i++) {
        printf("\nEnter the Arrival Time of process[%d]: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter the Burst Time of process[%d]: ", i+1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; // copy burst time
    }

    printf("\nEnter the Time Quantum: ");
    scanf("%d", &quant);

    printf("\nProcess No\tBurst Time\tTurnaround Time\tWaiting Time\n");

    i = 0;
    sum = 0;
    while(y != 0) {
        if(temp[i] <= quant && temp[i] > 0) {
            sum += temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if(temp[i] > 0) {
            temp[i] -= quant;
            sum += quant;
        }

        if(temp[i] == 0 && count == 1) {
            y--;
            printf("Process[%d]\t%d\t\t%d\t\t%d\n", i+1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt += sum - at[i] - bt[i];
            tat += sum - at[i];
            count = 0;
        }

        if(i == NOP-1)
            i = 0;
        else if(at[i+1] <= sum)
            i++;
        else
            i = 0;
    }

    avg_wt = (float)wt / NOP;
    avg_tat = (float)tat / NOP;

    printf("\nAverage Waiting Time: %f", avg_wt);
    printf("\nAverage Turnaround Time: %f\n", avg_tat);

    getch();
    return 0;
}

