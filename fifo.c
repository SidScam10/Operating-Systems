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

    int blocks[frame_size],hits=0,misses=0,index=0;
    for(int i=0;i<frame_size;i++) blocks[i]=-1;

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
            misses++;
        }
        display_blocks(blocks,frame_size);
    }
    printf("Hits: %d\nMisses: %d\nHit Ratio: %.2f\nMiss Ratio: %.2f\n",hits,misses,(float)hits/n,(float)misses/n);
    return 0;
}