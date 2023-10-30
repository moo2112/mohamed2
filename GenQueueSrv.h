#ifndef GENERIC_QUEUE_SERVICE_H
#define GENERIC_QUEUE_SERVICE_H

#ifndef STD_TYPES_H
  #include "StdTypes.h"
#endif

typedef struct
{
  U32 u32MaxSize;
  U32 u32ElementSizeInBytes;
  U32 u32CurrentSize;
  U32 u32Rear;
  U32 u32Front;
  U8  *pau8Elements;
} GQU_tstrQueueGen;


typedef struct
{
    U32 u32MaxSize;
    U32 u32CurrentSize;
    U32 u32Rear;
    U32 u32Front;
    U8  *pau8Elements;
} GQU_tstrU8Queue;

typedef struct
{
    U32 u32MaxSize;
    U32 u32CurrentSize;
    U32 u32Rear;
    U32 u32Front;
    U16 *pau16Elements;
} GQU_tstrU16Queue;

typedef struct
{
    U32 u32MaxSize;
    U32 u32CurrentSize;
    U32 u32Rear;
    U32 u32Front;
    U32 *pau32Elements;
} GQU_tstrU32Queue;

BOOL GQU_bGenQueueIsFull(GQU_tstrQueueGen *pstrQueue);
BOOL GQU_bGenQueueIsEmpty(GQU_tstrQueueGen *pstrQueue);
BOOL GQU_bGenQueueEnqueue(GQU_tstrQueueGen *pstrQueue, void* pvValue);
BOOL GQU_bGenQueueDequeue(GQU_tstrQueueGen *pstrQueue, void* pvValue);
BOOL GQU_bGenQueueGetItem(GQU_tstrQueueGen *pstrQueue, void* pvValue);
void GQU_vGenQueueMakeEmpty(GQU_tstrQueueGen *pstrQueue);
void GQU_vGenQueueInit( GQU_tstrQueueGen *pstrQueue, U32 u32MaxSize, U32 u32ElementSizeInBytes, U8* pau8Elements);


BOOL GQU_bGenQueueU8IsFull(GQU_tstrU8Queue *pstrU8Queue);
BOOL GQU_bGenQueueU8IsEmpty(GQU_tstrU8Queue *pstrU8Queue);
BOOL GQU_bGenQueueU8Enqueue(GQU_tstrU8Queue *pstrU8Queue, U8 u8Value);
BOOL GQU_bGenQueueU8Dequeue(GQU_tstrU8Queue *pstrU8Queue, U8 *pu8Value);
BOOL GQU_bGenQueueU8GetItem(GQU_tstrU8Queue *pstrU8Queue, U8 *pu8Value);
void GQU_vGenQueueU8MakeEmpty(GQU_tstrU8Queue *pstrU8Queue);
void GQU_vGenQueueU8Init( GQU_tstrU8Queue *pstrU8Queue, U32 u32MaxSize, U8  *pau8Elements);

BOOL GQU_bGenQueueU16IsFull(GQU_tstrU16Queue *pstrU16Queue);
BOOL GQU_bGenQueueU16IsEmpty(GQU_tstrU16Queue *pstrU16Queue);
BOOL GQU_bGenQueueU16Enqueue(GQU_tstrU16Queue *pstrU16Queue, U16 u16Value);
BOOL GQU_bGenQueueU16Dequeue(GQU_tstrU16Queue *pstrU16Queue, U16 *pu16Value);
BOOL GQU_bGenQueueU16GetItem(GQU_tstrU16Queue *pstrU16Queue, U16 *pu16Value);
void GQU_vGenQueueU16MakeEmpty(GQU_tstrU16Queue *pstrU16Queue);
void GQU_vGenQueueU16Init( GQU_tstrU16Queue *pstrU16Queue, U32 u32MaxSize, U16 *pau16Elements);

BOOL GQU_bGenQueueU32IsFull(GQU_tstrU32Queue *pstrU32Queue);
BOOL GQU_bGenQueueU32IsEmpty(GQU_tstrU32Queue *pstrU32Queue);
BOOL GQU_bGenQueueU32Enqueue(GQU_tstrU32Queue *pstrU32Queue, U32 u32Value);
BOOL GQU_bGenQueueU32Dequeue(GQU_tstrU32Queue *pstrU32Queue, U32 *pu32Value);
BOOL GQU_bGenQueueU32GetItem(GQU_tstrU32Queue *pstrU32Queue, U32 *pu32Value);
void GQU_vGenQueueU32MakeEmpty(GQU_tstrU32Queue *pstrU32Queue);
void GQU_vGenQueueU32Init( GQU_tstrU32Queue *pstrU32Queue, U32 u32MaxSize, U32 *pau32Elements);


#endif
