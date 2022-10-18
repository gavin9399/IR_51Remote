/*====================================================
File    : clkout.c
Version : V1.01
Date    : 2022.8.9
Author  : Gavin Hu
Company : ZJOU
Comments: Main clock output, @P5.4/P1.6
IDE     : 
MCU type: STC8G/H
====================================================*/

#include "cpu.h"
#include "clkout.h"

/*----------------------------------------------
Function: Main clock output initialization
Parameter: Output pin, frequency (Hz)
Return: true/false
----------------------------------------------*/
bool ClockOutInit(uint8_t OutPin, uint32_t u32Frequency)
{
    u32Frequency = FOSC / u32Frequency;
    if ((u32Frequency > 127) || (0 == u32Frequency))
    {
        return false;
    }
    if (MCLKO_PIN5_4 == OutPin)
    {
        P_SW2 |= (1<<7);
        MCLKOCR = (uint8_t)u32Frequency;
        P_SW2 &= ~(1<<7);
        P5n_push_pull(Pin4);
    }
    else if (MCLKO_PIN1_6 == OutPin)
    {
        P_SW2 |= (1<<7);
        MCLKOCR = (1<<7) | (uint8_t)u32Frequency;
        P_SW2 &= ~(1<<7);
        P1n_push_pull(Pin6);
    }
    else
    {
        return false;
    }
    return true;
}
