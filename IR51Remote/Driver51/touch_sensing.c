/*====================================================
File    : touch_sensing.c
Version : V1.01
Date    : 2022.8.9
Author  : Gavin Hu
Company : ZJOU
Comments: Touch sensing use ADC & clock out
IDE     : 
MCU type: 51 MCU
====================================================*/

#include "touch_sensing.h"
#include "cpu.h"
#include "gpio.h"
#include "adc.h"
#include "system_timer.h"
#ifdef STC8G
#include "clkout.h"
#endif

/*----------------------------------------------
Function: Touch Sensing initialization
Parameter: void
Return: void
----------------------------------------------*/
void TouchSensingInitialization(void)
{
#ifdef STC8G
    ADC_InitTypeDef adc;
    /*ADC initialization*/
	adc.ADC_SMPduty = 10;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	adc.ADC_Speed = ADC_SPEED_2X1T;			//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	adc.ADC_Power = ENABLE;			//ADC功率允许/关闭	ENABLE,DISABLE
//	adc.ADC_AdjResult;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
//	adc.ADC_Priority;			//优先级设置	Priority_0,Priority_1,Priority_2,Priority_3
	adc.ADC_Interrupt = DISABLE;	//中断允许	ENABLE,DISABLE
	adc.ADC_CsSetup = 0;		//ADC 通道选择时间控制 0(默认),1
	adc.ADC_CsHold = 1;			//ADC 通道选择保持时间控制 0,1(默认),2,3
    ADC_Inilize(&adc);
    ClockOutInit(MCLKO_PIN5_4, 300000);
#else
    uint8_t u8Data = 0;
  #if TOUCH_KEY_QUANTIY>0
    u8Data |= 1<<TOUCH_KEY0_ADC;
  #endif
  #if TOUCH_KEY_QUANTIY>1
    u8Data |= 1<<TOUCH_KEY1_ADC;
  #endif
  #if TOUCH_KEY_QUANTIY>2
    u8Data |= 1<<TOUCH_KEY2_ADC;
  #endif
  #if TOUCH_KEY_QUANTIY>3
    u8Data |= 1<<TOUCH_KEY3_ADC;
  #endif
  #if TOUCH_KEY_QUANTIY>4
    u8Data |= 1<<TOUCH_KEY4_ADC;
  #endif
  #if TOUCH_KEY_QUANTIY>5
    u8Data |= 1<<TOUCH_KEY5_ADC;
  #endif
  #if TOUCH_KEY_QUANTIY>6
    u8Data |= 1<<TOUCH_KEY6_ADC;
  #endif
  #if TOUCH_KEY_QUANTIY>7
    u8Data |= 1<<TOUCH_KEY7_ADC;
  #endif
    /*ADC initialization*/
    ADC_Initialization(u8Data);

    /*GPIO & Clock out initialization*/
//    GPIO_Init(GPIO_PORTS_1, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW);
//    BRT_ClockOutInit(300);
#endif
}

