#include "queue_f.h"

_Uart3	Uart3f;
struct fifo_data	Uart3;

void fifo_init1()
{
	fifo_Init(&Uart3,Uart3f.Rxbuff,sizeof(Uart3f.Rxbuff));
	fifo_Init(&Uart3,Uart3f.Txbuff,sizeof(Uart3f.Txbuff));
}













