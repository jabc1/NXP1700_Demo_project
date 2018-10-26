#include "delay.h"
/************************** PRIVATE VARIABLES *************************/
/* SysTick Counter */
volatile unsigned long SysTickCnt;

/************************** PRIVATE FUNCTIONS *************************/
void SysTick_Handler (void);

void delay_ms (unsigned long tick);

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		SysTick handler sub-routine (1ms)
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void SysTick_Handler (void)
{
  SysTickCnt++;
}

void delay_init(void)
{
	SysTick_Config(SystemCoreClock/1000 - 1); /* Generate interrupt each 1 ms   */
}
/*-------------------------PRIVATE FUNCTIONS------------------------------*/
/*********************************************************************//**
 * @brief		Delay function
 * @param[in]	tick - number milisecond of delay time
 * @return 		None
 **********************************************************************/
void delay_ms (unsigned long tick) 
{
  unsigned long systickcnt;

  systickcnt = SysTickCnt;
  while ((SysTickCnt - systickcnt) < tick);
}

void delay_us (unsigned long zms) 
{
 	unsigned long i,j;
	for(j=zms;j>0;j--)
		for(i=20;i>0;i--);
}



