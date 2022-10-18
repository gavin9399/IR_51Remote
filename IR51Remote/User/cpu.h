/*====================================================
File    : cpu.h
Version : V1.12
Date    : 2022.8.7
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     :
MCU type: 51 MCU
====================================================*/

#ifndef _CPU_H_
#define _CPU_H_ 1

#if defined STC12C5A60S2
  #include "STC12C5A60S2.h"
  #define FOSC 24000000L
  #define SYSTEM_TIME_USE   0   /*0,1 for STC12C5A60S2*/
#elif (defined STC15) || (defined STC15W401AS) || (defined STC15W402AS) || (defined STC15W404AS) || (defined STC15W408AS)
  #include "STC15F2K60S2.h"
  #define FOSC 35000000L
  #define SYSTEM_TIME_USE   0   /*0,2 for STC15*/
#elif defined STC8F
  #include "STC8F.h"
  #define FOSC 24000000L
  #define SYSTEM_TIME_USE   0   /*0,1,2,3,4 for STC8*/
#elif defined STC8G
  #include "STC8xxxx.h"
  #define FOSC 30000000L
  #define SYSTEM_TIME_USE   0   /*0,1,2,3,4 for STC8*/
#elif defined STC8H
  #include "STC8xxxx.h"
  #define FOSC 35000000L
  #define SYSTEM_TIME_USE   0   /*0,1,2,3,4 for STC8*/
#elif defined C8051F350
  #include "C8051F350.h"
  #include "C8051F350G.h"
  #define SYSCLK 49000000L      /*49000000L/24500000L/12250000L/6125000L/3062500L*/
  #define FOSC SYSCLK
  #define SYSTEM_TIME_USE   3   /*0,1,2,3 for C8051F350*/
#else
  #include "reg51.h"
  #define FOSC 12000000L
  #define SYSTEM_TIME_USE   0   
#endif

#endif  /* _CPU_H_ */
