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
	PinCfg.Funcnum = 1;//设置管脚功能为串口功能
	PinCfg.Portnum = 0;//设置管脚端口号,GPIO0
	PinCfg.Pinnum = 3;//GPIO0_3
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	PinCfg.Pinnum = 2;//GPIO0_2
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	UARTConfigStruct.Baud_rate = Baud_rate;//设置波特率
	UARTConfigStruct.Databits=UART_DATABIT_8;//设置数据8位
	UARTConfigStruct.Parity=UART_PARITY_NONE;//无校验
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//设置停止位1位
	UART_Init(LPC_UART0, &UARTConfigStruct);//初始化结构体
	UART_TxCmd(LPC_UART0, ENABLE);//使能发送
	
	UART_IntConfig(LPC_UART0, UART_INTCFG_RBR, ENABLE);//设置接收中断
	NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));//设置优先级
	NVIC_EnableIRQ(UART0_IRQn);//智能终端

}




