//#include "StdTypes.h"
//#include "Extern.h"
 // #include "BBAssert.h"
//#include "Alloc.h"
#include "GenQueueSrv.h"
#include "StdTypes.h"
static const S8 *pks8FileName = __FILE__;

/* Gen Implementation */
/**********************/
BOOL GQU_bGenQueueIsFull(GQU_tstrQueueGen *pstrQueue)
{
  BOOL bStatus;

  if(pstrQueue->u32CurrentSize == pstrQueue->u32MaxSize)
  {
    bStatus = TRUE;
  }
  else
  {
    bStatus = FALSE;
  }

  return bStatus;
}

BOOL GQU_bGenQueueIsEmpty(GQU_tstrQueueGen *pstrQueue)
{
  BOOL bStatus;

  if(pstrQueue->u32CurrentSize == (U16)0)
  {
    bStatus = TRUE;
  }
  else
  {
    bStatus = FALSE;
  }

  return bStatus;
}

BOOL GQU_bGenQueueEnqueue(GQU_tstrQueueGen *pstrQueue, void* pvValue)
{
  U32  u32Index;
  BOOL bStatus = TRUE;
  U32  *pau32Data = (U32*) pvValue;
  U32  u32TempElementSizeInBytes;
  U32  *pau32TempElements;
  U32  u32TempMaxSize = pstrQueue->u32MaxSize;

  // BAS_ASSERT((pstrQueue->pau8Elements != NULL), pks8FileName);  /*Check if the queue is Full*/
  if(pstrQueue->u32CurrentSize == u32TempMaxSize)
  {
    bStatus = FALSE;
  }
  else
  {
    u32TempElementSizeInBytes = pstrQueue->u32ElementSizeInBytes;
    pau32TempElements = (U32 *)&pstrQueue->pau8Elements[pstrQueue->u32Front];
    /* Loop to enqueue the element*/
    for (u32Index = (U32)0; u32Index < (u32TempElementSizeInBytes / 4); u32Index++)
    {
      pau32TempElements[u32Index] = pau32Data[u32Index];
    }
    /*increment the number of elements*/
    pstrQueue->u32CurrentSize += u32TempElementSizeInBytes;

    pstrQueue->u32Front += u32TempElementSizeInBytes;
    /* circulate the front if needed */
    if(pstrQueue->u32Front == u32TempMaxSize)
    {
      pstrQueue->u32Front = (U16)0;
    }
    //BAS_ASSERT(((&pstrQueue->pau8Elements[pstrQueue->u32Front]) < (pstrQueue->pau8Elements +  u32TempMaxSize )), pks8FileName);
  }
  return bStatus;
}

BOOL GQU_bGenQueueDequeue(GQU_tstrQueueGen *pstrQueue, void* pvValue)
{
  BOOL bStatus = TRUE;
  U32 u32Index;
  U32* pau32Data = (U32*) pvValue;
  U32 u32TempElementSizeInBytes;
  U32 *pau32TempElements;
  U32  u32TempMaxSize = pstrQueue->u32MaxSize;

  //BAS_ASSERT((pstrQueue->pau8Elements != NULL), pks8FileName);
  /*Check if the queue is Empty*/
  if(pstrQueue->u32CurrentSize == (U16)0)
  {
    bStatus = FALSE;
  }
  else
  {
    u32TempElementSizeInBytes = pstrQueue->u32ElementSizeInBytes;

    pau32TempElements = (U32 *)&pstrQueue->pau8Elements[pstrQueue->u32Rear];
    /*loop to dequeue the element*/
    for (u32Index = (U32)0; u32Index < (u32TempElementSizeInBytes / 4); u32Index++)
    {
      pau32Data[u32Index] = pau32TempElements[u32Index];
    }
    /*Decrement the number of elements*/
    pstrQueue->u32CurrentSize -= u32TempElementSizeInBytes;
    pstrQueue->u32Rear += u32TempElementSizeInBytes;
    /* circulate the front if needed */
    if(pstrQueue->u32Rear == u32TempMaxSize)
    {
      pstrQueue->u32Rear = (U32)0;
    }
    //BAS_ASSERT(((&pstrQueue->pau8Elements[pstrQueue->u32Rear]) < (pstrQueue->pau8Elements +  u32TempMaxSize)), pks8FileName);
  }

  return bStatus;
}

