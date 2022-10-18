/*====================================================
File    : gpio.c
Version : V1.1
Date    : 2021.1.5
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G/H
====================================================*/

#include "gpio.h"
#include "cpu.h"
#include "typedef.h"

/*----------------------------------------------
Function: GPIO Initialization
  * @param  GPIO_Pin : This parameter contains the pin number, it can be any value
  *         of the @ref GPIO_Pin_TypeDef enumeration.
  * @param  GPIO_Mode : This parameter can be a value of the
  *         @Ref GPIO_Mode_TypeDef enumeration.
Return: void
----------------------------------------------*/
void GPIO_Init(GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode)
{
    uint8_t u8Value;
    u8Value = GPIO_Pin & 0x0F;
    if (u8Value < 8)
    {
        u8Value = 1 << u8Value;
    }
    else if (8 == u8Value)
    {
        u8Value = 0x0F;
    }
    else if (9 == u8Value)
    {
        u8Value = 0xF0;
    }
    else if (10 == u8Value)
    {
        u8Value = 0xFF;
    }
    else
    {
    }
    switch (GPIO_Pin & 0xF0)
    {
        case 0x00:
        if ((GPIO_Mode & Bit2)!=0)
        {
            P0 |= u8Value;
        }
        else
        {
            P0 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit0)!=0)
        {
            P0M0 |= u8Value;
        }
        else
        {
            P0M0 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit1)!=0)
        {
            P0M1 |= u8Value;
        }
        else
        {
            P0M1 &= ~u8Value;
        }
        break;
        case 0x10:
        if ((GPIO_Mode & Bit2)!=0)
        {
            P1 |= u8Value;
        }
        else
        {
            P1 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit0)!=0)
        {
            P1M0 |= u8Value;
        }
        else
        {
            P1M0 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit1)!=0)
        {
            P1M1 |= u8Value;
        }
        else
        {
            P1M1 &= ~u8Value;
        }
        break;
        case 0x20:
        if ((GPIO_Mode & Bit2)!=0)
        {
            P2 |= u8Value;
        }
        else
        {
            P2 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit0)!=0)
        {
            P2M0 |= u8Value;
        }
        else
        {
            P2M0 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit1)!=0)
        {
            P2M1 |= u8Value;
        }
        else
        {
            P2M1 &= ~u8Value;
        }
        break;
        case 0x30:
        if ((GPIO_Mode & Bit2)!=0)
        {
            P3 |= u8Value;
        }
        else
        {
            P3 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit0)!=0)
        {
            P3M0 |= u8Value;
        }
        else
        {
            P3M0 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit1)!=0)
        {
            P3M1 |= u8Value;
        }
        else
        {
            P3M1 &= ~u8Value;
        }
        break;
        case 0x40:
        if ((GPIO_Mode & Bit2)!=0)
        {
            P4 |= u8Value;
        }
        else
        {
            P4 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit0)!=0)
        {
            P4M0 |= u8Value;
        }
        else
        {
            P4M0 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit1)!=0)
        {
            P4M1 |= u8Value;
        }
        else
        {
            P4M1 &= ~u8Value;
        }
        break;
        case 0x50:
        if ((GPIO_Mode & Bit2)!=0)
        {
            P5 |= u8Value;
        }
        else
        {
            P5 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit0)!=0)
        {
            P5M0 |= u8Value;
        }
        else
        {
            P5M0 &= ~u8Value;
        }
        if ((GPIO_Mode & Bit1)!=0)
        {
            P5M1 |= u8Value;
        }
        else
        {
            P5M1 &= ~u8Value;
        }
        break;
        default:
        break;
    }
}
/*----------------------------------------------
Function: GPIO Write
  * @param  GPIO_Pin : This parameter contains the pin number, it can be any value
  *         of the @ref GPIO_Pin_TypeDef enumeration.
  * @param  u8Value : u8Value to write.
Return: void
----------------------------------------------*/
void GPIO_Write(GPIO_Pin_TypeDef GPIO_Pin, uint8_t u8Value)
{
    uint8_t u8Mask;
    u8Mask = GPIO_Pin & 0x0F;
    if (u8Mask < 8)
    {
        u8Mask = 1 << u8Mask;
        if (0 != u8Value)
        {
            u8Value = u8Mask;
        }
        u8Mask = ~u8Mask;
    }
    else if (8 == u8Mask)
    {
        u8Mask = 0xF0;
        u8Value &= 0x0F;
    }
    else if (9 == u8Mask)
    {
        u8Mask = 0x0F;
        u8Value &= 0xF0;
    }
    else if (10 == u8Mask)
    {
        u8Mask = 0x00;
    }
    else
    {
    }
    switch (GPIO_Pin & 0xF0)
    {
        case 0x00:
        P0 = (P0 & u8Mask) | u8Value;
        break;
        case 0x10:
        P1 = (P1 & u8Mask) | u8Value;
        break;
        case 0x20:
        P2 = (P2 & u8Mask) | u8Value;
        break;
        case 0x30:
        P3 = (P3 & u8Mask) | u8Value;
        break;
        case 0x40:
        P4 = (P4 & u8Mask) | u8Value;
        break;
        case 0x50:
        P5 = (P5 & u8Mask) | u8Value;
        break;
        default:
        break;
    }
}