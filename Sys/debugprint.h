#ifndef _debugprint_h
#define _debugprint_h
#include "LPC17xx.h"

void RS485_Send_Data(char *buf,uint32_t len);
void USART2_Printf(const char *fmt, ...);
#endif