/*----------------------------------------------
Function: Touch Key scan
Parameter: void
Return: bit0~4 Touch Key number,
    bit5~7 Touch Key status: 0x00 no press, 0x20 Touch Key down, 
    0x40 Touch Key up, 0x80 Touch Key long press,
    0xC0 Touch Key up after long press.
Comments: Scan Touch Keys in 100mS
----------------------------------------------*/
uint8_t u8TouchKeyScan(void)
{
    static uint8_t s_u8ScanedTime;
    static uint8_t idata s_a_u8TouchKey[TOUCH_KEY_QUANTIY];
    static uint8_t idata s_a_u8TouchKeyTimeCount[TOUCH_KEY_QUANTIY];
    static uint8_t idata s_a_u8Status[TOUCH_KEY_QUANTIY];
    uint8_t u8i;
  #if SYSTEM_TIME_USE_INTERRUPT
    u8i = g_u8SystemTimeTicks;
  #else
    u8i = u32GetSysTicks();
  #endif
    if ((uint8_t)(u8i - s_u8ScanedTime) >= TOUCH_KEY_SCAN_PERIOD)
    {
        s_u8ScanedTime = u8i;
        for (u8i=0;u8i<TOUCH_KEY_QUANTIY;u8i++)
        {
            s_a_u8TouchKey[u8i] = (s_a_u8TouchKey[u8i] << 1) & 0x02;
        }
      #if TOUCH_KEY_QUANTIY>0
        if(u16Get_ADC_Result(TOUCH_KEY0_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key0 pressed*/
        {
            s_a_u8TouchKey[0] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>1
        if(u16Get_ADC_Result(TOUCH_KEY1_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key1 pressed*/
        {
            s_a_u8TouchKey[1] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>2
        if(u16Get_ADC_Result(TOUCH_KEY2_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key2 pressed*/
        {
            s_a_u8TouchKey[2] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>3
        if(u16Get_ADC_Result(TOUCH_KEY3_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key3 pressed*/
        {
            s_a_u8TouchKey[3] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>4
        if(u16Get_ADC_Result(TOUCH_KEY4_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key4 pressed*/
        {
            s_a_u8TouchKey[4] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>5
        if(u16Get_ADC_Result(TOUCH_KEY5_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key5 pressed*/
        {
            s_a_u8TouchKey[5] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>6
        if(u16Get_ADC_Result(TOUCH_KEY6_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key6 pressed*/
        {
            s_a_u8TouchKey[6] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>7
        if(u16Get_ADC_Result(TOUCH_KEY7_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key7 pressed*/
        {
            s_a_u8TouchKey[7] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>8
        if(u16Get_ADC_Result(TOUCH_KEY8_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key7 pressed*/
        {
            s_a_u8TouchKey[8] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>9
        if(u16Get_ADC_Result(TOUCH_KEY9_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key7 pressed*/
        {
            s_a_u8TouchKey[9] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>10
        if(u16Get_ADC_Result(TOUCH_KEY10_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key7 pressed*/
        {
            s_a_u8TouchKey[10] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>11
        if(u16Get_ADC_Result(TOUCH_KEY11_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key7 pressed*/
        {
            s_a_u8TouchKey[11] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>12
        if(u16Get_ADC_Result(TOUCH_KEY12_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key7 pressed*/
        {
            s_a_u8TouchKey[12] |= 0x01;
        }
      #endif
      #if TOUCH_KEY_QUANTIY>13
        if(u16Get_ADC_Result(TOUCH_KEY13_ADC) < TOUCH_SENSING_THRESHOLD) /*Touch Key7 pressed*/
        {
            s_a_u8TouchKey[13] |= 0x01;
        }
      #endif
        for (u8i=0;u8i<TOUCH_KEY_QUANTIY;u8i++)
        {
            switch (s_a_u8TouchKey[u8i])
            {
            case 0x01:
                s_a_u8Status[u8i] = TOUCH_KEY_DOWN;
                s_a_u8TouchKeyTimeCount[u8i] = 0;
                return (TOUCH_KEY_DOWN | u8i);
            case 0x02:
                return (((s_a_u8Status[u8i] & TOUCH_KEY_LONG_PRESS) | TOUCH_KEY_UP) | u8i);
            case 0x03:
                if (TOUCH_KEY_DOWN == s_a_u8Status[u8i])
                {
                    s_a_u8TouchKeyTimeCount[u8i]++;
                    if (s_a_u8TouchKeyTimeCount[u8i] >= LONG_PRESS_TIME)
                    {
                        s_a_u8Status[u8i] = TOUCH_KEY_LONG_PRESS;
                        return (TOUCH_KEY_LONG_PRESS | u8i);
                    }
                }
                break;
            default:    /*case 0x00*/
                break;
            }
        }
    }
    return TOUCH_KEY_NO_CHANGE;
}