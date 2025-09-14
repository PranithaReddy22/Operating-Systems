#include <stdio.h>

void firstfit(int mp[], int p[], int m, int n) {
    int allocated[m];
    for (int i = 0; i < m; i++) allocated[i] = -1;

    for (int i = 0; i < m; i++) {   // for each process
        for (int j = 0; j < n; j++) {  // check each partition
            if (mp[j] >= p[i]) {
                allocated[i] = j;
                mp[j] -= p[i];
                break;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (allocated[i] != -1)
            printf("Process %d (size %d) allocated in Partition %d\n", i+1, p[i], allocated[i]+1);
        else
            printf("Process %d (size %d) must wait\n", i+1, p[i]);
    }
}

void bestfit(int mp[], int p[], int m, int n) {
    int allocated[m];
    for (int i = 0; i < m; i++) allocated[i] = -1;

    for (int i = 0; i < m; i++) {
        int bestIdx = -1;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (bestIdx == -1 || mp[j] < mp[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocated[i] = bestIdx;
            mp[bestIdx] -= p[i];
        }
    }

    for (int i = 0; i < m; i++) {
        if (allocated[i] != -1)
            printf("Process %d (size %d) allocated in Partition %d\n", i+1, p[i], allocated[i]+1);
        else
            printf("Process %d (size %d) must wait\n", i+1, p[i]);
    }
}

void worstfit(int mp[], int p[], int m, int n) {
    int allocated[m];
    for (int i = 0; i < m; i++) allocated[i] = -1;

    for (int i = 0; i < m; i++) {
        int worstIdx = -1;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (worstIdx == -1 || mp[j] > mp[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocated[i] = worstIdx;
            mp[worstIdx] -= p[i];
        }
    }

    for (int i = 0; i < m; i++) {
        if (allocated[i] != -1)
            printf("Process %d (size %d) allocated in Partition %d\n", i+1, p[i], allocated[i]+1);
        else
            printf("Process %d (size %d) must wait\n", i+1, p[i]);
    }
}

int main() {
    int m, n, mp[20], p[20], ch;

    printf("Number of memory partitions: ");
    scanf("%d", &n);

    printf("Number of processes: ");
    scanf("%d", &m);

    printf("Enter the memory partitions:\n");
    for (int i = 0; i < n; i++) scanf("%d", &mp[i]);

    printf("Enter process sizes:\n");
    for (int i = 0; i < m; i++) scanf("%d", &p[i]);

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            firstfit(mp, p, m, n);
            break;
        case 2:
            bestfit(mp, p, m, n);
            break;
        case 3:
            worstfit(mp, p, m, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

