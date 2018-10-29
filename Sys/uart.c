#include "uart.h"
#include "debugprint.h"
#include "queue.h"
_Uart Uart;
_Uart Uart2t;
QueueType Uart0;
QueueType Uart2;

void Queue_init()
{
	Queue_Init(&Uart0,Uart.Rxbuff,UART_LEN,1);
	Queue_Init(&Uart0,Uart.Txbuff,UART_LEN,1);
	Queue_Init(&Uart2,Uart2t.Rxbuff,UART_LEN,1);
	Queue_Init(&Uart2,Uart2t.Txbuff,UART_LEN,1);
}

void Queue_test()
{
	u8 temp;
	if(Queue_Query(&Uart0,&temp))
	{
		Uart.len=0;
		while(Queue_Get(&Uart0,&Uart.Txbuff[Uart.len++]))
			;
		Uart.Txbuff[Uart.len] = 0;
		printf("%s",Uart.Txbuff);
		memset(Uart.Txbuff,0,sizeof(Uart.Txbuff));
	}
	if(Queue_Query(&Uart2,&temp))
	{
		Uart2t.len=0;
		while(Queue_Get(&Uart2,&Uart2t.Txbuff[Uart2t.len++]))
			;
		Uart2t.Txbuff[Uart2t.len] = 0;
		USART2_Printf("%s",Uart2t.Txbuff);
		memset(Uart2t.Txbuff,0,sizeof(Uart2t.Txbuff));
	}
}

void uart_config0(uint32_t Baud_rate)
{
	
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 1;//���ùܽŹ���Ϊ���ڹ���
	PinCfg.Portnum = 0;//���ùܽŶ˿ں�,GPIO0
	PinCfg.Pinnum = 3;//GPIO0_3
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	PinCfg.Pinnum = 2;//GPIO0_2
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	
	UARTConfigStruct.Baud_rate = Baud_rate;//���ò�����
	UARTConfigStruct.Databits=UART_DATABIT_8;//��������8λ
	UARTConfigStruct.Parity=UART_PARITY_NONE;//��У��
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//����ֹͣλ1λ
	UART_Init(LPC_UART0, &UARTConfigStruct);//��ʼ���ṹ��
	
	UART_TxCmd(LPC_UART0, ENABLE);//ʹ�ܷ���
	
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);//���ý����ж�
	NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));//�������ȼ�
	NVIC_EnableIRQ(UART0_IRQn);//�����ն�

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
void uart_config2(uint32_t Baud_rate)
{
	
	UART_CFG_Type UARTConfigStruct;
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 1;//���ùܽŹ���Ϊ���ڹ���
	PinCfg.Portnum = 0;//���ùܽŶ˿ں�,GPIO0
	PinCfg.Pinnum = 10;
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);//��ʼ���ṹ��
	
	UARTConfigStruct.Baud_rate = Baud_rate;//���ò�����
	UARTConfigStruct.Databits=UART_DATABIT_8;//��������8λ
	UARTConfigStruct.Parity=UART_PARITY_NONE;//��У��
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//����ֹͣλ1λ
	UART_Init(LPC_UART2, &UARTConfigStruct);//��ʼ���ṹ��
	
	UART_TxCmd(LPC_UART2, ENABLE);//ʹ�ܷ���
	
	UART_IntConfig(LPC_UART2, UART_INTCFG_RBR, ENABLE);//���ý����ж�
	NVIC_SetPriority(UART2_IRQn, ((0x01<<3)|0x01));//�������ȼ�
	NVIC_EnableIRQ(UART2_IRQn);//�����ն�

}
/*********************************************************************************************************
������:void UART2_IRQHandler(void)
��������: ����2�ж�ͨ��������
����:��
����ֵ:��
*********************************************************************************************************/

void UART2_IRQHandler(void)
{
	u8 temp;
	NVIC_ClearPendingIRQ(UART2_IRQn);

	if((UART_GetLineStatus(LPC_UART2)&0x01))//��ȡLSRʱ�жϻᱻ���
	{
		temp = UART_ReceiveByte(LPC_UART2);
		Queue_Put(&Uart2,&temp);
	}
}










