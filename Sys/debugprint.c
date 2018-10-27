#include "uart.h"
#include "stdio.h"
#include <stdarg.h>
#include <string.h>
#include "uart.h"
#include "debugprint.h"

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

void RS485_Send_Data(char *buf,uint32_t len)
{
	uint16_t  t;
	for(t=0;t<len;t++)
	{
		while (!(LPC_UART2->LSR & 0x20));
		(LPC_UART2->THR = buf[t]); 
	}    
	while (!(LPC_UART2->LSR & 0x20));
}

void USART2_Printf(const char *fmt, ...)
{
	char Buff[256];
	va_list ap;      
	va_start(ap, fmt);  
	vsprintf(Buff, fmt, ap);
	va_end(ap);
	RS485_Send_Data(Buff,strlen(Buff));
}







