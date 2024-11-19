#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process {
    int id, at, bt, ct, tat, wt, st, rt;
    bool q;
};

struct Queue {
    int front, rear, size, capacity, *arr;
};

struct Queue* createQueue(int capacity) {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->front = q->size = 0;
    q->rear = capacity - 1;
    q->arr = malloc(capacity * sizeof(int));
    return q;
}

bool isEmpty(struct Queue* q) { return q->size == 0; }
void enqueue(struct Queue* q, int item) {
    if (q->size < q->capacity) {
        q->rear = (q->rear + 1) % q->capacity;
        q->arr[q->rear] = item;
        q->size++;
    }
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

int main() {
    int n, quantum, time = 0, completed = 0, exec_ind = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process arr[n];
    struct Queue* queue = createQueue(n);
    int exec_order[1000], wt = 0, tat = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time & Burst Time of Process P%d: ", i + 1);
        scanf("%d %d", &arr[i].at, &arr[i].bt);
        arr[i] = (struct Process){i + 1, arr[i].at, arr[i].bt, 0, 0, 0, 0, arr[i].bt, false};
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (arr[i].at <= time && !arr[i].q && arr[i].rt > 0) {
                enqueue(queue, i);
                arr[i].q = true;
            }
        }

        int curr = dequeue(queue);
        if (curr == -1) {
            time++;
            continue;
        }

        exec_order[exec_ind++] = arr[curr].id;
        if (arr[curr].bt == arr[curr].rt) arr[curr].st = time;

        int t = (arr[curr].rt <= quantum) ? arr[curr].rt : quantum;
        time += t;
        arr[curr].rt -= t;

        if (arr[curr].rt == 0) {
            arr[curr].ct = time;
            arr[curr].tat = arr[curr].ct - arr[curr].at;
            arr[curr].wt = arr[curr].tat - arr[curr].bt;
            wt += arr[curr].wt;
            tat += arr[curr].tat;
            completed++;
        } else {
            enqueue(queue, curr);
        }
    }

    printf("\nGantt Chart: ");
    for (int i = 0; i < exec_ind; i++) printf("P%d ", exec_order[i]);

    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", arr[i].id, arr[i].at, arr[i].bt, 
               arr[i].st, arr[i].ct, arr[i].tat, arr[i].wt);
    }

    printf("\nAverage WT: %.2f\nAverage TAT: %.2f\n", (double)wt / n, (double)tat / n);
    return 0;
}
