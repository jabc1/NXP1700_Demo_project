#include "time.h"

#include "LPC17xx.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg.h"

void LPC_TIEM0_init()//1ms
{
	
	LPC_SC->PCONP|= 1 << 1; //������ʱ��0���ʿ���

	LPC_TIM0-> TCR  = 0x02;//ʱ�ܶ�ʱ��
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
//	timParstruct.Mode = TIM_TIMER_MODE; //����ģʽ
//	timParstruct.CapCtrl = ENABLE;//����ж�
//	timParstruct.InitValue = 5000;//��װ��ֵ
//	timParstruct.Prescaler = 1;//��Ƶϵ��
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
* Description    : ��ʼ����ʱ��
* EntryParameter : timNum - ��ʱ��ѡ��(0~3)��timPar - ��ʱ�����ò���
* ReturnValue    : �ɹ�����0�����򷵻�1
********************************************************************************************************/
u8 TIM32Init(u8 timNum, TIM_SET *timPar)
{
    u32 clock = SystemCoreClock/4;							         // TIMʱ��

	if (timNum > 3)
	{
	    return 1;
	}

    switch (timNum)
	{
	    case TIM0: LPC_SC->PCONP |= (1 << 1);  break;	             // �򿪶�ʱ��0�Ĺ��ʿ���λ
		case TIM1: LPC_SC->PCONP |= (1 << 2);  break;		         // �򿪶�ʱ��1�Ĺ��ʿ���λ
		case TIM2: LPC_SC->PCONP |= (1 << 22); break;		         // �򿪶�ʱ��2�Ĺ��ʿ���λ
		case TIM3: LPC_SC->PCONP |= (1 << 23); break;		         // �򿪶�ʱ��3�Ĺ��ʿ���λ
		default: break;
	}

	TIM32ClearInt(timNum, timPar->IntClear);					     // ����ж�
	LPC_TIM[timNum]->TC = timPar->InitValue;				         // ��ʱ/��������ʼֵ
	LPC_TIM[timNum]->PR = timPar->Prescaler;                         // ���÷�Ƶϵ��

	if (timPar->Mode == TIM_TIMER)									 // ��ʱģʽ
	{
	    LPC_TIM[timNum]->CTCR = 0x00; 								 // ��ʱ��ģʽ
	    LPC_TIM[timNum]->MCR  = timPar->MatchSet;                    // ����MRƥ��
		LPC_TIM[timNum]->EMR  = timPar->MatchOut;                    // ƥ���������

	    /* ���ö�ʱ��ƥ��ֵ������1000000�����us������1000���Ի����ms */

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
	else															 // ������ģʽ
	{
	    LPC_TIM[timNum]->CCR  = timPar->CapCtrl;					 // ���ò����¼�����ʱ���������Ĺ���״̬
	    LPC_TIM[timNum]->CTCR = timPar->CaptureSet;					 // ���ü���ģʽ����ѡ�������
	} 
	
    switch (timNum)													 // ʹ���ж�
	{
	    case TIM0: NVIC_EnableIRQ(TIMER0_IRQn); break;	             
		case TIM1: NVIC_EnableIRQ(TIMER1_IRQn); break;		        
		case TIM2: NVIC_EnableIRQ(TIMER2_IRQn); break;		        
		case TIM3: NVIC_EnableIRQ(TIMER3_IRQn); break;		        
		default: break;
	} 
	
	TIM32Enable(timNum);         									 // ʹ�ܶ�ʱ/������

	return 0;
}

/******************************************************************************************************** 
* FunctionName   : TIM32Clear()
* Description    : ���ж�
* EntryParameter : timNum - ��ʱ��ѡ��intSou - Ҫ������ж�Դ
* ReturnValue    : None
********************************************************************************************************/
void TIM32ClearInt(u8 timNum, u8 intSou)
{
    LPC_TIM[timNum]->IR = intSou;
}

/******************************************************************************************************** 
* FunctionName   : TIM32Enable()
* Description    : ʹ�ܶ�ʱ/������
* EntryParameter : timNum - ��ʱ��ѡ��
* ReturnValue    : None
********************************************************************************************************/
void TIM32Enable(u8 timNum)
{
    LPC_TIM[timNum]->TCR |= TIM_TCRE;
}

/******************************************************************************************************** 
* FunctionName   : TIM32Disable()
* Description    : ��ֹ��ʱ/������
* EntryParameter : timNum - ��ʱ��ѡ��
* ReturnValue    : None
********************************************************************************************************/
void TIM32Disable(u8 timNum)
{
    LPC_TIM[timNum]->TCR &= ~TIM_TCRE;
}

/******************************************************************************************************** 
* FunctionName   : TIM32Reset()
* Description    : ��λ��ʱ/������
* EntryParameter : timNum - ��ʱ��ѡ��
* ReturnValue    : None
********************************************************************************************************/
void TIM32Reset(u8 timNum)
{
	LPC_TIM[timNum]->TCR |= TIM_TCRR;
}

/******************************************************************************************************** 
* FunctionName   : TIM32GetTC()
* Description    : TC����
* EntryParameter : timNum - ��ʱ��ѡ��
* ReturnValue    : None
********************************************************************************************************/
void TIM32ClearTC(u8 timNum)
{
    LPC_TIM[timNum]->TC = 0x00;
}

/******************************************************************************************************** 
* FunctionName   : TIM32GetTC()
* Description    : ��ȡTC
* EntryParameter : timNum - ��ʱ��ѡ��
* ReturnValue    : ����TCֵ
********************************************************************************************************/
u32 TIM32GetTC(u8 timNum)
{
    return (LPC_TIM[timNum]->TC);
}

/******************************************************************************************************** 
* End Of File                  
********************************************************************************************************/