BOOL GQU_bGenQueueGetItem(GQU_tstrQueueGen *pstrQueue, void* pvValue)
{
  BOOL bStatus = TRUE;
  U32 u32Index;
  U32* pau32Data = (U32*) pvValue;
  U32 u32TempElementSizeInBytes;
  U32 *pau32TempElements;

  //BAS_ASSERT((pstrQueue->pau8Elements != NULL), pks8FileName);

  /*Check if the queue is Empty*/
  if(pstrQueue->u32CurrentSize == (U16)0)
  {
    bStatus = FALSE;
  }
  else
  {
    u32TempElementSizeInBytes = pstrQueue->u32ElementSizeInBytes;
    pau32TempElements = (U32 *)&pstrQueue->pau8Elements[pstrQueue->u32Rear];
    /*loop to get the element without deleting it*/
    for (u32Index = (U32)0; u32Index < (u32TempElementSizeInBytes / 4); u32Index++)
    {
      pau32Data[u32Index] = pau32TempElements[u32Index];
    }
  }

  return bStatus;
}

void GQU_vGenQueueMakeEmpty(GQU_tstrQueueGen *pstrQueue)
{
  pstrQueue->u32CurrentSize = (U16)0;
  pstrQueue->u32Rear = (U16)0;
  pstrQueue->u32Front = (U16)0;
}

void GQU_vGenQueueInit( GQU_tstrQueueGen *pstrQueue, U32 u32MaxSize, U32 u32ElementSizeInBytes, U8* pau8Elements)
{
  //BAS_ASSERT((pau8Elements != NULL), pks8FileName);
  //BAS_ASSERT((U32)(u32ElementSizeInBytes % (U32)4) == (U32)0, pks8FileName);

  pstrQueue->u32MaxSize = u32MaxSize;
  pstrQueue->u32ElementSizeInBytes = u32ElementSizeInBytes;
  pstrQueue->pau8Elements = pau8Elements;
  pstrQueue->u32CurrentSize = (U16)0;
  pstrQueue->u32Rear = (U16)0;
  pstrQueue->u32Front = (U16)0;
}


/* U8 Implementation */
/*********************/
BOOL GQU_bGenQueueU8IsFull(GQU_tstrU8Queue *pstrU8Queue)
{
    BOOL bStatus;

    if(pstrU8Queue->u32CurrentSize == pstrU8Queue->u32MaxSize)
    {
        bStatus = TRUE;
    }
    else
    {
        bStatus = FALSE;
    }

    return bStatus;
}

BOOL GQU_bGenQueueU8IsEmpty(GQU_tstrU8Queue *pstrU8Queue)
{
    BOOL bStatus;

    if(pstrU8Queue->u32CurrentSize == (U16)0)
    {
        bStatus = TRUE;
    }
    else
    {
        bStatus = FALSE;
    }

    return bStatus;
}

BOOL GQU_bGenQueueU8Enqueue(GQU_tstrU8Queue *pstrU8Queue, U8 u8Value)
{
    BOOL bStatus = TRUE;
    U32  u32TempMaxSize = pstrU8Queue->u32MaxSize;

    //BAS_ASSERT((pstrU8Queue->pau8Elements != NULL), pks8FileName);
    /*Check if the queue is Full*/
    if(pstrU8Queue->u32CurrentSize == u32TempMaxSize)
    {
        bStatus = FALSE;
    }
    else
    {
        /* Enqueue the element*/
        pstrU8Queue->pau8Elements[pstrU8Queue->u32Front] = u8Value;
        /*increment the number of elements*/
        pstrU8Queue->u32CurrentSize++;

        /* circulate the front if needed or Increment the Front*/
        pstrU8Queue->u32Front++;
        if(pstrU8Queue->u32Front == u32TempMaxSize)
        {
            pstrU8Queue->u32Front = 0;
        }
        else
        {
          /**/
        }
        //BAS_ASSERT(((&pstrU8Queue->pau8Elements[pstrU8Queue->u32Front]) < (pstrU8Queue->pau8Elements +  u32TempMaxSize)), pks8FileName);
    }

    return bStatus;
}

