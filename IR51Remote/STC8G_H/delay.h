/*====================================================
File    : delay.h
Version : V1.1
Date    : 2015.3.10
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: 8051 series
====================================================*/

#ifndef _DELAY_H_
#define _DELAY_H_ 1

#include "typedef.h"

extern void delay_ms(uint16_t u16Time);
extern void delay_us(uint8_t u8Time);
extern void delay_1us(void);

#endif  /* _DELAY_H_ */
