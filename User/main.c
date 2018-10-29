#include "LPC17xx.h"
#include "debugprint.h"
#include "system_LPC17xx.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "fifo.h"
#include "queue_jk.h"
#include "timexx.h"
#include "runflag.h"
#include "esp8266.h"
#include  "queue.h"

static u8 flag=0;
int main(void)
{
	SystemInit();
	delay_init();
	LPC_GPIO_init();
	LPC_TIEM0_init();
	uart_config0(115200);
	uart_config2(115200);
	RunFlagInit();
	Queue_init();
//	esp8266_softreset();
//	esp8266_init();
	//esp8266_softreset();
	while(1)
	{
		RunFlagHandler();
		if(RunFlag.Hz10)
		{
			//Queue_test();
		}
		if(RunFlag.Hz1)
		{
			flag=!flag;
			if(flag)
			{
				SET_GPIO_H(LED2);
//				esp_8266_send_cmd("printfuart2\r\n","OK",200);
//				printf("mac=%s\r\n",Idinfo.macbuff);
			}
			else
			{
				SET_GPIO_L(LED2);
			}
		}

	}
}


/******************************************************************************
                           End Of File
******************************************************************************/





