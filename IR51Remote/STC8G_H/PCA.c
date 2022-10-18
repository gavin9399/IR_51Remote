/*====================================================
File    : pca.c
Version : V1.01
Date    : 2022.8.13
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G/H
====================================================*/

#include "pca.h"
#include "cpu.h"

static uint16_t l_u16PCA_Output_PWM_Cycle;
static PCA_Output_PWM_Bits_TypeDef l_PCA_Output_PWM_Bits;

#if USE_PCA_16BITS_PWM==TRUE
static uint16_t idata l_a_u16PCA_Output_PWM_HighTime[3];
static uint16_t idata l_a_u16PCA_Output_PWM_LowTime[3];
static uint32_t idata l_a_u32PCA_OutputWaveNumber[3];
bit g_bWave0Generating=false;
bit g_bWave1Generating=false;
bit g_bWave2Generating=false;
/*----------------------------------------------
Function: PCA output 16bits PWM interrupt routine
Parameter: void
Return: void
----------------------------------------------*/
void PCA_Output_16Bits_PWM_interrupt(void) interrupt PCA_VECTOR
{
    static Word_t W_CCAP0Reload, W_CCAP1Reload, W_CCAP2Reload;
    static bool b_PWM0OutPin=false, b_PWM1OutPin=false, b_PWM2OutPin=false;
    if (CCF0)
    {
        CCF0 = 0;
        b_PWM0OutPin = !b_PWM0OutPin;
        if(b_PWM0OutPin)
        {
            W_CCAP0Reload.Data16 += l_a_u16PCA_Output_PWM_HighTime[0];
        }
        else
        {
            W_CCAP0Reload.Data16 += l_a_u16PCA_Output_PWM_LowTime[0];
            if (0xFFFFFFFF != l_a_u32PCA_OutputWaveNumber[0])
            {
                if (0 != l_a_u32PCA_OutputWaveNumber[0])
                {
                    l_a_u32PCA_OutputWaveNumber[0]--;
                    if (0 == l_a_u32PCA_OutputWaveNumber[0])
                    {
                        CCAPM0 = 0;
                        g_bWave0Generating = false;
                    }
                }
                else
                {
                    CCAPM0 = 0;
                    g_bWave0Generating = false;
                }
            }
        }
        CCAP0L = W_CCAP0Reload.Byte[1];     /*Low byte first*/
        CCAP0H = W_CCAP0Reload.Byte[0];
    }
    else if (CCF1)
    {
        CCF1 = 0;
        b_PWM1OutPin = !b_PWM1OutPin;
        if(b_PWM1OutPin)
        {
            W_CCAP1Reload.Data16 += l_a_u16PCA_Output_PWM_HighTime[1];
        }
        else
        {
            W_CCAP1Reload.Data16 += l_a_u16PCA_Output_PWM_LowTime[1];
            if (0xFFFFFFFF != l_a_u32PCA_OutputWaveNumber[1])
            {
                if (0 != l_a_u32PCA_OutputWaveNumber[1])
                {
                    l_a_u32PCA_OutputWaveNumber[1]--;
                    if (0 == l_a_u32PCA_OutputWaveNumber[1])
                    {
                        CCAPM1 = 0;
                        g_bWave1Generating = false;
                    }
                }
                else
                {
                    CCAPM1 = 0;
                    g_bWave1Generating = false;
                }
            }
        }
        CCAP1L = W_CCAP1Reload.Byte[1];     /*Low byte first*/
        CCAP1H = W_CCAP1Reload.Byte[0];
    }
    else if (CCF2)
    {
        CCF2 = 0;
        b_PWM2OutPin = !b_PWM2OutPin;
        if(b_PWM2OutPin)
        {
            W_CCAP2Reload.Data16 += l_a_u16PCA_Output_PWM_HighTime[2];
        }
        else
        {
            W_CCAP2Reload.Data16 += l_a_u16PCA_Output_PWM_LowTime[2];
            if (0xFFFFFFFF != l_a_u32PCA_OutputWaveNumber[2])
            {
                if (0 != l_a_u32PCA_OutputWaveNumber[2])
                {
                    l_a_u32PCA_OutputWaveNumber[2]--;
                    if (0 == l_a_u32PCA_OutputWaveNumber[2])
                    {
                        CCAPM2 = 0;
                        g_bWave2Generating = false;
                    }
                }
                else
                {
                    CCAPM2 = 0;
                    g_bWave2Generating = false;
                }
            }
        }
        CCAP2L = W_CCAP2Reload.Byte[1];     /*Low byte first*/
        CCAP2H = W_CCAP2Reload.Byte[0];
    }
    else
    {
    }
}
/*----------------------------------------------
Function: Set PWM cycle function
Parameter: Cycle number
Return: void
Comments: This function is for the 16bits mode PWM output
----------------------------------------------*/
void PCA_SetPWM_Cycle(uint16_t u16PWM_Cycle)
{
    l_u16PCA_Output_PWM_Cycle = u16PWM_Cycle;
}
/*----------------------------------------------
Function: PCA output square wave
Parameter: PCA channel, Frequency (Hz), Wave Number
Return: void
Comments: PWM mode = 16bits
----------------------------------------------*/
void PCA_OutputSquareWave(PCA_Channel_TypeDef PCA_Channel, uint32_t u32Frequency, uint32_t u32WaveNumber)
{
    uint16_t u16Data;
    switch (CMOD & 0x0E)
    {
        case PCA_CLOCK_2T:
        u16Data = FOSC/2 / u32Frequency;
        break;
        case PCA_CLOCK_4T:
        u16Data = FOSC/4 / u32Frequency;
        break;
        case PCA_CLOCK_6T:
        u16Data = FOSC/6 / u32Frequency;
        break;
        case PCA_CLOCK_8T:
        u16Data = FOSC/8 / u32Frequency;
        break;
        case PCA_CLOCK_12T:
        u16Data = FOSC/12 / u32Frequency;
        break;
        default:
        u16Data = FOSC / u32Frequency;
        break;
    }
    l_u16PCA_Output_PWM_Cycle = u16Data;
    u16Data /= 2;
    switch (PCA_Channel)
    {
        case PCA_CHANNEL0:
        CCAPM0 &= ~ECCF0;        /* Disable CCF interrupt */
        l_a_u16PCA_Output_PWM_HighTime[0] = u16Data;
        l_a_u16PCA_Output_PWM_LowTime[0] = l_u16PCA_Output_PWM_Cycle - u16Data;
        l_a_u32PCA_OutputWaveNumber[0] = u32WaveNumber;
        CCAPM0 = PCA_MODE_FAST_PULSE_OUTPUT | ECCF0;         /* Enable CCF interrupt */
        g_bWave0Generating = true;
        break;
        case PCA_CHANNEL1:
        CCAPM1 &= ~ECCF1;        /* Disable CCF interrupt */
        l_a_u16PCA_Output_PWM_HighTime[1] = u16Data;
        l_a_u16PCA_Output_PWM_LowTime[1] = l_u16PCA_Output_PWM_Cycle - u16Data;
        l_a_u32PCA_OutputWaveNumber[1] = u32WaveNumber;
        CCAPM1 = PCA_MODE_FAST_PULSE_OUTPUT | ECCF1;         /* Enable CCF interrupt */
        g_bWave1Generating = true;
        break;
        case PCA_CHANNEL2:
        CCAPM2 &= ~ECCF2;        /* Disable CCF interrupt */
        l_a_u16PCA_Output_PWM_HighTime[2] = u16Data;
        l_a_u16PCA_Output_PWM_LowTime[2] = l_u16PCA_Output_PWM_Cycle - u16Data;
        l_a_u32PCA_OutputWaveNumber[2] = u32WaveNumber;
        CCAPM2 = PCA_MODE_FAST_PULSE_OUTPUT | ECCF2;         /* Enable CCF interrupt */
        g_bWave2Generating = true;
        break;
        default:
        break;
    }
}
#endif

