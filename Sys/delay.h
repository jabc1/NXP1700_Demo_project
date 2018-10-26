#ifndef _delay_h
#define _delay_h

#include "LPC17xx.h"
#include "lpc17xx_libcfg_default.h"

void delay_init(void);					  
void delay_ms (unsigned long tick);
void delay_us (unsigned long tick);



#endif

