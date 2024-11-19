#include<stdio.h>
#include<stdlib.h>
int n;
void display_blocks(int blocks[], int frame_size)
{
    for(int i=0;i<frame_size;i++)
    {
        if(blocks[i]==-1)
        {
            printf(" ");
        }
        else
        {
            printf("%d ",blocks[i]);
        }
    }
    printf("\n");
}
void fifo(int pages[],int frame_size)
{
    int blocks[frame_size],hits=0,miss=0;
    for(int i=0;i<frame_size;i++) blocks[i]=-1;
    int index=0;
    for(int i=0;i<n;i++)
    {
        int found=0;
        for(int j=0;j<frame_size;j++)
        {
            if(blocks[j]==pages[i])
            {
                hits++;
                found=1;
                break;
            }
        }
        if(!found)
        {
            blocks[index]=pages[i];
            index=(index+1)%frame_size;
            miss++;
        }
        display_blocks(blocks,frame_size);
    }
    printf("Hits: %d\tMiss: %d\tHit Ratio: %.3f\tMiss Ratio: %.3f",hits,miss,(float)hits/n,(float)miss/n);
}
void lru(int pages[],int frame_size)
{
    int block[frame_size],recent[frame_size],hit=0,miss=0;
    for(int i=0;i<frame_size;i++)
    {
        block[i]=-1;
        recent[i]=-1;
    }
    for(int i=0;i<n;i++)
    {
        int found=0,least_recent=0;
        for(int j=0;j<frame_size;j++)
        {
            if(block[i]==recent[j])
            {
                hit++;
                recent[j]=i;
                found=1;
                break;
            }
        }
        if(!found)
        {
            for(int j=1;j<frame_size;j++)
            {
                if(recent[j]<recent[least_recent])
                {
                    least_recent=j;
                }
            }
            block[least_recent]=pages[i];
            recent[least_recent]=i;
            miss++;

        }
    }
    printf("Hits: %d\tMiss: %d\tHit Ratio: %.3f\tMiss Ratio: %.3f",hit,miss,(float)hit/n,(float)miss/n);
}
int main()
{
    printf("Enter Number of Pages: ");
    scanf("%d",&n);
    int pages[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    int frame_size;
    scanf("%d",&frame_size);
    fifo(pages,frame_size);
    lru(pages,frame_size);
}