/*----------------------------------------------
Function: PCA base initialization
Parameter: PCA Channel, PCA Init Information
Return: void
----------------------------------------------*/
void PCA_Initialization(PCA_Channel_TypeDef PCA_Channel, PCA_Init_TypeDef* PCA_Inf)
{
  #if USE_PCA_16BITS_PWM==TRUE
    code const uint16_t c_a_u16PWM_CycleTable[]={256,128,64,1024,PCA_PWM_DEFAULT_CYCLE};
  #else
    code const uint16_t c_a_u16PWM_CycleTable[]={256,128,64,1024};
  #endif
    switch (PCA_Channel)
    {
        case PCA_COUNTER:
        CCON = 0;
        CL = 0;
        CH = 0;
        P_SW1 = (P_SW1 & ~(CCP_S1|CCP_S0)) | PCA_Inf->IO_Switch;
        CMOD = PCA_Inf->Clock | PCA_Inf->IdleCounter | PCA_Inf->Interrupt;
        break;
        case PCA_CHANNEL0:
        if (PCA_MODE_PWM_OUT == (PCA_Inf->Mode & PCA_MODE_PWM_OUT))
        {
            l_PCA_Output_PWM_Bits = PCA_Inf->PWM_Bits;
            l_u16PCA_Output_PWM_Cycle = c_a_u16PWM_CycleTable[l_PCA_Output_PWM_Bits];
            switch (PCA_Inf->IO_Switch)
            {
                case PCA_AT_P12_P11_P10_P37:
                P1 &= ~Bit1;
                P1M0 |= Bit1;
                P1M1 &= ~Bit1;
                break;
                case PCA_AT_P34_P35_P36_P37:
                P3 &= ~Bit5;
                P3M0 |= Bit5;
                P3M1 &= ~Bit5;
                break;
                case PCA_AT_P24_P25_P26_P27:
                P2 &= ~Bit5;
                P2M0 |= Bit5;
                P2M1 &= ~Bit5;
                break;
                default :
                break;
            }
          #if USE_PCA_16BITS_PWM==TRUE
            if (PCA_16BITS_PWM == l_PCA_Output_PWM_Bits)
            {
                CCAPM0 = PCA_MODE_FAST_PULSE_OUTPUT;
                PCA_SetPWM_Duty(PCA_CHANNEL0,PCA_PWM_MIN_HIGH_TIME);
                l_a_u32PCA_OutputWaveNumber[0] = 0xFFFFFFFF;
            }
            else
          #endif
            {
                CCAPM0 = PCA_Inf->Mode;
                PCA_PWM0 = (l_PCA_Output_PWM_Bits << 6) | (EPC0H | EPC0L);
            }
        }
        else
        {
            CCAPM0 = PCA_Inf->Mode | PCA_Inf->Interrupt;
        }
        break;
        case PCA_CHANNEL1:
        if (PCA_MODE_PWM_OUT == (PCA_Inf->Mode & PCA_MODE_PWM_OUT))
        {
            l_PCA_Output_PWM_Bits = PCA_Inf->PWM_Bits;
            l_u16PCA_Output_PWM_Cycle = c_a_u16PWM_CycleTable[l_PCA_Output_PWM_Bits];
            switch (PCA_Inf->IO_Switch)
            {
                case PCA_AT_P12_P11_P10_P37:
                P1 &= ~Bit0;
                P1M0 |= Bit0;
                P1M1 &= ~Bit0;
                break;
                case PCA_AT_P34_P35_P36_P37:
                P3 &= ~Bit6;
                P3M0 |= Bit6;
                P3M1 &= ~Bit6;
                break;
                case PCA_AT_P24_P25_P26_P27:
                P2 &= ~Bit6;
                P2M0 |= Bit6;
                P2M1 &= ~Bit6;
                break;
                default :
                break;
            }
          #if USE_PCA_16BITS_PWM==TRUE
            if (PCA_16BITS_PWM == l_PCA_Output_PWM_Bits)
            {
                CCAPM1 = PCA_MODE_FAST_PULSE_OUTPUT;
                PCA_SetPWM_Duty(PCA_CHANNEL1,PCA_PWM_MIN_HIGH_TIME);
                l_a_u32PCA_OutputWaveNumber[1] = 0xFFFFFFFF;
            }
            else
          #endif
            {
                CCAPM1 = PCA_Inf->Mode;
                PCA_PWM1 = (l_PCA_Output_PWM_Bits << 6) | (EPC1H | EPC1L);
            }
        }
        else
        {
            CCAPM1 = PCA_Inf->Mode | PCA_Inf->Interrupt;
        }
        break;
        case PCA_CHANNEL2:
        if (PCA_MODE_PWM_OUT == (PCA_Inf->Mode & PCA_MODE_PWM_OUT))
        {
            l_PCA_Output_PWM_Bits = PCA_Inf->PWM_Bits;
            l_u16PCA_Output_PWM_Cycle = c_a_u16PWM_CycleTable[l_PCA_Output_PWM_Bits];
            switch (PCA_Inf->IO_Switch)
            {
                case PCA_AT_P12_P11_P10_P37:
                P3 &= ~Bit7;
                P3M0 |= Bit7;
                P3M1 &= ~Bit7;
                break;
                case PCA_AT_P34_P35_P36_P37:
                P3 &= ~Bit7;
                P3M0 |= Bit7;
                P3M1 &= ~Bit7;
                break;
                case PCA_AT_P24_P25_P26_P27:
                P2 &= ~Bit7;
                P2M0 |= Bit7;
                P2M1 &= ~Bit7;
                break;
                default :
                break;
            }
          #if USE_PCA_16BITS_PWM==TRUE
            if (PCA_16BITS_PWM == l_PCA_Output_PWM_Bits)
            {
                CCAPM2 = PCA_MODE_FAST_PULSE_OUTPUT;
                PCA_SetPWM_Duty(PCA_CHANNEL2,PCA_PWM_MIN_HIGH_TIME);
                l_a_u32PCA_OutputWaveNumber[2] = 0xFFFFFFFF;
            }
            else
          #endif
            {
                CCAPM2 = PCA_Inf->Mode;
                PCA_PWM2 = (l_PCA_Output_PWM_Bits << 6) | (EPC2H | EPC2L);
            }
        }
        else
        {
            CCAPM2 = PCA_Inf->Mode | PCA_Inf->Interrupt;
        }
        break;
    }
    PCA_Priority(PCA_Inf->Priority);
    CR = PCA_Inf->Run;
}

