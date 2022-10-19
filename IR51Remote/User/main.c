/*====================================================
File    : main.c
Project : 
Version : V1.0
Date    : 2022.8.7
Author  : Gavin Hu
Company : ZJOU
Comments: 
    PCB: 
IDE     :
Chip type           : STC8G1K17
Program type        : Application
Clock frequency     : 30.000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
====================================================*/
/*#pragma  src*/
#define DEBUG 0
#include "cpu.h"
#include "typedef.h"
#include "system_timer.h"
#include "led.h"
#include "uart.h"
#include "stdio.h"
#include "gpio.h"
#include "pca.h"
#include "touch_sensing.h"
#include "IrRemote.h"
#include "eeprom.h"
#include "adc.h"

/*----------------------------------------------
  Constant define
----------------------------------------------*/
#define NORMAL_MODE 0X00
#define STUDY_MODE  0X10

/*----------------------------------------------
  Port define
----------------------------------------------*/

/*----------------------------------------------
  Function declaration
----------------------------------------------*/
void SystemInitialization(void);

/*----------------------------------------------
  Public variable declaration
----------------------------------------------*/


/*----------------------------------------------
Function: Main routine
Parameter: void
Return: void
----------------------------------------------*/
void main(void)
{
    uint16_t u16StartStudyTime;
    uint8_t u8Key, u8Work=NORMAL_MODE;

    /*System timer initialization*/
    SystemTimerInit();
    SystemInitialization();

    EA = 1;

    while (1)
    {
        SystemTimerUpdate();
        u8Key = u8TouchKeyScan();
        if ((TOUCH_KEY_LONG_PRESS+1) == u8Key)
        {
            if (STUDY_MODE != (0xF0 & u8Work))
            {
                u8Work = STUDY_MODE;
                IrRemoteInit(IR_RECEIVE_MODE);
                LedSet(LED_0, LED_MODE_ON);
                u16StartStudyTime = u32GetSysTicks();
            }
            else
            {
                u8Work = NORMAL_MODE;
                IrRemoteInit(IR_TRANSMIT_MODE);
                LedSet(LED_0, LED_MODE_OFF);
            }
        }
        else if (STUDY_MODE == (0xF0 & u8Work))
        {
            if ((uint16_t)((uint16_t)u32GetSysTicks() - u16StartStudyTime) > 10000)
            {
                u8Work = NORMAL_MODE;
                IrRemoteInit(IR_TRANSMIT_MODE);
                LedSet(LED_0, LED_MODE_OFF);
            }
            else
            {
                if (0 != (TOUCH_KEY_DOWN & u8Key))
                {
                    IrStartRead();
                    LedTwinkle(LED_0, 20, 5, 5);
                    u8Work = STUDY_MODE | (0x0F & u8Key);
                    u16StartStudyTime = u32GetSysTicks();
                }
                if (SaveIrWave(0x0F & u8Work))
                {
                    LedSet(LED_0, LED_MODE_ON);
                }
            }
        }
        else
        {
            if (0 != (TOUCH_KEY_DOWN & u8Key))
            {
                IrTransmit(0x0F & u8Key);
                LedTwinkle(LED_0, 2, 1, 1);
            }
        }
        LedUpdate();
    }
}

void SystemInitialization(void)
{
    /*UART initialization*/
    UART_ConfInf_t UART_Inf;
    UART_Inf.UART_Mode = UART_8BIT_BRTX;
    UART_Inf.UART_BRT_Use = BRT_TIMER2;
    UART_Inf.UART_BaudRate = 115200;
    UART_Inf.UART_RxEnable = ENABLE;
    UART_Inf.UART_Interrupt = ENABLE;
    u8UART_Configuration(UART1, &UART_Inf);
    LedInitialization();
    TouchSensingInitialization();
    IrRemoteInit(IR_TRANSMIT_MODE);
}
