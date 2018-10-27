#include "time.h"
#include "LPC17xx.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg.h"

void LPC_TIEM0_init()
{
//	LPC_SC->PCONP|= 1 << 1; 

//	LPC_TIM0-> TCR  = 0x02;
//	LPC_TIM0-> IR   = 1;
//	LPC_TIM0-> CTCR = 0;
//	LPC_TIM0-> TC   = 0;
//	LPC_TIM0-> PR   = 0;
//	LPC_TIM0-> MR0  = 1000-1;
//	LPC_TIM0-> MCR  = 0x03;

//	NVIC_EnableIRQ(TIMER0_IRQn);
//	NVIC_SetPriority(TIMER0_IRQn, 4);

//	LPC_TIM0-> TCR  = 0x01;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct;
		// Initialize timer, prescale count time of 1uS
		TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
		TIM_ConfigStruct.PrescaleValue	= 1000;
		TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);

		// use channel 0, MR0
		TIM_MatchConfigStruct.MatchChannel = 0;
		// Disable interrupt when MR0 matches the value in TC register
		TIM_MatchConfigStruct.IntOnMatch   = FALSE;
		//Enable reset on MR0: TIMER will reset if MR0 matches it
		TIM_MatchConfigStruct.ResetOnMatch = TRUE;
		//Stop on MR0 if MR0 matches it
		TIM_MatchConfigStruct.StopOnMatch  = FALSE;
		//Toggle MR0.0 pin if MR0 matches it
		TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
		// Set Match value
		TIM_MatchConfigStruct.MatchValue   = 500000/100;
		TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);

		TIM_Cmd(LPC_TIM0,ENABLE);
}




