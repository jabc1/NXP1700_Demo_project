#include "uart.h"
#include "stdio.h"
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




