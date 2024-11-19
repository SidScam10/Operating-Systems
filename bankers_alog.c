#include <stdio.h>

int main() {
    
    int process_count, resource_count;
    printf("Enter Number of Processes: ");
    scanf("%d", &process_count);
    printf("Enter Number of Resources: ");
    scanf("%d", &resource_count);
    
    int res_alloc[process_count][resource_count], max_res_alloc[process_count][resource_count], aval_resources[resource_count], need_resources[process_count][resource_count], safe_seq[process_count];
    int finished[process_count], count = 0;
    
    printf("Enter Resource Allocation Table Values: \n");
    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < resource_count; j++) {
            scanf("%d", &res_alloc[i][j]);
        }
    }
    
    printf("Enter Maximum Resource Table Values: \n");
    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < resource_count; j++) {
            scanf("%d", &max_res_alloc[i][j]);
        }
    }

    printf("Enter Available Resources: ");
    for (int i = 0; i < resource_count; i++) {
        scanf("%d", &aval_resources[i]);
    }

    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < resource_count; j++) {
            aval_resources[j] -= res_alloc[i][j];
        }
    }

    printf("Available Resources After Allocation: ");
    for (int i = 0; i < resource_count; i++) {
        printf("%d ", aval_resources[i]);
    }
    printf("\n");

    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < resource_count; j++) {
            need_resources[i][j] = max_res_alloc[i][j] - res_alloc[i][j];
        }
    }

    for (int i = 0; i < process_count; i++) {
        finished[i] = 0;
    }

    while (count < process_count) {
        int found = 0;
        for (int i = 0; i < process_count; i++) {
            if (!finished[i]) {
                int j;
                for (j = 0; j < resource_count; j++) {
                    if (need_resources[i][j] > aval_resources[j]) {
                        break;
                    }
                }

                if (j == resource_count) {
                    for (int k = 0; k < resource_count; k++) {
                        aval_resources[k] += res_alloc[i][k];
                    }
                    safe_seq[count++] = i+1;
                    finished[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("System Is Not In A Safe State\n");
            return 0;
        }
    }

    printf("Final Resource Table: \n");
    printf("Process\tResource Allocation\tMaximum Allocation\tNeed Resources\n");
    for (int i = 0; i < process_count; i++) {
        printf("P%d",i+1);
        for(int j=0;j<resource_count;j++)
        {
            printf("\t%d",res_alloc[i][j]);
        }
        for(int j=0;j<resource_count;j++)
        {
            printf("\t%d",max_res_alloc[i][j]);
        }
        for(int j=0;j<resource_count;j++)
        {
            printf("\t%d",need_resources[i][j]);
        }
        printf("\n");
    }

    printf("Available Resources: ");
    for (int i = 0; i < resource_count; i++) {
        printf("%d ", aval_resources[i]);
    }
    printf("\n");

    printf("System Is In A Safe State\n");
    printf("Safe Sequence: ");
    for (int i = 0; i < count; i++) {
        if(i==count-1)
        {
            printf("P%d\n",safe_seq[i]);
            break;
        }
        printf("P%d -> ", safe_seq[i]);
    }

    return 0;
}