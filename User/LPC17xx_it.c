#include "LPC17xx_it.h"
#include "gpio.h"


/*********************************************************************************************************
������:void EINT0_IRQHandler()
��������: EINT0�ж�ͨ��������
����:��
����ֵ:��
*********************************************************************************************************/
void EINT0_IRQHandler()				
{
	;
}
void TIMER0_IRQHandler()
{
	static u8 flag = 0;
	flag = !flag;
	//if(((LPC_TIM0->IR) &(1<<0))==(1<<0))
	if(TIM_GetIntStatus(LPC_TIM0,TIM_MR0_INT)==SET)
	{
		if(flag)
		{
			SET_GPIO_H(LED1);
		}
		else
		{
			SET_GPIO_L(LED1);
		}
	}
	//LPC_TIM0->IR |=(1<<0);
	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);

}
/*********************************************************************************************************
������:void UART0_IRQHandler(void)
��������: ����0�ж�ͨ��������
����:��
����ֵ:��
*********************************************************************************************************/

void UART0_IRQHandler(void)
{
	u8 temp;
//	uint32_t flag;
	NVIC_ClearPendingIRQ(UART0_IRQn);
//	flag=UART_GetIntId(LPC_UART0);
//	flag=flag&0x0f;
//	if(flag==0x04)
//	{
		if((UART_GetLineStatus(LPC_UART0)&0x01))//��ȡLSRʱ�жϻᱻ���
		{
			temp = UART_ReceiveByte(LPC_UART0);
			Queue_Put(&Uart0,&temp);
		}
//	}
}



