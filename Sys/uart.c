#include "uart.h"

_Uart Uart;
QueueType Uart0;
QueueType Uart1;

void Queue_init()
{
	Queue_Init(&Uart0,Uart.Rxbuff,UART_LEN,2);
	Queue_Init(&Uart0,Uart.Txbuff,UART_LEN,2);
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
		printf("re=%s\r\n",Uart.Txbuff);
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