BOOL GQU_bGenQueueU8Dequeue(GQU_tstrU8Queue *pstrU8Queue, U8 *pu8Value)
{
    BOOL bStatus = TRUE;
    U32  u32TempMaxSize = pstrU8Queue->u32MaxSize;

    //BAS_ASSERT((pstrU8Queue->pau8Elements != NULL), pks8FileName);
    /*Check if the queue is Empty*/
    if(pstrU8Queue->u32CurrentSize == (U16)0)
    {
        bStatus = FALSE;
    }
    else
    {
        /*dequeue the element*/
        *pu8Value = pstrU8Queue->pau8Elements[pstrU8Queue->u32Rear];
        /*Decrement the number of elements*/
        pstrU8Queue->u32CurrentSize--;

        /*Circulate the rear if needed or increment it*/
        pstrU8Queue->u32Rear++;
        if(pstrU8Queue->u32Rear == pstrU8Queue->u32MaxSize)
        {
            pstrU8Queue->u32Rear = 0;
        }
        else
        {
          /**/
        }
        //BAS_ASSERT(((&pstrU8Queue->pau8Elements[pstrU8Queue->u32Rear]) < (pstrU8Queue->pau8Elements +  u32TempMaxSize )), pks8FileName);
    }

    return bStatus;
}

BOOL GQU_bGenQueueU8GetItem(GQU_tstrU8Queue *pstrU8Queue, U8 *pu8Value)
{
  BOOL bStatus = TRUE;

  //BAS_ASSERT((pstrU8Queue->pau8Elements != NULL), pks8FileName);

    /*Check if the queue is Empty*/
    if(pstrU8Queue->u32CurrentSize == (U16)0)
    {
        bStatus = FALSE;
    }
    else
    {
        /* get the element without deleting it*/
        *pu8Value = pstrU8Queue->pau8Elements[pstrU8Queue->u32Rear];
    }

    return bStatus;
}

void GQU_vGenQueueU8MakeEmpty(GQU_tstrU8Queue *pstrU8Queue)
{
    pstrU8Queue->u32CurrentSize = (U16)0;
    pstrU8Queue->u32Rear = (U16)0;
    pstrU8Queue->u32Front = (U16)0;
}

void GQU_vGenQueueU8Init( GQU_tstrU8Queue *pstrU8Queue, U32 u32MaxSize, U8  *pau8Elements)
{
  //BAS_ASSERT((pau8Elements != NULL), pks8FileName);

  pstrU8Queue->u32MaxSize = u32MaxSize;
  pstrU8Queue->pau8Elements = pau8Elements;
  pstrU8Queue->u32CurrentSize = (U16)0;
  pstrU8Queue->u32Rear = (U16)0;
  pstrU8Queue->u32Front = (U16)0;
}

/* U16 Implementation */
/*********************/
BOOL GQU_bGenQueueU16IsFull(GQU_tstrU16Queue *pstrU16Queue)
{
    BOOL bStatus;

    if(pstrU16Queue->u32CurrentSize == pstrU16Queue->u32MaxSize)
    {
        bStatus = TRUE;
    }
    else
    {
        bStatus = FALSE;
    }

    return bStatus;
}

BOOL GQU_bGenQueueU16IsEmpty(GQU_tstrU16Queue *pstrU16Queue)
{
    BOOL bStatus;

    if(pstrU16Queue->u32CurrentSize == (U16)0)
    {
        bStatus = TRUE;
    }
    else
    {
        bStatus = FALSE;
    }

    return bStatus;
}

BOOL GQU_bGenQueueU16Enqueue(GQU_tstrU16Queue *pstrU16Queue, U16 u16Value)
{
    BOOL bStatus = TRUE;
    U32  u32TempMaxSize = pstrU16Queue->u32MaxSize;
    U8 *pu8temp = (U8 *)pstrU16Queue->pau16Elements;
    U16 *pu16val;

    /*Check if the queue is Full*/
    if(pstrU16Queue->u32CurrentSize == u32TempMaxSize)
    {
        bStatus = FALSE;
    }
    else
    {
        /* Enqueue the element*/
        pu16val = &pu8temp[pstrU16Queue->u32Front];
        *pu16val=u16Value;
        /*increment the number of elements*/
        pstrU16Queue->u32CurrentSize += 2;

        /* circulate the front if needed or Increment the Front*/
        pstrU16Queue->u32Front+=2;
        if((pstrU16Queue->u32Front) == u32TempMaxSize)
        {
            pstrU16Queue->u32Front = 0;
        }
        else
        {
          /**/
        }
        //BAS_ASSERT(((&pstrU16Queue->pau16Elements[pstrU16Queue->u32Front]) < (pstrU16Queue->pau16Elements +  u32TempMaxSize)), pks8FileName);
    }
    u32TempMaxSize*2;
    return bStatus;
}

