#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Process {
    int id,at,bt,st,ct,tat,wt,rt;
    bool q;
};

struct Queue {
    int front,rear,size,cap,*arr;
};

struct Queue* createQueue(int cap){
    struct Queue* q=malloc(sizeof(struct Queue));
    q->cap=cap;
    q->front=q->size=0;
    q->rear=cap-1;
    q->arr=malloc(cap*sizeof(int));
    return q;
};

bool isEmpty(struct Queue* q) { return q->size==0; }

void enqueue(struct Queue* q,int item){
    if(q->size<q->cap)
    {
        q->rear=(q->rear+1)%q->cap;
        q->arr[q->rear]=item;
        q->size++;
    }
}

int dequeue(struct Queue* q) {
    if(isEmpty(q)) return -1;
    int item=q->arr[q->front];
    q->front=(q->front+1)%q->cap;
    q->size--;
    return item;
}

int main()
{
    int n,quantum,completed=0,time=0,tat=0,wt=0;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct Process arr[n];
    struct Queue* queue=createQueue(n);
    for(int i=0;i<n;i++)
    {
        arr[i].id=i+1;
        printf("Enter Arrival Time & Burst Time of Process P%d: ",i+1);
        scanf("%d %d",&arr[i].at,&arr[i].bt);
        arr[i].rt=arr[i].bt;
        arr[i].q=false;
    }
    printf("Enter Time Quantum: ");
    scanf("%d",&quantum);

    printf("Gantt Chart: ");
    while(completed<n)
    {
        for(int i=0;i<n;i++)
        {
            if(arr[i].at<=time && !arr[i].q && arr[i].rt>0)
            {
                enqueue(queue,i);
                arr[i].q=true;
            }
        }
        int curr=dequeue(queue);
        if(curr==-1)
        {
            time++;
            continue;
        }

        printf("P%d ",arr[curr].id);

        if(arr[curr].bt==arr[curr].rt) arr[curr].st=time;

        int t=(arr[curr].rt<=quantum)? arr[curr].rt:quantum;
        time+=t;
        arr[curr].rt-=t;
        
        if(arr[curr].rt==0)
        {
            arr[curr].ct=time;
            arr[curr].tat=arr[curr].ct-arr[curr].at;
            arr[curr].wt=arr[curr].tat-arr[curr].bt;

            tat+=arr[curr].tat;
            wt+=arr[curr].wt;
            completed++;
        }
        else{
            enqueue(queue,curr);
        }
    }
    
    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",arr[i].id,arr[i].at,arr[i].bt,arr[i].st,arr[i].ct,arr[i].tat,arr[i].wt);
    }
    printf("Avg TAT: %.2f \n Avg WT: %.2f",(float)tat/n,(float)wt/n);
    return 0;
}