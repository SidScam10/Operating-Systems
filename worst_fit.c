#include<stdio.h>
#include<stdlib.h>

int main()
{
    int m,n;
    printf("Enter Number of Blocks: ");
    scanf("%d",&m);
    printf("Enter Number of Processes: ");
    scanf("%d",&n);

    int block_size[m],proc_size[n];
    for(int i=0;i<m;i++) 
    {
        scanf("%d",&block_size[i]);
    }
    for(int i=0;i<n;i++)
    {
        scanf("%d",&proc_size[i]);
    }

    int alloc[n];
    for(int i=0;i<n;i++) alloc[i]=-1;

    for(int i=0;i<n;i++)
    {
        int worst_ind=-1;
        for(int j=0;j<m;j++)
        {
            if(block_size[j]>=proc_size[i])
            {
                if(worst_ind==-1 || block_size[j]>block_size[worst_ind]) worst_ind=j;
            }
        }
        if(worst_ind!=-1)
        {
            alloc[i]=worst_ind;
            block_size[worst_ind]-=proc_size[i];
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