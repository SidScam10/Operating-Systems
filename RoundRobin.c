#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process {
    int id, at, bt, ct, tat, wt, st, rt;
    bool q;
};

struct Queue {
    int front, rear, size, capacity;
    int* arr;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = 25;
    queue->front = queue->size = 0;
    queue->rear = queue->capacity - 1;
    queue->arr = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int main() {
    printf("Enter number of processes: ");
    int n;
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter Arrival Time & Burst Time of Process P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].rt = processes[i].bt;
        processes[i].q = false;
    }

    int quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    struct Queue* queue = createQueue();
    int time = 0, completed = 0;

    int exec_order[1000];
    int exec_ind = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].at <= time) {
            enqueue(queue, i);
            processes[i].q = true;
        }
    }

    int curr_process;
    while (completed < n) {
        curr_process = dequeue(queue);

        if (curr_process == -1) {
            time++;
            for (int i = 0; i < n; i++) {
                if (processes[i].at <= time && processes[i].rt > 0 && !processes[i].q) {
                    enqueue(queue, i);
                    processes[i].q = true;
                }
            }
            continue;
        }

        exec_order[exec_ind++] = processes[curr_process].id;

        if (processes[curr_process].bt == processes[curr_process].rt) {
            processes[curr_process].st = time;
        }

        if (processes[curr_process].rt <= quantum) {
            time += processes[curr_process].rt;
            processes[curr_process].rt = 0;
            processes[curr_process].ct = time;
            processes[curr_process].tat = processes[curr_process].ct - processes[curr_process].at;
            processes[curr_process].wt = processes[curr_process].tat - processes[curr_process].bt;
            completed++;
            processes[curr_process].q = false;

            for (int i = 0; i < n; i++) {
                if (processes[i].at <= time && processes[i].rt > 0 && !processes[i].q) {
                    enqueue(queue, i);
                    processes[i].q = true;
                }
            }
        } else {
            time += quantum;
            processes[curr_process].rt -= quantum;
            for (int i = 0; i < n; i++) {
                if (processes[i].at <= time && processes[i].rt > 0 && !processes[i].q) {
                    enqueue(queue, i);
                    processes[i].q = true;
                }
            }

            enqueue(queue, curr_process);
        }
    }

    printf("\nGantt Chart: ");
    for (int i = 0; i < exec_ind; i++) {
        printf("P%d ", exec_order[i]);
    }

    int wt = 0, tat = 0;
    printf("\nProcess\tArrival_Time\tBurst_Time\tStart_Time\tCompletion_Time\tTurn_Around_Time\tWaiting_Time\n");
    for (int i = 0; i < n; i++) {
        wt += processes[i].wt;
        tat += processes[i].tat;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",
               processes[i].id, processes[i].at, processes[i].bt, processes[i].st,
               processes[i].ct, processes[i].tat, processes[i].wt);
    }

    double avg_wt = 1.0 * wt / n;
    double avg_tat = 1.0 * tat / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average TurnAround Time: %.2f\n", avg_tat);

    return 0;
}