/*----------------------------------------------
Function: Set PWM duty function
Parameter: PCA channel, High pulse number
Return: void
----------------------------------------------*/
void PCA_SetPWM_Duty(PCA_Channel_TypeDef PCA_Channel, uint16_t u16PWM_HighLevelTime)
{
    uint16_t u16Value;
    uint8_t u8Value;
  #if USE_PCA_16BITS_PWM==TRUE
    if (PCA_16BITS_PWM == l_PCA_Output_PWM_Bits)
    {
        if(u16PWM_HighLevelTime > PCA_PWM_MAX_HIGH_TIME)
        {
            u16PWM_HighLevelTime = PCA_PWM_MAX_HIGH_TIME;
        }
        if(u16PWM_HighLevelTime < PCA_PWM_MIN_HIGH_TIME)
        {
            u16PWM_HighLevelTime = PCA_PWM_MIN_HIGH_TIME;
        }
        switch (PCA_Channel)
        {
            case PCA_CHANNEL0:
            CCAPM0 &= ~ECCF0;        /*Disable CCF interrupt */
            l_a_u16PCA_Output_PWM_HighTime[0] = u16PWM_HighLevelTime;
            l_a_u16PCA_Output_PWM_LowTime[0] = l_u16PCA_Output_PWM_Cycle - u16PWM_HighLevelTime;
            CCAPM0 |= ECCF0;         /*Enable CCF interrupt */
            break;
            case PCA_CHANNEL1:
            CCAPM1 &= ~ECCF1;        /*Disable CCF interrupt */
            l_a_u16PCA_Output_PWM_HighTime[1] = u16PWM_HighLevelTime;
            l_a_u16PCA_Output_PWM_LowTime[1] = l_u16PCA_Output_PWM_Cycle - u16PWM_HighLevelTime;
            CCAPM1 |= ECCF1;         /*Enable CCF interrupt */
            break;
            case PCA_CHANNEL2:
            CCAPM2 &= ~ECCF2;        /*Disable CCF interrupt */
            l_a_u16PCA_Output_PWM_HighTime[2] = u16PWM_HighLevelTime;
            l_a_u16PCA_Output_PWM_LowTime[2] = l_u16PCA_Output_PWM_Cycle - u16PWM_HighLevelTime;
            CCAPM2 |= ECCF2;         /*Enable CCF interrupt */
            break;
            default :
            break;
        }
    }
    else
  #endif
    {
        if (u16PWM_HighLevelTime > l_u16PCA_Output_PWM_Cycle)
        {
            u16PWM_HighLevelTime = l_u16PCA_Output_PWM_Cycle;
        }
        u16Value = l_u16PCA_Output_PWM_Cycle - u16PWM_HighLevelTime;
        u8Value = (uint8_t)(u16Value >> 4) & 0x30;
        if (0 == u16PWM_HighLevelTime)
        {
            u8Value |= EPC0H;
        }
        switch (PCA_Channel)
        {
            case PCA_CHANNEL0:
            PCA_PWM0 = u8Value | (PCA_PWM0 & 0xCD);
            CCAP0H = (uint8_t)u16Value;
            break;
            case PCA_CHANNEL1:
            PCA_PWM1 = u8Value | (PCA_PWM1 & 0xCD);
            CCAP1H = (uint8_t)u16Value;
            break;
            case PCA_CHANNEL2:
            PCA_PWM2 = u8Value | (PCA_PWM2 & 0xCD);
            CCAP2H = (uint8_t)u16Value;
            break;
            default :
            break;
        }
    }
}
