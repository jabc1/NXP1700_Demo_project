#include "uart.h"
#include "stdio.h"

_Uart Uart0;

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


#define debug_print
#ifdef debug_print
struct __FILE 
{ 
	int handle; 

}; 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{      
	while (!(LPC_UART0->LSR & 0x20))
		;/*读bit5 0 为有数据，1 为发送完成*/
    (LPC_UART0->THR = ch);    
	return ch;
}
#endif

