/*====================================================
File    : IrRemote.c
Version : V1.0
Date    : 2022.10.14
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G
====================================================*/

#include "cpu.h"
#include "gpio.h"
#include "pca.h"
#include "timer.h"
#include "eeprom.h"
#include "IrRemote.h"

static bit l_bIrReceiveStart=false;
static bit l_bIrReceiveFinish=false;
static uint8_t l_u8IrWaveIndex=0;
static xdata uint16_t l_a_u16IrWave[IR_WAVE_MAX_NUM];

/*----------------------------------------------
Function: Sine Initialization routine
Parameter: void
Return: void
----------------------------------------------*/
void IrRemoteInit(uint8_t Mode)
{
    PCA_Init_TypeDef Pca;
    Pca.IO_Switch = PCA_AT_P12_P11_P10_P37;
    Pca.Clock = PCA_CLOCK_12T;
    Pca.IdleCounter = DISABLE;
    Pca.Priority = PCA_Priority_0;
    if (IR_RECEIVE_MODE == Mode)
    {
        PCA0_none();
        PCA2_none();
        GPIO_Init(IR_OUT_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
        GPIO_Init(IR_IN_PIN_INIT, GPIO_MODE_IN_PU);
        Pca.Run = ENABLE;
        Pca.Interrupt = ENABLE;
        PCA_Initialization(PCA_COUNTER, &Pca);
        Pca.Mode = PCA_MODE_CHANGING_EDGE_CAPTURE;
        PCA_Initialization(PCA_CHANNEL1, &Pca);
        PCA1_none();
    }
    else
    {
        PCA1_none();
        Pca.Run = DISABLE;
        Pca.Interrupt = DISABLE;
        PCA_Initialization(PCA_COUNTER, &Pca);
        Pca.Mode = PCA_MODE_PWM_OUT;
        Pca.PWM_Bits = PCA_6BITS_PWM;
        PCA_Initialization(PCA_CHANNEL2, &Pca);
        PCA_SetPWM_Duty(PCA_CHANNEL2, 23);
        PCA2_none();
        Pca.Mode = PCA_MODE_SOFT_TIMER;
        Pca.Interrupt = ENABLE;
        PCA_Initialization(PCA_CHANNEL0, &Pca);
        GPIO_Init(IR_OUT_PIN_INIT, GPIO_MODE_OUT_PP_LOW);
    }
}
/*----------------------------------------------
Function: start read infrared
Parameter: void
Return: void
----------------------------------------------*/
void IrStartRead(void)
{
    l_bIrReceiveStart = false;
    l_u8IrWaveIndex = 0;
    CCF1 = 0;
    CCAPM1 = PCA_MODE_CHANGING_EDGE_CAPTURE|ECCF1;
}
/*----------------------------------------------
Function: Transmit infrared key
Parameter: key number
Return: void
----------------------------------------------*/
void IrTransmit(uint8_t u8Number)
{
    EEPROM_Read_n_Byte((uint16_t)u8Number*512, (uint8_t*)l_a_u16IrWave, IR_WAVE_MAX_NUM*2);
    l_u8IrWaveIndex = 0;
    PCA_Run();
}
/*----------------------------------------------
Function: Save infrared wave data
Parameter: key number
Return: true = seccess
----------------------------------------------*/
bool SaveIrWave(uint8_t u8Number)
{
    uint16_t u16Addr;
    if (l_bIrReceiveFinish)
    {
        u16Addr = (uint16_t)u8Number * 512;
        IapEraseSector(u16Addr);
        EEPROM_Write_n_Byte(u16Addr, (uint8_t*)l_a_u16IrWave, (uint16_t)l_u8IrWaveIndex*2);
        l_u8IrWaveIndex = 0;
        l_bIrReceiveFinish = false;
        return true;
    }
    else
    {
        return false;
    }
}
/*----------------------------------------------
Function: PCA interrupt routine
Parameter: void
Return: void
----------------------------------------------*/
void PCA_Output_16Bits_PWM_interrupt(void) interrupt PCA_VECTOR
{
    static uint16_t s_u16CCAP0_Keep, s_u16CCAP1_Keep;
    static uint8_t s_u8PCA_OverflowCount=0;
    static uint8_t s_u8PCA_CaptureCount=0;
    uint16_t u16Value;
    if (CCF0)   /* 红外波形发送 */
    {
        u16Value = l_a_u16IrWave[l_u8IrWaveIndex];
        if (65535 == u16Value)  /* 结束发送 */
        {
            PCA_Stop();
            PCA2_none();
            IR_OUT_PIN = 0;
        }
        else
        {
            s_u16CCAP0_Keep += u16Value;
            CCAP0L = (uint8_t)s_u16CCAP0_Keep;  /* Lower byte first!!! */
            CCAP0H = s_u16CCAP0_Keep >> 8;
            if (l_u8IrWaveIndex & 0x01)
            {
                PCA2_none();
                IR_OUT_PIN = 0;
            }
            else
            {
                PCA2_PWM_Output();  /* 打开载波 */
            }
            l_u8IrWaveIndex ++;
        }
        CCF0 = 0;
    }
    else if (CCF1)  /* 红外波形读取 */
    {
        s_u8PCA_CaptureCount = s_u8PCA_OverflowCount;
        u16Value = ((uint16_t)CCAP1H << 8) | CCAP1L;
        if(l_bIrReceiveStart)   /* 已接收信号起始边沿 */
        {
            l_a_u16IrWave[l_u8IrWaveIndex] = u16Value - s_u16CCAP1_Keep;
            if (l_a_u16IrWave[0] > 1250)    /* 起始低电平大于500us为有效码 */
            {
                l_u8IrWaveIndex ++;
            }
            else
            {
                l_bIrReceiveStart = false;
            }
        }
        else
        {
            l_bIrReceiveStart = true;
        }
        s_u16CCAP1_Keep = u16Value;
        CCF1 = 0;
    }
    else if (CF)
    {
        s_u8PCA_OverflowCount ++;
        if (l_bIrReceiveStart && ((uint8_t)(s_u8PCA_OverflowCount - s_u8PCA_CaptureCount) > 1)) /* 超时判定为接收完成 */
        {
            PCA1_none();
            l_bIrReceiveStart = false;
            l_bIrReceiveFinish = true;
        }
        CF = 0;
    }
    else if (CCF2)
    {
        CCF2 = 0;
    }
    else
    {
    }
}
