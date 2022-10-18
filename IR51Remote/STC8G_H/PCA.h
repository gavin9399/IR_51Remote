/*====================================================
File    : pca.h
Version : V1.01
Date    : 2022.8.13
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G/H
====================================================*/

#ifndef _PCA_H_
#define _PCA_H_ 1

#include "typedef.h"

#define USE_PCA_16BITS_PWM    FALSE  //TRUE   //

#define EPC0H (1<<1)
#define EPC0L (1<<0)
#define EPC1H (1<<1)
#define EPC1L (1<<0)
#define EPC2H (1<<1)
#define EPC2L (1<<0)
#define CCP_S0 (1<<4)
#define CCP_S1 (1<<5)

#define ECCF0       0x01
#define ECCF1       0x01
#define ECCF2       0x01

#if USE_PCA_16BITS_PWM==TRUE
    #define PCA_PWM_DEFAULT_CYCLE    4000
    #define PCA_PWM_MIN_HIGH_TIME    10
    #define PCA_PWM_MAX_HIGH_TIME    (l_u16PCA_Output_PWM_Cycle - PCA_PWM_MIN_HIGH_TIME)
#endif

/* PCA channel type define */
typedef enum
{
    PCA_CHANNEL0     = ((uint8_t)0),
    PCA_CHANNEL1     = ((uint8_t)1),
    PCA_CHANNEL2     = ((uint8_t)2),
    PCA_COUNTER      = ((uint8_t)3)
}PCA_Channel_TypeDef;

/* PCA output PWM type define */
typedef enum
{
  #if USE_PCA_16BITS_PWM==TRUE
    PCA_16BITS_PWM   = ((uint8_t)4),
  #endif
    PCA_10BITS_PWM   = ((uint8_t)3),
    PCA_6BITS_PWM    = ((uint8_t)2),
    PCA_7BITS_PWM    = ((uint8_t)1),
    PCA_8BITS_PWM    = ((uint8_t)0)
}PCA_Output_PWM_Bits_TypeDef;

/* PCA clock type define */
typedef enum
{
    PCA_CLOCK_1T    = ((uint8_t)(4<<1)),
    PCA_CLOCK_2T    = ((uint8_t)(1<<1)),
    PCA_CLOCK_4T    = ((uint8_t)(5<<1)),
    PCA_CLOCK_6T    = ((uint8_t)(6<<1)),
    PCA_CLOCK_8T    = ((uint8_t)(7<<1)),
    PCA_CLOCK_12T   = ((uint8_t)(0<<1)),
    PCA_CLOCK_T0T   = ((uint8_t)(2<<1)),
    PCA_CLOCK_ECI   = ((uint8_t)(3<<1))
}PCA_Clock_TypeDef;

/* PCA IO pin switch type define */
typedef enum
{
    PCA_AT_P12_P11_P10_P37     = ((uint8_t)(0<<4)),
    PCA_AT_P34_P35_P36_P37     = ((uint8_t)(1<<4)),
    PCA_AT_P24_P25_P26_P27     = ((uint8_t)(2<<4))
}PCA_IO_Switch_TypeDef;

/* PCA IO pin switch type define */
typedef enum
{
    PCA_Priority_0     = ((uint8_t)0),
    PCA_Priority_1     = ((uint8_t)1),
    PCA_Priority_2     = ((uint8_t)2),
    PCA_Priority_3     = ((uint8_t)3)
}PCA_Priority_TypeDef;

/* PCA mode type define */
typedef enum
{
    PCA_MODE_PWM_OUT                = ((uint8_t)0x42),
    PCA_MODE_PWM_OUT_RISING_INT     = ((uint8_t)0x63),
    PCA_MODE_PWM_OUT_TRAILING_INT   = ((uint8_t)0x53),
    PCA_MODE_PWM_OUT_CHANGING_INT   = ((uint8_t)0x73),
    PCA_MODE_RISING_EDGE_CAPTURE    = ((uint8_t)0x20),
    PCA_MODE_TRAILING_EDGE_CAPTURE  = ((uint8_t)0x10),
    PCA_MODE_CHANGING_EDGE_CAPTURE  = ((uint8_t)0x30),
    PCA_MODE_SOFT_TIMER             = ((uint8_t)0x48),
    PCA_MODE_FAST_PULSE_OUTPUT      = ((uint8_t)0x4C)
}PCA_Mode_TypeDef;

typedef struct
{
    PCA_IO_Switch_TypeDef IO_Switch;
    PCA_Clock_TypeDef Clock;
    FunctionalState_TypeDef IdleCounter;
    FunctionalState_TypeDef Interrupt;
    PCA_Priority_TypeDef Priority;
    PCA_Mode_TypeDef Mode;
    PCA_Output_PWM_Bits_TypeDef PWM_Bits;
    FunctionalState_TypeDef Run;
}PCA_Init_TypeDef;

#define PCA_Run() CR=1
#define PCA_Stop() CR=0
#define PCA2_PWM_Output() CCAPM2=PCA_MODE_PWM_OUT

extern void PCA_Initialization(PCA_Channel_TypeDef PCA_Channel, PCA_Init_TypeDef* PCA_Inf);
extern void PCA_SetPWM_Duty(PCA_Channel_TypeDef PCA_Channel, uint16_t u16PWM_HighPulse);
#if USE_PCA_16BITS_PWM==TRUE
extern bit g_bWave0Generating;
extern bit g_bWave1Generating;
extern bit g_bWave2Generating;
extern void PCA_SetPWM_Cycle(uint16_t u16PWM_Cycle);
extern void PCA_OutputSquareWave(PCA_Channel_TypeDef PCA_Channel, uint32_t u32Frequency, uint32_t u32WaveNumber);
#endif

#endif  /* _PCA_H_ */
