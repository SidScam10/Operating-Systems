#include<stdio.h>
#include<stdlib.h>

int main()
{
    int m,n;
    printf("Enter number of blocks: ");
    scanf("%d",&m);
    int block_size[m];
    printf("Enter block sizes: ");
    for(int i=0;i<m;i++)
    {
        scanf("%d",&block_size[i]);
    }

    printf("Enter Number of Process: ");
    scanf("%d",&n);
    int proc_size[n];
    printf("Enter Process Sizes: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&proc_size[i]);
    }

    int alloc[n];
    for(int i=0;i<n;i++) alloc[i]=-1;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(block_size[j]>=proc_size[i])
            {
                alloc[i]=j;
                block_size[j]-=proc_size[i];
                break;
            }
        }
    }

    printf("Process No\tProcess Size\tBlock Number\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t\t%d\t\t",i+1,proc_size[i]);
        if(alloc[i]!=-1) printf("%d\n",alloc[i]+1);
        else printf("Not Allocated\n");
    }
    return 0;
}