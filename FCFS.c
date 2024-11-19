#include<stdio.h>

struct Process {
    int id,at,bt,st,ct,tat,wt;
};

int main()
{
    int n;
    scanf("%d",&n);

    struct Process arr[n];
    for(int i=0;i<n;i++)
    {
        arr[i].id=i+1;
        printf("Enter Arrival Time & Burst Time for Process P%d: ",i+1);
        scanf("%d %d",&arr[i].at,&arr[i].bt);
    } 
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j].at>arr[j+1].at)
            {
                struct Process temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    int tat=0,wt=0,time=0;
    printf("Gantt Chart: ");
    for(int i=0;i<n;i++)
    {
        if(time<arr[i].at)
        {
            time=arr[i].at;
        }
        printf("P%d ",arr[i].id);
        arr[i].st=time;
        arr[i].ct=time+arr[i].bt;
        arr[i].tat=arr[i].ct-arr[i].at;
        arr[i].wt=arr[i].tat-arr[i].bt;
        time=arr[i].ct;

        tat+=arr[i].tat;
        wt+=arr[i].wt;
    }
    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",arr[i].id,arr[i].at,arr[i].bt,arr[i].st,arr[i].ct,arr[i].tat,arr[i].wt);
    }
    printf("AVG TAT: %.2f\nAVG WT: %.2f\n",(float)tat/n,(float)wt/n);
}