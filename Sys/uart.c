#include "uart.h"
#include "stdio.h"

_Uart Uart0;

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


#define debug_print
#ifdef debug_print
struct __FILE 
{ 
	int handle; 

}; 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{      
	while (!(LPC_UART0->LSR & 0x20))
		;/*��bit5 0 Ϊ�����ݣ�1 Ϊ�������*/
    (LPC_UART0->THR = ch);    
	return ch;
}
#endif

