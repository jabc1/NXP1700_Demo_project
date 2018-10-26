#include "LPC17xx_it.h"



/*********************************************************************************************************
函数名:void EINT0_IRQHandler()
函数功能: EINT0中断通道服务函数
参数:无
返回值:无
*********************************************************************************************************/
void EINT0_IRQHandler()				
{
	;
}
/*********************************************************************************************************
函数名:void UART0_IRQHandler(void)
函数功能: 串口0中断通道服务函数
参数:无
返回值:无
*********************************************************************************************************/

void UART0_IRQHandler(void)
{
	u8 temp;
	uint32_t flag;
	NVIC_ClearPendingIRQ(UART0_IRQn);
	flag=UART_GetIntId(LPC_UART0);
	flag=flag&0x0f;
	if(flag==0x04)
	{
		if((UART_GetLineStatus(LPC_UART0)&0x01))//读取LSR时中断会被清除
		{
			temp = UART_ReceiveByte(LPC_UART0);
			Queue_Put(&Uart0,&temp);
		}
	}
}



