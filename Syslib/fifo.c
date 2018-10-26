#include "fifo.h"

/*!
 * @file fifo.c
 * @brief 实现缓存机制
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */

static uint16_t FifoNext( Fifo_t *fifo, uint16_t index )
{
    return ( index + 1 ) % fifo->Size;
}

void FifoInit( Fifo_t *fifo, uint8_t *buffer, uint16_t size )
{
    fifo->Begin = 0;
    fifo->End = 0;
    fifo->Data = buffer;
    fifo->Size = size;
}

void FifoPush( Fifo_t *fifo, uint8_t data )
{
    fifo->End = FifoNext( fifo, fifo->End );
    fifo->Data[fifo->End] = data;
}

uint8_t FifoPop( Fifo_t *fifo )
{
    uint8_t data = fifo->Data[FifoNext( fifo, fifo->Begin )];

    fifo->Begin = FifoNext( fifo, fifo->Begin );
    return data;
}

void FifoFlush( Fifo_t *fifo )
{
    fifo->Begin = 0;
    fifo->End = 0;
}

bool IsFifoEmpty( Fifo_t *fifo )
{
    return (bool)( fifo->Begin == fifo->End );
}

bool IsFifoFull( Fifo_t *fifo )
{
    return (bool)( FifoNext( fifo, fifo->End ) == fifo->Begin );
}






