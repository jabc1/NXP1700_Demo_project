#ifndef _uart_h
#define _uart_h
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"
#include "debug_frmwrk.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_nvic.h"
#include "stdio.h"
#include "fifo.h"
#include "queue_jk.h"

#define		UART_LEN		1024

#pragma pack(push,1)
typedef struct
{
	u16 len;
	u8 Rxbuff[UART_LEN];
	u8 Txbuff[UART_LEN];
}_Uart;
#pragma pack(pop)

extern _Uart Uart;
extern	QueueType Uart0;
extern	QueueType Uart1;

void Queue_init(void);
void Queue_test(void);
void uart_config0(uint32_t Baud_rate);
void uart_config2(uint32_t Baud_rate);

#endif

