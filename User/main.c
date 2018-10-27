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
#include "runflag.h"
extern void LPC_TIEM0_init(void);
static u8 flag=0;
int main(void)
{
	SystemInit();
	delay_init();
	uart_config0(115200);
	LPC_GPIO_init();
	LPC_TIEM0_init();
	RunFlagInit();
	Queue_init();
	
	while(1)
	{
		RunFlagHandler();
		if(RunFlag.Hz100)
		{
			Queue_test();
		}
		if(RunFlag.Hz1)
		{
			printf("test runflag test");
		}
		if(RunFlag.Hz4)
		{
			flag=!flag;
			if(flag)
			{
				SET_GPIO_H(LED2);
			}
			else
			{
				SET_GPIO_L(LED2);
			}
		}

	}
}



//中断服务函数，放在LPC17xx_it.C文件中
/******************************************************************************
                           End Of File
******************************************************************************/





