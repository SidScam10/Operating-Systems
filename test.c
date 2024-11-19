#include<stdio.h>

struct Process {
    int id,at,bt,st,ct,pri,tat,wt,rt;
};

int main()
{
    int n,wt=0,tat=0;
    printf("Enter Number of Processes: ");
    scanf("%d",&n);
    struct Process arr[n];
    for(int i=0;i<n;i++)
    {
        arr[i].id=i+1;
        printf("Enter Arrival Time, Burst Time and Priority of Process P%d: ",i+1);
        scanf("%d %d %d",&arr[i].at,&arr[i].bt,&arr[i].pri);
        arr[i].ct=0;
    }
    int completed=0,time=0;
    while(completed<n)
    {
        int max=-1, highest_pri=-1;
        for(int i=0;i<n;i++)
        {
            if(arr[i].at<=time && arr[i].ct==0 && arr[i].pri>highest_pri)
            {
                max=i;
                highest_pri=arr[i].pri;
            }
        }
        if(max!=-1)
        {
            printf("%d ",arr[max].id);
            arr[max].st=time;
            arr[max].ct=time+arr[max].bt;
            arr[max].tat=arr[max].ct-arr[max].at;
            arr[max].wt=arr[max].tat-arr[max].bt;
            time=arr[max].ct;
            completed++;
            wt+=arr[max].wt;
            tat+=arr[max].tat;
        }
        else
        {
            time++;
        }
    }
    printf("\nProcess\tPriority\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",arr[i].id,arr[i].pri,arr[i].at,arr[i].bt,arr[i].st,arr[i].ct,arr[i].tat,arr[i].wt);
    }
    printf("AVG TAT: %.2f\nAVG WT: %.2f\n",(float)tat/n,(float)wt/n);
    return 0;
}