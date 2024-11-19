#include <stdio.h>

#define MAX 100

void best_fit(int size_block[], int m, int proc_size[], int n) {
    int alloc[n];
    for (int i = 0; i < n; i++) {
        alloc[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int best_ind = -1;
        for (int j = 0; j < m; j++) {
            if (size_block[j] >= proc_size[i]) {
                if (best_ind == -1 || size_block[j] < size_block[best_ind]) {
                    best_ind = j;
                }
            }
        }
        if (best_ind != -1) {
            alloc[i] = best_ind;
            size_block[best_ind] -= proc_size[i];
        }
    }

    printf("\nBest Fit Allocation:");
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, proc_size[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worst_fit(int size_block[], int m, int proc_size[], int n) {
    int alloc[n];
    for (int i = 0; i < n; i++) {
        alloc[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worst_ind = -1;
        for (int j = 0; j < m; j++) {
            if (size_block[j] >= proc_size[i]) {
                if (worst_ind == -1 || size_block[j] > size_block[worst_ind]) {
                    worst_ind = j;
                }
            }
        }
        if (worst_ind != -1) {
            alloc[i] = worst_ind;
            size_block[worst_ind] -= proc_size[i];
        }
    }

    printf("\nWorst Fit Allocation:");
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, proc_size[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void first_fit(int size_block[], int m, int proc_size[], int n) {
    int alloc[n];
    for (int i = 0; i < n; i++) {
        alloc[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (size_block[j] >= proc_size[i]) {
                alloc[i] = j;
                size_block[j] -= proc_size[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:");
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, proc_size[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int size_block[MAX], proc_size[MAX];
    int m, n, choice;
    
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    printf("Enter the block sizes: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &size_block[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the process sizes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &proc_size[i]);
    }

    int t=0;
    while(t==0)
    {
        printf("\nChoose an Allocation Method:");
        printf("\n1) Best Fit\n2) Worst Fit\n3) First Fit\n4) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                best_fit(size_block, m, proc_size, n);
                break;
            case 2:
                worst_fit(size_block, m, proc_size, n);
                break;
            case 3:
                first_fit(size_block, m, proc_size, n);
                break;
            case 4:
                t=1;
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    

    return 0;
}