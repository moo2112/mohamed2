#include <stdio.h>
#include <stdlib.h>
#include "GenQueueSrv.h"
#include "StdTypes.h"
#include<time.h>

void delay(int number_of_seconds)
{
    int milli_second = number_of_seconds;
    clock_t start_time = clock();
    while(start_time+milli_second > clock());
}

GQU_tstrU32Queue strU32Queue;
U32 ENbuffer[1000];
U32 TestENbuffer[1000000];
U32 ENbufferIndex = 0;
U32 TestDEbuffer[1000000];
U32 DEbufferIndex = 0;
U32 u32RandNum;
U32 u32ChecckCounter;
U32 u32LoopCounter;
int random;
int i;
int j;
int main()
{
    BOOL bCheck;
    GQU_vGenQueueU32Init(&strU32Queue,sizeof(ENbuffer),&ENbuffer);
    while(1)
    {
        random = rand();
        for (i=0; i<random; i++)
        {
           // printf("Element[%d] = %d\n", i,rand());
          u32RandNum = rand();
          bCheck = GQU_bGenQueueU32Enqueue(&strU32Queue, u32RandNum);
          if(bCheck == TRUE)
          {
              TestENbuffer[ENbufferIndex] = u32RandNum;
              ENbufferIndex++;
          }
          //delay(100);
        }
        printf("Enqueue size: %d\n", strU32Queue.u32CurrentSize);
        printf("%d\n", ENbufferIndex);

        random = rand();
        for (j=0;j<random;j++)
        {
            u32RandNum = 0;
            bCheck = GQU_bGenQueueU32Dequeue(&strU32Queue, &u32RandNum);
    //    printf("Element dequeue [%d] = %d\n",j,DEbuffer[j]);
            if(bCheck == TRUE)
            {
                TestDEbuffer[DEbufferIndex] = u32RandNum;
                DEbufferIndex++;
            }
        }
        printf("%d\n", strU32Queue.u32CurrentSize);
        delay(100);
        if(ENbufferIndex < DEbufferIndex)
        {
            u32ChecckCounter = ENbufferIndex;
        }
        else
        {
            u32ChecckCounter = DEbufferIndex;
        }
        for(u32LoopCounter = 0; u32LoopCounter < u32ChecckCounter; u32LoopCounter++)
        {
            if(TestENbuffer[u32LoopCounter] != TestDEbuffer[u32LoopCounter])
            {
               printf("False\n");
               break;
            }
        }
    }

    return 0;
}
