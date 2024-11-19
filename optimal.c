#include<stdio.h>

void display_blocks(int block[],int frame_size)
{
    for(int i=0;i<frame_size;i++)
    {
        if(block[i]==-1) printf("- ");
        else printf("%d ",block[i]);
    }
    printf("\n");
}
int find_opt(int blocks[], int pages[], int n, int frame_size, int curr_ind)
{
    int farthest=curr_ind,index=0;
    for(int i=0;i<frame_size;i++)
    {
        int j;
        for(j=curr_ind;j<n;j++)
        {
            if(blocks[i]==pages[j])
            {
                if(j>farthest)
                {
                    farthest=j;
                    index=i;
                }
                break;
            }
        }
        if(j==n) return i;
    }
    return index;
}
int main()
{
    int n,frame_size;
    printf("Enter Number of Pages: ");
    scanf("%d",&n);

    int pages[n];
    printf("Enter Pages: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }

    printf("Enter Frame Size: ");
    scanf("%d",&frame_size);

    int blocks[frame_size],hits=0,miss=0;
    for(int i=0;i<frame_size;i++) blocks[i]=-1;

    for(int i=0;i<n;i++)
    {
        int found=0;
        for(int j=0;j<frame_size;j++)
        {
            if(blocks[j]==pages[i])
            {
                found=1;
                hits++;
                break;
            }
        }
        if(!found)
        {
            if(i<frame_size)
            {
                blocks[i]=pages[i];
            }
            else
            {
                int replace=find_opt(blocks,pages,n,frame_size,i+1);
                blocks[replace]=pages[i];
            }
            miss++;
        }
        display_blocks(blocks,frame_size);
    }
    printf("Hits: %d\nMisses: %d\nHit Ratio: %.2f\nMiss Ratio: %.2f\n",hits,miss,(float)hits/n,(float)miss/n);
    return 0;
}