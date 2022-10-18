/*====================================================
File    : IED.h
Version : V1.02
Date    : 2021.6.16
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

#ifndef _LED_H_
#define _LED_H_ 1

#include "typedef.h"

/*----------------------------------------------
The following parameters are based on the hardware configuration
----------------------------------------------*/
#ifdef STC8G
#define LED_QUANTIY         1   /*1~8*/
#define LED0_PIN            P55
#define LED0_PIN_INIT       GPIO_P5_5
#define LED_TURN_ON_VOLTAGE  0
#define LED_TURN_OFF_VOLTAGE (!LED_TURN_ON_VOLTAGE)
#endif

#ifdef STC8F
#define LED_QUANTIY         2   /*1~8*/
#define LED0_PIN            P30
#define LED1_PIN            P31
#define LED0_PIN_INIT       GPIO_PORTS_3,GPIO_PIN_0
#define LED1_PIN_INIT       GPIO_PORTS_3,GPIO_PIN_1
#define LED_TURN_ON_VOLTAGE  0
#define LED_TURN_OFF_VOLTAGE (!LED_TURN_ON_VOLTAGE)
#endif

#ifdef STC15
#define LED_QUANTIY         4   /*1~8*/
#define LED0_PIN            P30
#define LED1_PIN            P31
#define LED2_PIN            P27
#define LED3_PIN            P34
#define LED0_PIN_INIT       GPIO_PORTS_3,GPIO_PIN_0
#define LED1_PIN_INIT       GPIO_PORTS_3,GPIO_PIN_1
#define LED2_PIN_INIT       GPIO_PORTS_2,GPIO_PIN_7
#define LED3_PIN_INIT       GPIO_PORTS_3,GPIO_PIN_4
#define LED_TURN_ON_VOLTAGE  0
#define LED_TURN_OFF_VOLTAGE (!LED_TURN_ON_VOLTAGE)
#endif

#ifdef STC12C5A60S2
#define LED_QUANTIY         4   /*1~8*/
#define LED0_PIN            P30
#define LED1_PIN            P31
#define LED2_PIN            P42
#define LED3_PIN            P36
#define LED0_PIN_INIT       GPIO_PORTS_3,GPIO_PIN_0
#define LED1_PIN_INIT       GPIO_PORTS_3,GPIO_PIN_1
#define LED2_PIN_INIT       GPIO_PORTS_4,GPIO_PIN_2
#define LED3_PIN_INIT       GPIO_PORTS_3,GPIO_PIN_6
#define LED_TURN_ON_VOLTAGE  0
#define LED_TURN_OFF_VOLTAGE (!LED_TURN_ON_VOLTAGE)
#endif
/*----------------------------------------------
The above parameters are based on the hardware configuration
----------------------------------------------*/

/* LEDS - The LED number is the same as the bit position */
typedef enum
{
  LED_0    = ((uint8_t)0x01),  /*!< LED 0 selected */
  LED_1    = ((uint8_t)0x02),  /*!< LED 1 selected */
  LED_2    = ((uint8_t)0x04),  /*!< LED 2 selected */
  LED_3    = ((uint8_t)0x08),  /*!< LED 3 selected */
  LED_4    = ((uint8_t)0x10),  /*!< LED 4 selected */
  LED_5    = ((uint8_t)0x20),  /*!< LED 5 selected */
  LED_6    = ((uint8_t)0x40),  /*!< LED 6 selected */
  LED_7    = ((uint8_t)0x80),  /*!< LED 7 selected */
  LED_LNIB = ((uint8_t)0x0F),  /*!< Low nibble LEDs selected */
  LED_HNIB = ((uint8_t)0xF0),  /*!< High nibble LEDs selected */
  LED_ALL  = ((uint8_t)0xFF)   /*!< All LEDs selected */
} LED_TypeDef;

/* Modes */
typedef enum
{
  LED_MODE_OFF      = ((uint8_t)0x00),
  LED_MODE_ON       = ((uint8_t)0x01),
  LED_MODE_TOGGLE   = ((uint8_t)0x02),
  LED_MODE_TWINKLE  = ((uint8_t)0x04)
} LED_Mode_TypeDef;

/* Special Modes */
typedef enum
{
  LED_MODE_NORMAL   = ((uint8_t)0x00),
  LED_MODE_SLEEP    = ((uint8_t)0x01),
  LED_MODE_TEST     = ((uint8_t)0x02)
} LED_Special_Mode_TypeDef;

#define LED_INFINITE_TWINKLE        255
#define LED_UPDATE_PERIOD           50  /*50msec*/

/* Defaults */
#define LED_DEFAULT_ON_TIME         (500/LED_UPDATE_PERIOD)
#define LED_DEFAULT_OFF_TIME        (500/LED_UPDATE_PERIOD)

/* LED control structure */
typedef struct
{
  uint8_t u8TwinkleCount;   /* Twinkle cycles count */
  uint8_t u8OnTime;         /* LED turn on time (50msec) */
  uint8_t u8OffTime;        /* LED turn off time (50msec) */
  uint8_t u8HoldTime;       /* Time for next change */
} LedControl_t;

/*
 * Initialize LED Service.
 */
extern void LedInitialization(void);

/*
 * Set the LED ON/OFF/TOGGLE.
 */
extern void LedSet(LED_TypeDef Leds, LED_Mode_TypeDef Mode);

/*
 * Blink the LED.
 */
extern void LedTwinkle(LED_TypeDef Leds, uint8_t u8TwinkleNumber, uint8_t u8TurnOnTime, uint8_t u8TurnOffTime);

/*
 * Update leds to work with blink.(Call in 100 ms)
 */
extern void LedUpdate(void);

/*
 * Put LEDs in sleep state - store current values
 */
extern void LedEnterSleep(void);

/*
 * Retore LEDs from sleep state
 */
extern void LedExitSleep(void);

/*
 * Put LEDs in test state - store current values
 */
extern void LedEnterTest(void);

/*
 * Retore LEDs from test state
 */
extern void LedExitTest(void);

/*
 * Return LED set state
 */
extern LED_Mode_TypeDef LedGetSetting(LED_TypeDef Leds);

/*
 * Return LED state
 */
extern uint8_t u8LedGetState(void);

#endif  /* _LED_H_ */
