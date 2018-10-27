#include "gpio.h"

u32 status ;
void LPC_GPIO_init()
{
	SET_GPIO_OUT(LED1);
	SET_GPIO_OUT(LED2);
	SET_GPIO_OUT(LED3);
	SET_GPIO_OUT(LED4);
}
void GPIO_Toggle()
{
	;
}




