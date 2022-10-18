/*====================================================
File    : led.h
Version : V1.01
Date    : 2016.12.24
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: 51 MCU
----------------------------------------------------
2017.12.10
Modify: "void LedTwinkle(LED_TypeDef Leds, uint8_t u8TwinkleNumber, uint8_t u8TurnOnTime, uint8_t u8u8Period)"
    --> "void LedTwinkle(LED_TypeDef Leds, uint8_t u8TwinkleNumber, uint8_t u8TurnOnTime, uint8_t u8TurnOffTime)"
Fix bug: Twinkle period calculate error.
====================================================*/

#include "cpu.h"
#include "gpio.h"
#include "led.h"
#include "system_timer.h"

code const uint8_t c_a_u8BitMask[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
static LED_Special_Mode_TypeDef l_S_LedMode;
static uint8_t l_u8LedState;
static LedControl_t idata l_S_LedControl[LED_QUANTIY];

static void LedOutputState(void);
/*----------------------------------------------
Function: LED initialization
Parameter: void
Return: void
----------------------------------------------*/
void LedInitialization(void)
{
    uint8_t u8i;
  #ifdef LED0_PIN
    #if LED_TURN_ON_VOLTAGE==0
    GPIO_Init(LED0_PIN_INIT, GPIO_MODE_OUT_OD_HIZ);
    #else
    GPIO_Init(LED0_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    #endif
  #endif
  #ifdef LED1_PIN
    #if LED_TURN_ON_VOLTAGE==0
    GPIO_Init(LED1_PIN_INIT, GPIO_MODE_OUT_OD_HIZ);
    #else
    GPIO_Init(LED1_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    #endif
  #endif
  #ifdef LED2_PIN
    #if LED_TURN_ON_VOLTAGE==0
    GPIO_Init(LED2_PIN_INIT, GPIO_MODE_OUT_OD_HIZ);
    #else
    GPIO_Init(LED2_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    #endif
  #endif
  #ifdef LED3_PIN
    #if LED_TURN_ON_VOLTAGE==0
    GPIO_Init(LED3_PIN_INIT, GPIO_MODE_OUT_OD_HIZ);
    #else
    GPIO_Init(LED3_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    #endif
  #endif
  #ifdef LED4_PIN
    #if LED_TURN_ON_VOLTAGE==0
    GPIO_Init(LED4_PIN_INIT, GPIO_MODE_OUT_OD_HIZ);
    #else
    GPIO_Init(LED4_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    #endif
  #endif
  #ifdef LED5_PIN
    #if LED_TURN_ON_VOLTAGE==0
    GPIO_Init(LED5_PIN_INIT, GPIO_MODE_OUT_OD_HIZ);
    #else
    GPIO_Init(LED5_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    #endif
  #endif
  #ifdef LED6_PIN
    #if LED_TURN_ON_VOLTAGE==0
    GPIO_Init(LED6_PIN_INIT, GPIO_MODE_OUT_OD_HIZ);
    #else
    GPIO_Init(LED6_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    #endif
  #endif
  #ifdef LED7_PIN
    #if LED_TURN_ON_VOLTAGE==0
    GPIO_Init(LED7_PIN_INIT, GPIO_MODE_OUT_OD_HIZ);
    #else
    GPIO_Init(LED7_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    #endif
  #endif
    for (u8i=0;u8i<LED_QUANTIY;u8i++)
    {
        l_S_LedControl[u8i].u8TwinkleCount = 0;
        l_S_LedControl[u8i].u8HoldTime = 0;
    }
    l_S_LedMode = LED_MODE_NORMAL;
}

/*----------------------------------------------
Function: LED set, Tun ON/OFF/TOGGLE given LEDs
Parameter: Leds - bit mask value of leds to be turned ON/OFF/TOGGLE
    mode - TWINKLE, TOGGLE, ON, OFF
Return: void
----------------------------------------------*/
void LedSet(LED_TypeDef Leds, LED_Mode_TypeDef Mode)
{
    uint8_t u8i;
    if (LED_MODE_TWINKLE == Mode)
    {
        LedTwinkle(Leds, LED_INFINITE_TWINKLE, LED_DEFAULT_ON_TIME, LED_DEFAULT_OFF_TIME);
    }
    else
    {
        if (LED_MODE_OFF == Mode)
        {
            l_u8LedState &= (~Leds);
        }
        else if (LED_MODE_ON == Mode)
        {
            l_u8LedState |= Leds;
        }
        else if (LED_MODE_TOGGLE == Mode)
        {
            l_u8LedState ^= Leds;
        }
        else
        {
        }
        for (u8i=0;u8i<LED_QUANTIY;u8i++)
        {
            if (Leds & c_a_u8BitMask[u8i])
            {
                l_S_LedControl[u8i].u8TwinkleCount = 0;
            }
        }
        LedOutputState();
    }
}

/*----------------------------------------------
Function: LED set twinkle, twinkle the given LEDs
Parameter: Leds - bit mask value of leds to be blinked
    u8TwinkleNumber  - number of blinks
    u8TurnOnTime    - the time in each period where the led will be on (50 mS)
    u8TurnOffTime     - length of each cycle in 50 milliseconds
Return: void
----------------------------------------------*/
void LedTwinkle(LED_TypeDef Leds, uint8_t u8TwinkleNumber, uint8_t u8TurnOnTime, uint8_t u8TurnOffTime)
{
    uint8_t u8i;
    if (0 == u8TurnOnTime)
    {
        l_u8LedState &= (~Leds);
        u8TwinkleNumber = 0;
    }
    else if (0 == u8TurnOffTime)
    {
        l_u8LedState |= Leds;
        u8TwinkleNumber = 0;
    }
    else
    {
    }
    for (u8i=0;u8i<LED_QUANTIY;u8i++)
    {
        if (Leds & c_a_u8BitMask[u8i])
        {
            l_S_LedControl[u8i].u8TwinkleCount = u8TwinkleNumber;
            l_S_LedControl[u8i].u8OnTime = u8TurnOnTime - 1;
            u8TurnOffTime --;
            if (l_S_LedControl[u8i].u8OffTime != u8TurnOffTime)
            {
                l_S_LedControl[u8i].u8HoldTime = u8TurnOffTime;
            }
            l_S_LedControl[u8i].u8OffTime = u8TurnOffTime;
        }
    }
    LedOutputState();
}

/*----------------------------------------------
Function: Update leds to work with blink
Parameter: void
Return: void
----------------------------------------------*/
void LedUpdate(void)
{
    static uint8_t s_u8UpdatedTime;
    uint8_t u8i;
    bool bLedChanged;
    if (LED_MODE_NORMAL == l_S_LedMode)
    {
        u8i = u32GetSysTicks();
        if ((uint8_t)(u8i - s_u8UpdatedTime) >= LED_UPDATE_PERIOD)
        {
            s_u8UpdatedTime = u8i;
            bLedChanged = false;
            for (u8i=0;u8i<LED_QUANTIY;u8i++)
            {
                if (0 != l_S_LedControl[u8i].u8TwinkleCount)
                {
                    if (0 == l_S_LedControl[u8i].u8HoldTime)
                    {
                        if (0 == (l_u8LedState & c_a_u8BitMask[u8i]))
                        {
                            l_S_LedControl[u8i].u8HoldTime = l_S_LedControl[u8i].u8OnTime;
                        }
                        else
                        {
                            if (LED_INFINITE_TWINKLE != l_S_LedControl[u8i].u8TwinkleCount)
                            {
                                l_S_LedControl[u8i].u8TwinkleCount -- ;
                            }
                            l_S_LedControl[u8i].u8HoldTime = l_S_LedControl[u8i].u8OffTime;
                        }
                        l_u8LedState ^= c_a_u8BitMask[u8i];
                        bLedChanged = true;
                    }
                    else
                    {
                        l_S_LedControl[u8i].u8HoldTime -- ;
                    }
                }
            }
            if (bLedChanged)
            {
                LedOutputState();
            }
        }
    }
}

/*----------------------------------------------
Function: LEDs state enter sleep (All off)
Parameter: void
Return: void
----------------------------------------------*/
void LedEnterSleep(void)
{
    l_S_LedMode = LED_MODE_SLEEP;
    LedOutputState();
}

/*----------------------------------------------
Function: Restore current LEDs state after sleep
Parameter: void
Return: void
----------------------------------------------*/
void LedExitSleep(void)
{
    l_S_LedMode = LED_MODE_NORMAL;
    LedOutputState();
}

/*----------------------------------------------
Function: LEDs state enter test (All on)
Parameter: void
Return: void
----------------------------------------------*/
void LedEnterTest(void)
{
    l_S_LedMode = LED_MODE_TEST;
    LedOutputState();
}

/*----------------------------------------------
Function: Restore current LEDs state after sleep
Parameter: void
Return: void
----------------------------------------------*/
void LedExitTest(void)
{
    l_S_LedMode = LED_MODE_NORMAL;
    LedOutputState();
}

/*----------------------------------------------
Function: Get LEDs setting
Parameter: LEDs
Return: LEDs setting
----------------------------------------------*/
LED_Mode_TypeDef LedGetSetting(LED_TypeDef Leds)
{
    uint8_t u8i;
    for (u8i=0;u8i<LED_QUANTIY;u8i++)
    {
        if (Leds & c_a_u8BitMask[u8i])
        {
            if (0 != l_S_LedControl[u8i].u8TwinkleCount)
            {
                return LED_MODE_TWINKLE;
            }
            else if (l_u8LedState & c_a_u8BitMask[u8i])
            {
                return LED_MODE_ON;
            }
            else
            {
                return LED_MODE_OFF;
            }
        }
    }
    return LED_MODE_OFF;
}

/*----------------------------------------------
Function: Get LEDs State
Parameter: void
Return: LEDs State
----------------------------------------------*/
uint8_t u8LedGetState(void)
{
    return l_u8LedState;
}

/*----------------------------------------------
Function: Output LEDs State
Parameter: void
Return: void
----------------------------------------------*/
static void LedOutputState(void)
{
    uint8_t u8LedVoltage;
    if (LED_MODE_NORMAL == l_S_LedMode)
    {
        u8LedVoltage = l_u8LedState ^ (LED_TURN_ON_VOLTAGE ? 0 : LED_ALL);
    }
    else if (LED_MODE_SLEEP == l_S_LedMode)
    {
        u8LedVoltage = LED_TURN_ON_VOLTAGE ? 0 : LED_ALL;
    }
    else if (LED_MODE_TEST == l_S_LedMode)
    {
        u8LedVoltage = LED_TURN_ON_VOLTAGE ? LED_ALL : 0;
    }
    else
    {
    }
  #ifdef LED0_PIN
    LED0_PIN = (bool)(u8LedVoltage & Bit0);
  #endif
  #ifdef LED1_PIN
    LED1_PIN = (bool)(u8LedVoltage & Bit1);
  #endif
  #ifdef LED2_PIN
    LED2_PIN = (bool)(u8LedVoltage & Bit2);
  #endif
  #ifdef LED3_PIN
    LED3_PIN = (bool)(u8LedVoltage & Bit3);
  #endif
  #ifdef LED4_PIN
    LED4_PIN = (bool)(u8LedVoltage & Bit4);
  #endif
  #ifdef LED5_PIN
    LED5_PIN = (bool)(u8LedVoltage & Bit5);
  #endif
  #ifdef LED6_PIN
    LED6_PIN = (bool)(u8LedVoltage & Bit6);
  #endif
  #ifdef LED7_PIN
    LED7_PIN = (bool)(u8LedVoltage & Bit7);
  #endif
}
