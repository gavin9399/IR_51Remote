/*====================================================
File    : clkout.h
Version : V1.01
Date    : 2022.8.9
Author  : Gavin Hu
Company : ZJOU
Comments: Main clock output, @P5.4/P1.6
IDE     : 
MCU type: STC8G/H
====================================================*/

#ifndef _CLK_OUT_H_
#define _CLK_OUT_H_ 1

#include "typedef.h"

#define MCLKO_PIN5_4 0
#define MCLKO_PIN1_6 1

extern bool ClockOutInit(uint8_t OutPin, uint32_t u32Frequency);

#endif  /* _CLK_OUT_H_ */
