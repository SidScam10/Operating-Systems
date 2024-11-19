#include <stdio.h>
#define MAX 100

void display_blocks(int blocks[], int frame_size) 
{
    for (int i = 0; i < frame_size; i++) 
    {
        if (blocks[i] == -1)
            printf("  ");
        else
            printf("%d ", blocks[i]);
    }
    printf("\n");
}

void fifo(int pages[], int n, int frame_size) 
{
    printf("\n-FIFO Page Replacement-\n");
    int blocks[frame_size], misses = 0, hits = 0;
    for (int i = 0; i < frame_size; i++) blocks[i] = -1;

    int index = 0;
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frame_size; j++) 
        {
            if (blocks[j] == pages[i]) 
            {
                found = 1;
                hits++;
                break;
            }
        }
        if (!found) 
        {
            blocks[index] = pages[i];
            index = (index + 1) % frame_size;
            misses++;
        }
        display_blocks(blocks, frame_size);
    }
    printf("Page Faults: %d\nHits: %d\nMiss Ratio: %.3f\nHit Ratio: %.3f\n", misses, hits, (float)misses / n, (float)hits/n);
}

void lru(int pages[], int n, int frame_size) 
{
    printf("\n-LRU Page Replacement-\n");
    int blocks[frame_size], misses = 0, hits = 0;
    int recent[frame_size];  

    for (int i = 0; i < frame_size; i++) 
    {
        blocks[i] = -1;  
        recent[i] = -1;  
    }

    for (int i = 0; i < n; i++) 
    {
        int found = 0, leastRecent = 0;

        for (int j = 0; j < frame_size; j++) 
        {
            if (blocks[j] == pages[i]) 
            {
                found = 1;  
                hits++;  
                recent[j] = i;
                break;
            }
        }

        if (!found) 
        {  
            for (int j = 1; j < frame_size; j++) 
            {
                if (recent[j] < recent[leastRecent]) 
                {
                    leastRecent = j;
                }
            }

            blocks[leastRecent] = pages[i];
            recent[leastRecent] = i;  
            misses++;
        }

        display_blocks(blocks, frame_size);
    }

    printf("Page Faults: %d\nHits: %d\nMiss Ratio: %.3f\nHit Ratio: %.3f\n", misses, hits, (float)misses/n, (float)hits/n);
}

int find_opt(int pages[], int blocks[], int frame_size, int currentIndex, int n) 
{
    int farthest = currentIndex, index = -1;
    for (int i = 0; i < frame_size; i++) 
    {
        int j;
        for (j = currentIndex; j < n; j++) 
        {
            if (blocks[i] == pages[j]) 
            {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n) 
        {
            return i;
        }
    }
    if(index==-1)
        return 0;
    return index;
}

void optimal(int pages[], int n, int frame_size) 
{
    printf("\n-Optimal Page Replacement-\n");
    int blocks[frame_size], misses = 0, hits = 0;

    for (int i = 0; i < frame_size; i++) blocks[i] = -1;

    for (int i = 0; i < n; i++) 
    {
        int found = 0;
        for (int j = 0; j < frame_size; j++) 
        {
            if (blocks[j] == pages[i]) 
            {
                found = 1;
                hits++;
                break;
            }
        }
        if (!found) 
        {
            if (i < frame_size) 
            {
                blocks[i] = pages[i];
            } 
            else 
            {
                int replacementIndex = find_opt(pages, blocks, frame_size, i + 1, n);
                blocks[replacementIndex] = pages[i];
            }
            misses++;
        }
        display_blocks(blocks, frame_size);
    }
    printf("Page Faults: %d\nHits: %d\nMiss Ratio: %.3f\nHit Ratio: %.3f\n", misses, hits, (float)misses/n, (float)hits/n);
}

int main() 
{
    int n, frame_size;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter page frame size: ");
    scanf("%d", &frame_size);

    fifo(pages, n, frame_size);
    lru(pages, n, frame_size);
    optimal(pages, n, frame_size);

    return 0;
}
