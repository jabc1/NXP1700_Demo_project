#include "uart.h"
#include "stdio.h"
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




