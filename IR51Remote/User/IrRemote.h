/*====================================================
File    : IrRemote.h
Version : V1.0
Date    : 2022.10.14
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G
====================================================*/

#ifndef _IR_REMOTE_H_
#define _IR_REMOTE_H_ 1

#include "typedef.h"

#define IR_IN_PIN           P10
#define IR_IN_PIN_INIT      GPIO_P1_0
#define IR_OUT_PIN          P37
#define IR_OUT_PIN_INIT     GPIO_P3_7
#define IR_RECEIVE_MODE     0
#define IR_TRANSMIT_MODE    1

#define IR_WAVE_MAX_NUM     200

extern void IrRemoteInit(uint8_t Mode);
extern void IrStartRead(void);
extern bool SaveIrWave(uint8_t u8Number);
extern void IrTransmit(uint8_t u8Number);

#endif  /* _IR_REMOTE_H_ */
