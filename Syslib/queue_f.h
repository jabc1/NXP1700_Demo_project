#ifndef _queue_f_h
#define _queue_f_h

#include "queue.h"
#include "debugprint.h"

#define		LEN3		512


#pragma pack(push,1)
typedef struct
{
	u8	Rxbuff[LEN3];
	u8  Txbuff[LEN3];
	u16 len3;
}_Uart3;
#pragma pack(pop)
extern _Uart3	Uart3f;
extern struct fifo_data	Uart3;

void fifo_init(void);



#endif

