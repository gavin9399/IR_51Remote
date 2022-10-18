/*====================================================
File    : delay.c
Version : V1.1
Date    : 2017.11.14
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     :
MCU type: STC8
====================================================*/

#include "delay.h"
#include "cpu.h"

/*----------------------------------------------
Function: Delay function
Parameter: Time to delay, in millisecond,
    unsigned 16 bits integer, 1~65535
Return: void
----------------------------------------------*/
void delay_ms(uint16_t u16Time)
{
    register uint8_t u8i,u8j;
    while (u16Time)
    {
        u8i=(FOSC+375000L)/750000L;  /*STC8 MCU*/
        do
        {
            u8j=249;
            do
            {
            ;
            } while (--u8j);
        } while (--u8i);
        u16Time--;
    }
}

/*----------------------------------------------
Function: Delay function
Parameter: Time to delay, in microsecond,
    unsigned 8 bits integer, 1~255
Return: void
----------------------------------------------*/
void delay_us(uint8_t u8Time)
{
    register uint8_t u8i;
    do
    {
        u8i=(FOSC+1250000L)/3500000L;  /*STC8 MCU*/
        do
        {
        ;
        } while (--u8i);
    } while (--u8Time);
}

/*----------------------------------------------
Function: Delay function
Parameter: void
Return: void
----------------------------------------------*/
void delay_1us(void)
{
    register uint8_t u8i;
    u8i=(FOSC+2000000L)/4000000L;  /*STC8 MCU*/
    do
    {
    ;
    } while (--u8i);
}

