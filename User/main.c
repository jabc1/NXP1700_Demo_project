#include "LPC17xx.h"
#include "system_LPC17xx.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "fifo.h"
#include "queue_jk.h"
#include "time.h"
extern void LPC_TIEM0_init(void);


int main(void)
{
	SystemInit();
	delay_init();
	uart_config0(115200);
	LPC_GPIO_init();
	LPC_TIEM0_init();
	Queue_init();
	while(1)
	{
//		SET_GPIO_H(LED1);
//		delay_ms(500);
//		SET_GPIO_L(LED1);
//		delay_ms(500);
//		printf("test\r\n");
		Queue_test();
		delay_ms(150);

	}
}



//中断服务函数，放在LPC17xx_it.C文件中
/******************************************************************************
                           End Of File
******************************************************************************/





