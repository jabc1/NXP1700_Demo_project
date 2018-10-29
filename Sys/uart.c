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
/*********************************************************************************************************
函数名:void UART0_IRQHandler(void)
函数功能: 串口0中断通道服务函数
参数:无
返回值:无
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
		if((UART_GetLineStatus(LPC_UART0)&0x01))//读取LSR时中断会被清除
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
	PinCfg.Funcnum = 1;//设置管脚功能为串口功能
	PinCfg.Portnum = 0;//设置管脚端口号,GPIO0
	PinCfg.Pinnum = 10;
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);//初始化结构体
	
	UARTConfigStruct.Baud_rate = Baud_rate;//设置波特率
	UARTConfigStruct.Databits=UART_DATABIT_8;//设置数据8位
	UARTConfigStruct.Parity=UART_PARITY_NONE;//无校验
	UARTConfigStruct.Stopbits=UART_STOPBIT_1;//设置停止位1位
	UART_Init(LPC_UART2, &UARTConfigStruct);//初始化结构体
	
	UART_TxCmd(LPC_UART2, ENABLE);//使能发送
	
	UART_IntConfig(LPC_UART2, UART_INTCFG_RBR, ENABLE);//设置接收中断
	NVIC_SetPriority(UART2_IRQn, ((0x01<<3)|0x01));//设置优先级
	NVIC_EnableIRQ(UART2_IRQn);//智能终端

}
/*********************************************************************************************************
函数名:void UART2_IRQHandler(void)
函数功能: 串口2中断通道服务函数
参数:无
返回值:无
*********************************************************************************************************/

void UART2_IRQHandler(void)
{
	u8 temp;
	NVIC_ClearPendingIRQ(UART2_IRQn);

	if((UART_GetLineStatus(LPC_UART2)&0x01))//读取LSR时中断会被清除
	{
		temp = UART_ReceiveByte(LPC_UART2);
		Queue_Put(&Uart2,&temp);
	}
}










