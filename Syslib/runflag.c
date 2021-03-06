#include "runflag.h"
/**
******************************************************************************
* @file    runflag.c
* @author  Jason
* @date    2018/10/27
* @brief   产生定时标志位
******************************************************************************
*/
#define TICK_FREQ       1000
#define TICK_CNT_FREQ   SYS_CLK
#define TICK_PERIOD     (TICK_CNT_FREQ/TICK_FREQ)

static uint8_t PriorityFlag;
static uint32_t RunTick;
RunFlag_Type RunFlag;

#define FREQ_FLAG_INIT(freq) do{ \
    RunFlag.Hz##freq = 0; \
    RunFlag.Hz##freq##Tick = tick; \
}while(0)

#define FREQ_FLAG(freq) FreqCalc(TICK_FREQ/freq, &(RunFlag.Hz##freq), &(RunFlag.Hz##freq##Tick))

void FreqCalc(uint32_t FreqFactor, uint8_t* pFlag, uint32_t* pTick)//产生中断标志
{
    if(!PriorityFlag && RunTick - *pTick >= FreqFactor)
    {
        *pFlag = 1;//中断标志
        (*pTick) += FreqFactor;
        PriorityFlag = 1;
    }
    else
    {
        *pFlag = 0;
    }
}

uint8_t CPU_AVG_Usage = 0;
uint32_t IT_BusyTime = 0;
extern volatile unsigned long SysTickCnt;

void RunFlagInit(void)
{
    uint32_t tick = SysTickCnt;
    
    FREQ_FLAG_INIT(1);//1hz
    FREQ_FLAG_INIT(4);
    FREQ_FLAG_INIT(10);
    FREQ_FLAG_INIT(20);
    FREQ_FLAG_INIT(50);
    FREQ_FLAG_INIT(100);
    FREQ_FLAG_INIT(250);
    FREQ_FLAG_INIT(500);
    FREQ_FLAG_INIT(1000);//1000hz
}

void RunFlagHandler(void)
{
	PriorityFlag = 0;
    RunTick = SysTickCnt;
    FREQ_FLAG(1000);//1000hz
    FREQ_FLAG(500);//500hz
    FREQ_FLAG(250);//250hz
    FREQ_FLAG(100);//10hz
    FREQ_FLAG(50);//50hz
    FREQ_FLAG(20);//20hz
    FREQ_FLAG(10);//10hz
    FREQ_FLAG(4);//4hz
    FREQ_FLAG(1);//1hz
}


