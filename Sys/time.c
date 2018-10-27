#include "time.h"

#include "LPC17xx.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg.h"

void LPC_TIEM0_init()//1ms
{
	
	LPC_SC->PCONP|= 1 << 1; //开启定时器0功率控制

	LPC_TIM0-> TCR  = 0x02;//时能定时器
	LPC_TIM0-> IR   = 1;//
	LPC_TIM0-> CTCR = 0;
	LPC_TIM0-> TC   = 0;
	LPC_TIM0-> PR   = 4;
	LPC_TIM0-> MR0  = 5000-1;
	LPC_TIM0-> MCR  = 0x03;

	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_SetPriority(TIMER0_IRQn, 4);

	LPC_TIM0-> TCR  = 0x01;
//	TIM_SET timParstruct;
//	timParstruct.Mode = TIM_TIMER_MODE; //工作模式
//	timParstruct.CapCtrl = ENABLE;//清除中断
//	timParstruct.InitValue = 5000;//重装载值
//	timParstruct.Prescaler = 1;//分频系数
//	
//	timParstruct.MatchOut = 100;
//	timParstruct.MatchSet=100;
//	timParstruct.TimValue = 10000;
//	
//	timParstruct.CaptureSet =0;
//	timParstruct.IntClear = 0;
//	TIM32Init(0,&timParstruct);
	

}

/******************************************************************************************************** 
* Variable Definition                            
********************************************************************************************************/
static LPC_TIM_TypeDef(* const LPC_TIM[4]) = {LPC_TIM0, LPC_TIM1, LPC_TIM2, LPC_TIM3};						  

/******************************************************************************************************** 
* FunctionName   : TIM32Init()
* Description    : 初始化定时器
* EntryParameter : timNum - 定时器选择(0~3)；timPar - 定时器配置参数
* ReturnValue    : 成功返回0，否则返回1
********************************************************************************************************/
u8 TIM32Init(u8 timNum, TIM_SET *timPar)
{
    u32 clock = SystemCoreClock/4;							         // TIM时钟

	if (timNum > 3)
	{
	    return 1;
	}

    switch (timNum)
	{
	    case TIM0: LPC_SC->PCONP |= (1 << 1);  break;	             // 打开定时器0的功率控制位
		case TIM1: LPC_SC->PCONP |= (1 << 2);  break;		         // 打开定时器1的功率控制位
		case TIM2: LPC_SC->PCONP |= (1 << 22); break;		         // 打开定时器2的功率控制位
		case TIM3: LPC_SC->PCONP |= (1 << 23); break;		         // 打开定时器3的功率控制位
		default: break;
	}

	TIM32ClearInt(timNum, timPar->IntClear);					     // 清除中断
	LPC_TIM[timNum]->TC = timPar->InitValue;				         // 定时/计数器初始值
	LPC_TIM[timNum]->PR = timPar->Prescaler;                         // 设置分频系数

	if (timPar->Mode == TIM_TIMER)									 // 定时模式
	{
	    LPC_TIM[timNum]->CTCR = 0x00; 								 // 定时器模式
	    LPC_TIM[timNum]->MCR  = timPar->MatchSet;                    // 设置MR匹配
		LPC_TIM[timNum]->EMR  = timPar->MatchOut;                    // 匹配输出设置

	    /* 设置定时器匹配值，除以1000000换算成us，除以1000可以换算成ms */

		if (timPar->IntClear & TIM_MR0)								 // MR0
		{
		    LPC_TIM[timNum]->MR0 = (clock/1000000) * timPar->TimValue;
		}

	    if (timPar->IntClear & TIM_MR1)								 // MR1
		{
		    LPC_TIM[timNum]->MR1 = (clock/1000000) * timPar->TimValue;
		}

		if (timPar->IntClear & TIM_MR2)								 // MR2
		{
		    LPC_TIM[timNum]->MR2 = (clock/1000000) * timPar->TimValue;
		}

		if (timPar->IntClear & TIM_MR3)								 // MR3
		{
		    LPC_TIM[timNum]->MR3 = (clock/1000000) * timPar->TimValue;
		}
	} 
	else															 // 计数器模式
	{
	    LPC_TIM[timNum]->CCR  = timPar->CapCtrl;					 // 设置捕获事件发生时，计数器的工作状态
	    LPC_TIM[timNum]->CTCR = timPar->CaptureSet;					 // 设置计数模式，并选择输入端
	} 
	
    switch (timNum)													 // 使能中断
	{
	    case TIM0: NVIC_EnableIRQ(TIMER0_IRQn); break;	             
		case TIM1: NVIC_EnableIRQ(TIMER1_IRQn); break;		        
		case TIM2: NVIC_EnableIRQ(TIMER2_IRQn); break;		        
		case TIM3: NVIC_EnableIRQ(TIMER3_IRQn); break;		        
		default: break;
	} 
	
	TIM32Enable(timNum);         									 // 使能定时/计数器

	return 0;
}

/******************************************************************************************************** 
* FunctionName   : TIM32Clear()
* Description    : 清中断
* EntryParameter : timNum - 定时器选择，intSou - 要清除的中断源
* ReturnValue    : None
********************************************************************************************************/
void TIM32ClearInt(u8 timNum, u8 intSou)
{
    LPC_TIM[timNum]->IR = intSou;
}

/******************************************************************************************************** 
* FunctionName   : TIM32Enable()
* Description    : 使能定时/计数器
* EntryParameter : timNum - 定时器选择
* ReturnValue    : None
********************************************************************************************************/
void TIM32Enable(u8 timNum)
{
    LPC_TIM[timNum]->TCR |= TIM_TCRE;
}

/******************************************************************************************************** 
* FunctionName   : TIM32Disable()
* Description    : 禁止定时/计数器
* EntryParameter : timNum - 定时器选择
* ReturnValue    : None
********************************************************************************************************/
void TIM32Disable(u8 timNum)
{
    LPC_TIM[timNum]->TCR &= ~TIM_TCRE;
}

/******************************************************************************************************** 
* FunctionName   : TIM32Reset()
* Description    : 复位定时/计数器
* EntryParameter : timNum - 定时器选择
* ReturnValue    : None
********************************************************************************************************/
void TIM32Reset(u8 timNum)
{
	LPC_TIM[timNum]->TCR |= TIM_TCRR;
}

/******************************************************************************************************** 
* FunctionName   : TIM32GetTC()
* Description    : TC清零
* EntryParameter : timNum - 定时器选择
* ReturnValue    : None
********************************************************************************************************/
void TIM32ClearTC(u8 timNum)
{
    LPC_TIM[timNum]->TC = 0x00;
}

/******************************************************************************************************** 
* FunctionName   : TIM32GetTC()
* Description    : 获取TC
* EntryParameter : timNum - 定时器选择
* ReturnValue    : 返回TC值
********************************************************************************************************/
u32 TIM32GetTC(u8 timNum)
{
    return (LPC_TIM[timNum]->TC);
}

/******************************************************************************************************** 
* End Of File                  
********************************************************************************************************/


