#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, at, bt, ct, tat, wt, st, priority;
};

int main() {
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    
    struct Process arr[n];
    
    for (int i = 0; i < n; i++) {
        arr[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority of Process P%d: ", i + 1);
        scanf("%d %d %d", &arr[i].at, &arr[i].bt, &arr[i].priority);
        arr[i].ct = 0;
    }

    int time = 0;
    int completed = 0;
    int total_wt = 0, total_tat = 0;

    printf("\nGantt Chart: ");

    while (completed < n) {
        int max = -1;
        int lowest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (arr[i].at <= time && arr[i].ct == 0 && arr[i].priority < lowest_priority) {
                lowest_priority = arr[i].priority;
                max = i;
            }
        }

        if (max != -1) {
            arr[max].st = time;
            printf("P%d ", arr[max].id);

            arr[max].ct = time+arr[max].bt;
            arr[max].tat = arr[max].ct - arr[max].at;
            arr[max].wt = arr[max].tat - arr[max].bt;
            time=arr[max].ct;
            total_wt += arr[max].wt;
            total_tat += arr[max].tat;
            completed++;
        } else {
            time++;
        }
    }

    printf("\n\nProcess\tPriority\tArrival_Time\tBurst_Time\tStart_Time\tCompletion_Time\tTurn_Around_Time\tWaiting_Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", arr[i].id, arr[i].priority, arr[i].at, arr[i].bt, arr[i].st, arr[i].ct, arr[i].tat, arr[i].wt);
    }

    double avg_wt = 1.0 * total_wt / n;
    double avg_tat = 1.0 * total_tat / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average TurnAround Time: %.2f\n", avg_tat);

    return 0;
}
