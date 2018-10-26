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

#define		UART_LEN		256
#pragma pack(push,1)
typedef struct
{
	u8 Rxbuff[UART_LEN];
	u8 Txbuff[UART_LEN];
	u16 len;
}_Uart;
#pragma pack(pop)

extern _Uart Uart0;


void uart_config0(uint32_t Baud_rate);


#endif

