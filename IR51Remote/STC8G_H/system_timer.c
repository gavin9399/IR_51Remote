/*====================================================
File    : system_timer.c
Version : V2.1
Date    : 2022.9.27
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G/H
====================================================*/

#include "system_timer.h"
#include "cpu.h"
#include "timer.h"

static uint32_t l_u32SystemTimeTicks=0;

#if SYSTEM_TIME_USE_INTERRUPT
uint8_t g_u8SystemTimeTicks=0;
/*----------------------------------------------
Function: Timer interrupt routine
Parameter: void
Return: void
Comments: interrupt every 1 ms, produce system time tick
----------------------------------------------*/
#if SYSTEM_TIME_USE==0
void TimerInterrupt(void) interrupt TIMER0_VECTOR
#elif SYSTEM_TIME_USE==1
void TimerInterrupt(void) interrupt TIMER1_VECTOR
#elif SYSTEM_TIME_USE==2
void TimerInterrupt(void) interrupt TIMER2_VECTOR
#elif SYSTEM_TIME_USE==3
void TimerInterrupt(void) interrupt TIMER3_VECTOR
#elif SYSTEM_TIME_USE==4
void TimerInterrupt(void) interrupt TIMER4_VECTOR
#endif
{
    g_u8SystemTimeTicks ++;
}
/*----------------------------------------------
Function: System timer update
Parameter: void
Return: void
----------------------------------------------*/
void SystemTimerUpdate(void)
{
    static uint8_t s_u8TimeRecord;
    uint8_t u8Now;
    u8Now = g_u8SystemTimeTicks;
    if (u8Now != s_u8TimeRecord)
    {
        l_u32SystemTimeTicks += (uint8_t)(u8Now - s_u8TimeRecord);
        s_u8TimeRecord = u8Now;
    }
}
#else
/*----------------------------------------------
Function: System timer update
Parameter: void
Return: void
----------------------------------------------*/
void SystemTimerUpdate(void)
{
    static uint16_t s_u16TimeRecord;
    uint16_t u16Now;
    uint8_t u8H,u8L;
  #if SYSTEM_TIME_USE==0
    u8H = TH0;
    u8L = TL0;
    if (u8H != TH0)
    {
        u8H = TH0;
        u8L = TL0;
    }
  #elif SYSTEM_TIME_USE==1
    u8H = TH1;
    u8L = TL1;
    if (u8H != TH1)
    {
        u8H = TH1;
        u8L = TL1;
    }
  #endif
    u16Now = ((uint16_t)u8H<<8) | u8L;
    if ((uint16_t)(u16Now - s_u16TimeRecord) >= (uint16_t)(FOSC/1000))
    {
        s_u16TimeRecord = u16Now;
        l_u32SystemTimeTicks ++;
    }
}
#endif

/*----------------------------------------------
Function: System timer initial
Parameter: void
Return: void
----------------------------------------------*/
void SystemTimerInit(void)
{
    TIM_InitTypeDef        TIM_InitStructure;
  #if SYSTEM_TIME_USE_INTERRUPT
    EA = 1;
    #if SYSTEM_TIME_USE==0
    TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReloadNoMask;   /* 指定工作模式, TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask */
    #else
    TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;   /* 指定工作模式, TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask */
    #endif
    TIM_InitStructure.TIM_Interrupt = ENABLE;                /* 中断允许 ENABLE, DISABLE */
    TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000UL);        /* 初值 */
  #else
    TIM_InitStructure.TIM_Mode      = TIM_16Bit;   /* 指定工作模式, TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask */
    TIM_InitStructure.TIM_Interrupt = DISABLE;                /* 中断允许 ENABLE, DISABLE */
  #endif
    TIM_InitStructure.TIM_Priority  = Priority_0;            /* 优先级设置 Priority_0,Priority_1,Priority_2,Priority_3 */
    TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;          /* 指定时钟源, TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext */
    TIM_InitStructure.TIM_ClkOut    = DISABLE;               /* 是否输出高速脉冲, ENABLE或DISABLE */
    TIM_InitStructure.TIM_Run       = ENABLE;                /* 是否初始化后启动定时器, ENABLE或DISABLE */
    Timer_Inilize(SYSTEM_TIME_USE,&TIM_InitStructure);       /* 初始化Timer Timer0,Timer1,Timer2,Timer3,Timer4 */
}

/*----------------------------------------------
Function: Get System timer ticks
Parameter: void
Return: void
----------------------------------------------*/
uint32_t u32GetSysTicks(void)
{
    return l_u32SystemTimeTicks;
}