BOOL GQU_bGenQueueU16Dequeue(GQU_tstrU16Queue *pstrU16Queue, U16 *pu16Value)
{
    BOOL bStatus = TRUE;
    U32  u32TempMaxSize = pstrU16Queue->u32MaxSize;
    U8 *pu8TempPtr = (U8*)pstrU16Queue->pau16Elements;
    U16 *pU16val;

    //BAS_ASSERT((pstrU16Queue->pau16Elements != NULL), pks8FileName);
    /*Check if the queue is Empty*/
    if(pstrU16Queue->u32CurrentSize == (U16)0)
    {
        bStatus = FALSE;
    }
    else
    {
        /*dequeue the element*/
        //*pu16Value = pstrU16Queue->pau16Elements[pstrU16Queue->u32Rear];
        pU16val = &pu8TempPtr[pstrU16Queue->u32Rear];
        *pu16Value = *pU16val;
        /*Decrement the number of elements*/
        pstrU16Queue->u32CurrentSize -= 2;

        /*Circulate the rear if needed or increment it*/
        pstrU16Queue->u32Rear++;
        if((pstrU16Queue->u32Rear * 2) == u32TempMaxSize)
        {
            pstrU16Queue->u32Rear = 0;
        }
        else
        {
          /**/
        }
        //BAS_ASSERT(((&pstrU16Queue->pau16Elements[pstrU16Queue->u32Rear]) < (pstrU16Queue->pau16Elements +  u32TempMaxSize )), pks8FileName);
    }

    return bStatus;
}

BOOL GQU_bGenQueueU16GetItem(GQU_tstrU16Queue *pstrU16Queue, U16 *pu16Value)
{
    BOOL bStatus = TRUE;

    //BAS_ASSERT((pstrU16Queue->pau16Elements != NULL), pks8FileName);
    /*Check if the queue is Empty*/
    if(pstrU16Queue->u32CurrentSize == (U16)0)
    {
        bStatus = FALSE;
    }
    else
    {
        /*get the element without deleting it*/
        *pu16Value = pstrU16Queue->pau16Elements[pstrU16Queue->u32Rear];
    }

    return bStatus;
}

void GQU_vGenQueueU16MakeEmpty(GQU_tstrU16Queue *pstrU16Queue)
{
    pstrU16Queue->u32CurrentSize = (U16)0;
    pstrU16Queue->u32Rear = (U16)0;
    pstrU16Queue->u32Front = (U16)0;
}

void GQU_vGenQueueU16Init( GQU_tstrU16Queue *pstrU16Queue, U32 u32MaxSize, U16 *pau16Elements)
{
  //BAS_ASSERT((pau16Elements != NULL), pks8FileName);
  pstrU16Queue->u32MaxSize = u32MaxSize;
  pstrU16Queue->pau16Elements = pau16Elements;
  pstrU16Queue->u32CurrentSize = (U16)0;
  pstrU16Queue->u32Rear = (U16)0;
  pstrU16Queue->u32Front = (U16)0;
}

/* U32 Implementation */
/*********************/
BOOL GQU_bGenQueueU32IsFull(GQU_tstrU32Queue *pstrU32Queue)
{
    BOOL bStatus;

    if(pstrU32Queue->u32CurrentSize == pstrU32Queue->u32MaxSize)
    {
        bStatus = TRUE;
    }
    else
    {
        bStatus = FALSE;
    }

    return bStatus;
}

BOOL GQU_bGenQueueU32IsEmpty(GQU_tstrU32Queue *pstrU32Queue)
{
    BOOL bStatus;

    if(pstrU32Queue->u32CurrentSize == (U16)0)
    {
        bStatus = TRUE;
    }
    else
    {
        bStatus = FALSE;
    }

    return bStatus;
}

