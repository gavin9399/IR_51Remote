/*====================================================
File    : system_timer.h
Version : V2.1
Date    : 2022.9.27
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: 51 MCU
====================================================*/

#ifndef _SYSTEM_TIMER_H_
#define _SYSTEM_TIMER_H_ 1

#include "typedef.h"

#define SYSTEM_TIME_USE_INTERRUPT true

#if SYSTEM_TIME_USE_INTERRUPT
extern uint8_t g_u8SystemTimeTicks;
#endif

extern void SystemTimerInit(void);
extern void SystemTimerUpdate(void);
extern uint32_t u32GetSysTicks(void);

#endif  /* _SYSTEM_TIMER_H_ */