BOOL GQU_bGenQueueU32Enqueue(GQU_tstrU32Queue *pstrU32Queue, U32 u32Value)
{
    BOOL bStatus = TRUE;
    U32  u32TempMaxSize = pstrU32Queue->u32MaxSize;
    U8 * pu8TempPtr = (U8 *)pstrU32Queue->pau32Elements;
    U32 * pu32val;

    /*Check if the queue is Full*/
    if(pstrU32Queue->u32CurrentSize == u32TempMaxSize)
    {
        bStatus = FALSE;
    }
    else
    {
        //printf("Add: %p\n", &pstrU32Queue->pau32Elements[pstrU32Queue->u32Front]);
        /* Enqueue the element*/
        pu32val = &pu8TempPtr[pstrU32Queue->u32Front];
        *pu32val = u32Value;
        /*increment the number of elements*/
        pstrU32Queue->u32CurrentSize += 4;

        /* circulate the front if needed or Increment the Front*/
        pstrU32Queue->u32Front += 4;
        if((pstrU32Queue->u32Front ) == u32TempMaxSize)
        {
            pstrU32Queue->u32Front = 0;
        }
        else
        {
          /**/
        }
        //BAS_ASSERT(((&pstrU32Queue->pau32Elements[pstrU32Queue->u32Front]) < (pstrU32Queue->pau32Elements +  u32TempMaxSize)), pks8FileName);
    }

    return bStatus;
}

BOOL GQU_bGenQueueU32Dequeue(GQU_tstrU32Queue *pstrU32Queue, U32 *pu32Value)
{
    BOOL bStatus = TRUE;
    U32  u32TempMaxSize = pstrU32Queue->u32MaxSize;
    U8 * pu8TempPtr = (U8 *)pstrU32Queue->pau32Elements;
    U32 * pu32val;

    //BAS_ASSERT((pstrU32Queue->pau32Elements != NULL), pks8FileName);
    /*Check if the queue is Empty*/
    if(pstrU32Queue->u32CurrentSize == (U16)0)
    {
        bStatus = FALSE;
    }
    else
    {
        /*dequeue the element*/
        //*pu32Value = pu8TempPtr[pstrU32Queue->u32Rear];
         //pstrU32Queue->pau32Elements = (U8*)pstrU32Queue->pau32Elements;
         pu32val = &pu8TempPtr[pstrU32Queue->u32Rear];
         *pu32Value = *pu32val;
        /*Decrement the number of elements*/
        pstrU32Queue->u32CurrentSize -= 4;

        /*Circulate the rear if needed or increment it*/
        pstrU32Queue->u32Rear += 4;
        if((pstrU32Queue->u32Rear) == u32TempMaxSize)
        {
            pstrU32Queue->u32Rear = 0;
        }
        else
        {
          /**/
        }
        //BAS_ASSERT(((&pstrU32Queue->pau32Elements[pstrU32Queue->u32Rear]) < (pstrU32Queue->pau32Elements +  u32TempMaxSize )), pks8FileName);
    }

    return bStatus;
}

BOOL GQU_bGenQueueU32GetItem(GQU_tstrU32Queue *pstrU32Queue, U32 *pu32Value)
{
    BOOL bStatus = TRUE;
    U8 * pu8TempPtr = (U8 *)pstrU32Queue->pau32Elements;
    U32 * pu32val;

    //BAS_ASSERT((pstrU32Queue->pau32Elements != NULL), pks8FileName);
    /*Check if the queue is Empty*/
    if(pstrU32Queue->u32CurrentSize == (U16)0)
    {
        bStatus = FALSE;
    }
    else
    {
        /*get the element without deleting it*/
        pu32val = &pu8TempPtr[pstrU32Queue->u32Rear];
        *pu32Value = *pu32val;
    }

    return bStatus;
}

void GQU_vGenQueueU32MakeEmpty(GQU_tstrU32Queue *pstrU32Queue)
{
    pstrU32Queue->u32CurrentSize = (U16)0;
    pstrU32Queue->u32Rear = (U16)0;
    pstrU32Queue->u32Front = (U16)0;
}

void GQU_vGenQueueU32Init( GQU_tstrU32Queue *pstrU32Queue, U32 u32MaxSize, U32 *pau32Elements)
{
  //BAS_ASSERT((pau32Elements != NULL), pks8FileName);
  pstrU32Queue->u32MaxSize = u32MaxSize;
  pstrU32Queue->pau32Elements = pau32Elements;
  pstrU32Queue->u32CurrentSize = (U16)0;
  pstrU32Queue->u32Rear = (U16)0;
  pstrU32Queue->u32Front = (U16)0;
}
