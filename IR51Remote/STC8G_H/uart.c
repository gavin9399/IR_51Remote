/* ====================================================
File    : uart.h
Version : V1.3
Date    : 2022.8.7
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     :
MCU type: STC8G/H
==================================================== */

#include "uart.h"
#include "cpu.h"
#include "system_timer.h"

#ifdef UART1
  #ifdef RS485_TE1
    static bit l_bRS485TransmitDelayFlag1=false;
    static uint8_t l_u8RxTimerRecord1;
  #endif
    /*  UART Receiver buffer  */
    static char_t idata l_a_cRx1Buffer[RX1_BUFFER_SIZE];
  #if RX1_BUFFER_SIZE<256
    static uint8_t l_uRx1WrIndex,l_uRx1RdIndex,l_uRx1Counter;
  #else
    static uint16_t l_uRx1WrIndex,l_uRx1RdIndex,l_uRx1Counter;
  #endif
    /*  This flag is set on UART Receiver buffer overflow  */
    static bit l_bRx1BufferOverflow=false;
    /*  UART Transmitter buffer  */
    static char_t idata l_a_cTx1Buffer[TX1_BUFFER_SIZE];
  #if TX1_BUFFER_SIZE<256
    static uint8_t l_uTx1WrIndex,l_uTx1RdIndex,l_uTx1Counter;
  #else
    static uint16_t l_uTx1WrIndex,l_uTx1RdIndex,l_uTx1Counter;
  #endif
    /*  This flag is set on UART Transmitter buffer busy  */
    static bit l_bSbufTx1Busy=false;
#endif

#ifdef UART2
  #ifdef RS485_TE2
    static bit l_bRS485TransmitDelayFlag2=false;
    static uint8_t l_u8RxTimerRecord2;
  #endif
    /*  UART Receiver buffer  */
    static char_t idata l_a_cRx2Buffer[RX2_BUFFER_SIZE];
  #if RX2_BUFFER_SIZE<256
    static uint8_t l_uRx2WrIndex,l_uRx2RdIndex,l_uRx2Counter;
  #else
    static uint16_t l_uRx2WrIndex,l_uRx2RdIndex,l_uRx2Counter;
  #endif
    /*  This flag is set on UART Receiver buffer overflow  */
    static bit l_bRx2BufferOverflow=false;
    /*  UART Transmitter buffer  */
    static char_t idata l_a_cTx2Buffer[TX2_BUFFER_SIZE];
  #if TX2_BUFFER_SIZE<256
    static uint8_t l_uTx2WrIndex,l_uTx2RdIndex,l_uTx2Counter;
  #else
    static uint16_t l_uTx2WrIndex,l_uTx2RdIndex,l_uTx2Counter;
  #endif
    /*  This flag is set on UART Transmitter buffer busy  */
    static bit l_bSbufTx2Busy=false;
#endif

#ifdef UART3
  #ifdef RS485_TE3
    static bit l_bRS485TransmitDelayFlag3=false;
    static uint8_t l_u8RxTimerRecord3;
  #endif
    /*  UART Receiver buffer  */
    static char_t idata l_a_cRx3Buffer[RX3_BUFFER_SIZE];
  #if RX3_BUFFER_SIZE<256
    static uint8_t l_uRx3WrIndex,l_uRx3RdIndex,l_uRx3Counter;
  #else
    static uint16_t l_uRx3WrIndex,l_uRx3RdIndex,l_uRx3Counter;
  #endif
    /*  This flag is set on UART Receiver buffer overflow  */
    static bit l_bRx3BufferOverflow=false;
    /*  UART Transmitter buffer  */
    static char_t idata l_a_cTx3Buffer[TX3_BUFFER_SIZE];
  #if TX3_BUFFER_SIZE<256
    static uint8_t l_uTx3WrIndex,l_uTx3RdIndex,l_uTx3Counter;
  #else
    static uint16_t l_uTx3WrIndex,l_uTx3RdIndex,l_uTx3Counter;
  #endif
    /*  This flag is set on UART Transmitter buffer busy  */
    static bit l_bSbufTx3Busy=false;
#endif

#ifdef UART4
  #ifdef RS485_TE4
    static bit l_bRS485TransmitDelayFlag4=false;
    static uint8_t l_u8RxTimerRecord4;
  #endif
    /*  UART Receiver buffer  */
    static char_t idata l_a_cRx4Buffer[RX4_BUFFER_SIZE];
  #if RX4_BUFFER_SIZE<256
    static uint8_t l_uRx4WrIndex,l_uRx4RdIndex,l_uRx4Counter;
  #else
    static uint16_t l_uRx4WrIndex,l_uRx4RdIndex,l_uRx4Counter;
  #endif
    /*  This flag is set on UART Receiver buffer overflow  */
    static bit l_bRx4BufferOverflow=false;
    /*  UART Transmitter buffer  */
    static char_t idata l_a_cTx4Buffer[TX4_BUFFER_SIZE];
  #if TX4_BUFFER_SIZE<256
    static uint8_t l_uTx4WrIndex,l_uTx4RdIndex,l_uTx4Counter;
  #else
    static uint16_t l_uTx4WrIndex,l_uTx4RdIndex,l_uTx4Counter;
  #endif
    /*  This flag is set on UART Transmitter buffer busy  */
    static bit l_bSbufTx4Busy=false;
#endif

/*----------------------------------------------
Function: UART Configuration
Parameter: UARTx, UART Configuration Information
Return: 0 success, other fail
----------------------------------------------*/
uint8_t u8UART_Configuration(uint8_t UARTx, UART_ConfInf_t *Inf)
{
    uint32_t u32Value;
  #ifdef UART1
    if(UART1 == UARTx)
    {
      #ifdef RS485_TE1
        l_bRS485TransmitDelayFlag1 = false;
      #endif
        l_uRx1WrIndex = 0;
        l_uRx1RdIndex = 0;
        l_uRx1Counter = 0;
        l_bRx1BufferOverflow = false;
        l_uTx1WrIndex = 0;
        l_uTx1RdIndex = 0;
        l_uTx1Counter = 0;
        l_bSbufTx1Busy = false;
        if(Inf->UART_Priority > Priority_3)
        {
            return 8;    /* 中断优先级错误 */
        }
        UART1_Priority(Inf->UART_Priority);    /* 指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3 */
        if((UART_9BIT_BRTX == Inf->UART_Mode) || (UART_8BIT_BRTX == Inf->UART_Mode))    /* 可变波特率 */
        {
            u32Value = (FOSC / 4) / Inf->UART_BaudRate;    /* 按1T计算 */
            if(u32Value >= 65536UL)
            {
                return 3;    /* 波特率错误 */
            }
            u32Value = 65536UL - u32Value;
            if(BRT_TIMER1 == Inf->UART_BRT_Use)
            {
                TR1 = 0;
                AUXR &= ~0x01;        /* S1 BRT Use Timer1; */
                TMOD &= ~(1<<6);    /* Timer1 set As Timer */
                TMOD &= ~0x30;        /* Timer1_16bitAutoReload; */
                AUXR |=  (1<<6);    /* Timer1 set as 1T mode */
                TH1 = (uint8_t)(u32Value>>8);
                TL1 = (uint8_t)u32Value;
                ET1 = 0;    /* 禁止中断 */
                TMOD &= ~0x40;    /* 定时 */
                INT_CLKO &= ~0x02;    /* 不输出时钟 */
                TR1  = 1;
            }
            else if(BRT_TIMER2 == Inf->UART_BRT_Use)
            {
                AUXR &= ~(1<<4);    /* Timer stop */
                AUXR |= 0x01;        /* S1 BRT Use Timer2; */
                AUXR &= ~(1<<3);    /* Timer2 set As Timer */
                AUXR |=  (1<<2);    /* Timer2 set as 1T mode */
                TH2 = (uint8_t)(u32Value>>8);
                TL2 = (uint8_t)u32Value;
                IE2  &= ~(1<<2);    /* 禁止中断 */
                AUXR |=  (1<<4);    /* Timer run enable */
            }
            else
            {
                return 2;    /* 波特率发生器错误 */
            }
        }
        else if(UART_SHIFT == Inf->UART_Mode)
        {
            if(ENABLE == Inf->BaudRateDouble)
            {
                AUXR |=  (1<<5);    /* 固定波特率SysClk/2 */
            }
            else
            {
                AUXR &= ~(1<<5);    /* 固定波特率SysClk/12 */
            }
        }
        else if(UART_9BIT_FIX == Inf->UART_Mode)    /* 固定波特率SysClk*2^SMOD/64 */
        {
            if(ENABLE == Inf->BaudRateDouble)
            {
                PCON |=  (1<<7);    /* 固定波特率SysClk/32 */
            }
            else
            {
                PCON &= ~(1<<7);    /* 固定波特率SysClk/64 */
            }
        }
        else
        {
            return 1;    /* 模式错误 */
        }
        SCON = (SCON & 0x3F) | Inf->UART_Mode;
        REN = Inf->UART_RxEnable;
        ES = Inf->UART_Interrupt;
        P_SW1 = (P_SW1 & 0x3F) | (Inf->UART_P_SW & 0xC0);    /* 切换IO */
        return 0;
    }
  #endif
    
  #ifdef UART2
    if(UART2 == UARTx)
    {
      #ifdef RS485_TE2
        l_bRS485TransmitDelayFlag2 = false;
      #endif
        l_uRx2WrIndex = 0;
        l_uRx2RdIndex = 0;
        l_uRx2Counter = 0;
        l_bRx2BufferOverflow = false;
        l_uTx2WrIndex = 0;
        l_uTx2RdIndex = 0;
        l_uTx2Counter = 0;
        l_bSbufTx2Busy = false;
        if(Inf->UART_Priority > Priority_3)
        {
            return 8;    /* 中断优先级错误 */
        }
        UART2_Priority(Inf->UART_Priority);    /* 指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3 */
        if((UART_9BIT_BRTX == Inf->UART_Mode) || (UART_8BIT_BRTX == Inf->UART_Mode))    /* 可变波特率 */
        {
            u32Value = (MAIN_Fosc / 4) / Inf->UART_BaudRate;    /* 按1T计算 */
            if(u32Value >= 65536UL)
            {
                return 3;    /* 波特率错误 */
            }
            u32Value = 65536UL - u32Value;
            if(BRT_TIMER2 == Inf->UART_BRT_Use)
            {
                AUXR &= ~(1<<4);    /* Timer stop */
                AUXR &= ~(1<<3);    /* Timer2 set As Timer */
                AUXR |=  (1<<2);    /* Timer2 set as 1T mode */
                TH2 = (uint8_t)(u32Value>>8);
                TL2 = (uint8_t)u32Value;
                IE2  &= ~(1<<2);    /* 禁止中断 */
                AUXR |=  (1<<4);    /* Timer run enable */
            }
            else
            {
                return 2;    /* 波特率发生器错误 */
            }
        }
        else
        {
            return 1;    /* 模式错误 */
        }
        if(UART_9BIT_BRTX == Inf->UART_Mode)
        {
            S2_9bit();
        }
        else
        {
            S2_8bit();
        }
        if(ENABLE == Inf->UART_RxEnable)
        {
            S2_RX_Enable();
        }
        else
        {
            S2_RX_Disable();
        }
        if(ENABLE == Inf->UART_Interrupt)
        {
            S2_Int_Enable();
        }
        else
        {
            S2_Int_Disable();
        }
        P_SW2 = (P_SW2 & ~1) | (Inf->UART_P_SW & 0x01);    /* 切换IO */
        return 0;
    }
  #endif
    
  #ifdef UART3
    if(UART3 == UARTx)
    {
      #ifdef RS485_TE3
        l_bRS485TransmitDelayFlag3 = false;
      #endif
        l_uRx3WrIndex = 0;
        l_uRx3RdIndex = 0;
        l_uRx3Counter = 0;
        l_bRx3BufferOverflow = false;
        l_uTx3WrIndex = 0;
        l_uTx3RdIndex = 0;
        l_uTx3Counter = 0;
        l_bSbufTx3Busy = false;
        if(Inf->UART_Priority > Priority_3)
        {
            return 8;    /* 中断优先级错误 */
        }
        UART3_Priority(Inf->UART_Priority);    /* 指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3 */
        if((UART_9BIT_BRTX == Inf->UART_Mode) || (UART_8BIT_BRTX == Inf->UART_Mode))    /* 可变波特率 */
        {
            u32Value = (MAIN_Fosc / 4) / Inf->UART_BaudRate;    /* 按1T计算 */
            if(u32Value >= 65536UL)
            {
                return 3;    /* 波特率错误 */
            }
            u32Value = 65536UL - u32Value;
            if(BRT_TIMER2 == Inf->UART_BRT_Use)
            {
                AUXR &= ~(1<<4);    /* Timer stop */
                S3_BRT_UseTimer2(); /* S3 BRT Use Timer2; */
                AUXR &= ~(1<<3);    /* Timer2 set As Timer */
                AUXR |=  (1<<2);    /* Timer2 set as 1T mode */
                TH2 = (uint8_t)(u32Value>>8);
                TL2 = (uint8_t)u32Value;
                IE2  &= ~(1<<2);    /* 禁止中断 */
                AUXR |=  (1<<4);    /* Timer run enable */
            }
            else if(BRT_TIMER3 == Inf->UART_BRT_Use)
            {
				S3_BRT_UseTimer3();		/* S3 BRT Use Timer3 */
				TH3 = (uint8_t)(u32Value>>8);
				TL3 = (uint8_t)u32Value;
				T4T3M &= 0xF0;
				T4T3M |= 0x0A;			/* Timer3 set As Timer, 1T mode, Start timer3 */
            }
            else
            {
                return 2;    /* 波特率发生器错误 */
            }
        }
        else
        {
            return 1;    /* 模式错误 */
        }
        if(UART_9BIT_BRTX == Inf->UART_Mode)
        {
            S3_9bit();
        }
        else
        {
            S3_8bit();
        }
        if(ENABLE == Inf->UART_RxEnable)
        {
            S3_RX_Enable();
        }
        else
        {
            S3_RX_Disable();
        }
        if(ENABLE == Inf->UART_Interrupt)
        {
            S3_Int_Enable();
        }
        else
        {
            S3_Int_Disable();
        }
        P_SW2 = (P_SW2 & ~2) | (Inf->UART_P_SW & 0x02);    /* 切换IO */
        return 0;
    }
  #endif
    
  #ifdef UART4
    if(UART4 == UARTx)
    {
      #ifdef RS485_TE4
        l_bRS485TransmitDelayFlag4 = false;
      #endif
        l_uRx4WrIndex = 0;
        l_uRx4RdIndex = 0;
        l_uRx4Counter = 0;
        l_bRx4BufferOverflow = false;
        l_uTx4WrIndex = 0;
        l_uTx4RdIndex = 0;
        l_uTx4Counter = 0;
        l_bSbufTx4Busy = false;
        if(Inf->UART_Priority > Priority_3)
        {
            return 8;    /* 中断优先级错误 */
        }
        UART4_Priority(Inf->UART_Priority);    /* 指定中断优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3 */
        if((UART_9BIT_BRTX == Inf->UART_Mode) || (UART_8BIT_BRTX == Inf->UART_Mode))    /* 可变波特率 */
        {
            u32Value = (MAIN_Fosc / 4) / Inf->UART_BaudRate;    /* 按1T计算 */
            if(u32Value >= 65536UL)
            {
                return 3;    /* 波特率错误 */
            }
            u32Value = 65536UL - u32Value;
            if(BRT_TIMER2 == Inf->UART_BRT_Use)
            {
                AUXR &= ~(1<<4);    /* Timer stop */
                S4_BRT_UseTimer2(); /* S4 BRT Use Timer2; */
                AUXR &= ~(1<<3);    /* Timer2 set As Timer */
                AUXR |=  (1<<2);    /* Timer2 set as 1T mode */
                TH2 = (uint8_t)(u32Value>>8);
                TL2 = (uint8_t)u32Value;
                IE2  &= ~(1<<2);    /* 禁止中断 */
                AUXR |=  (1<<4);    /* Timer run enable */
            }
            else if(BRT_TIMER4 == Inf->UART_BRT_Use)
            {
				S4_BRT_UseTimer4();		/* S4 BRT Use Timer4 */
				TH4 = (uint8_t)(u32Value>>8);
				TL4 = (uint8_t)u32Value;
				T4T3M &= 0x0F;
				T4T3M |= 0xA0;			/* Timer4 set As Timer, 1T mode, Start timer4 */
            }
            else
            {
                return 2;    /* 波特率发生器错误 */
            }
        }
        else
        {
            return 1;    /* 模式错误 */
        }
        if(UART_9BIT_BRTX == Inf->UART_Mode)
        {
            S4_9bit();
        }
        else
        {
            S4_8bit();
        }
        if(ENABLE == Inf->UART_RxEnable)
        {
            S4_RX_Enable();
        }
        else
        {
            S4_RX_Disable();
        }
        if(ENABLE == Inf->UART_Interrupt)
        {
            S4_Int_Enable();
        }
        else
        {
            S4_Int_Disable();
        }
        P_SW2 = (P_SW2 & ~4) | (Inf->UART_P_SW & 0x04);    /* 切换IO */
        return 0;
    }
  #endif
    return 10;    /* 错误 */
}

#ifdef UART1
/*----------------------------------------------
Function: Get the number of bytes (characters)
    available for reading from the serial port.
Parameter: void
Return: The number of bytes
----------------------------------------------*/
#if RX1_BUFFER_SIZE<256
uint8_t UART1_Available(void)
#else
uint16_t UART1_Available(void)
#endif
{
    return l_uRx1Counter;
}

/*----------------------------------------------
Function: Get a character from the UART Receiver buffer
Parameter: void
Return: Character received
----------------------------------------------*/
char _getkey(void)
{
    char_t cData;
    while (0 == l_uRx1Counter)
    {
        ;
    }
    ES = false;         /*  Disable serial interrupt */
    cData = l_a_cRx1Buffer[l_uRx1RdIndex];
    l_uRx1RdIndex++;
    if (l_uRx1RdIndex >= RX1_BUFFER_SIZE)
    {
        l_uRx1RdIndex = 0;
    }
    l_uRx1Counter--;
    ES = true;          /*  Enable serial interrupt */
    return cData;
}

/*----------------------------------------------
Function: Write a character to the UART Transmitter buffer
Parameter: Character to transmit
Return: Character transmitted
----------------------------------------------*/
char putchar(char cData)
{
    while (l_uTx1Counter >= TX1_BUFFER_SIZE)
    {
        ;
    }
    if (l_bSbufTx1Busy)
    {
        ES = false;         /* Disable serial interrupt */
        l_a_cTx1Buffer[l_uTx1WrIndex] = cData;
        l_uTx1WrIndex++;
        if (l_uTx1WrIndex >= TX1_BUFFER_SIZE)
        {
            l_uTx1WrIndex=0;
        }
        l_uTx1Counter++;
        ES = true;          /* Enable serial interrupt */
    }
    else
    {
      #ifdef RS485_TE1
        while (l_bRS485TransmitDelayFlag1 && ((uint8_t)((uint8_t)u32GetSysTicks()-l_u8RxTimerRecord1) < UART1_FRAME_INTERVAL))
        {
            SystemTimerUpdate();
        }
        REN = false;            /* Disable UART receive */
        RS485_TE1 = true;        /* Enable RS485 transmit */
        l_bRS485TransmitDelayFlag1 = false;
      #endif
        l_bSbufTx1Busy = true;
        SBUF = cData;
    }
    return cData;
}

/*----------------------------------------------
Function: UART interrupt service routine
Parameter: void
Return: void
----------------------------------------------*/
void uart1_rx_tx_isr(void) interrupt UART1_VECTOR
{
/* UART Receiver interrupt service routine */
    if (RI)
    {
        l_a_cRx1Buffer[l_uRx1WrIndex] = SBUF;
        RI = false;
        l_uRx1WrIndex++;
        if (l_uRx1WrIndex >= RX1_BUFFER_SIZE)
        {
            l_uRx1WrIndex = 0;
        }
        if (l_uRx1Counter < RX1_BUFFER_SIZE)
        {
            l_uRx1Counter++;
        }
        else
        {
            l_bRx1BufferOverflow = true;
            l_uRx1RdIndex = l_uRx1WrIndex;
        }
      #ifdef RS485_TE1
        l_bRS485TransmitDelayFlag1 = true;
        l_u8RxTimerRecord1 = u32GetSysTicks();
      #endif
    }
/* UART Transmitter interrupt service routine */
    if (TI)
    {
        TI = false;
        if (0 != l_uTx1Counter)
        {
            l_uTx1Counter--;
            SBUF = l_a_cTx1Buffer[l_uTx1RdIndex];
            l_uTx1RdIndex++;
            if (l_uTx1RdIndex >= TX1_BUFFER_SIZE)
            {
                l_uTx1RdIndex = 0;
            }
        }
        else
        {
          #ifdef RS485_TE1
            RS485_TE1 = false;   /* Disable RS485 transmit for receive */
            REN = true;         /* Enable UART receive */
          #endif
            l_bSbufTx1Busy = false;
        }
    }
}
#endif

#ifdef UART2
/*----------------------------------------------
Function: Get the number of bytes (characters)
    available for reading from the serial port.
Parameter: void
Return: The number of bytes
----------------------------------------------*/
#if RX2_BUFFER_SIZE<256
uint8_t UART2_Available(void)
#else
uint16_t UART2_Available(void)
#endif
{
    return l_uRx2Counter;
}

/*----------------------------------------------
Function: Get a character from the UART Receiver buffer
Parameter: void
Return: Character received
----------------------------------------------*/
char _getkey2(void)
{
    char_t cData;
    while (0 == l_uRx2Counter)
    {
        ;
    }
    S2_Int_Disable();         /*  Disable serial interrupt */
    cData = l_a_cRx2Buffer[l_uRx2RdIndex];
    l_uRx2RdIndex++;
    if (l_uRx2RdIndex >= RX2_BUFFER_SIZE)
    {
        l_uRx2RdIndex = 0;
    }
    l_uRx2Counter--;
    S2_Int_Enable();          /*  Enable serial interrupt */
    return cData;
}

/*----------------------------------------------
Function: Write a character to the UART Transmitter buffer
Parameter: Character to transmit
Return: Character transmitted
----------------------------------------------*/
char putchar2(char cData)
{
    while (l_uTx2Counter >= TX2_BUFFER_SIZE)
    {
        ;
    }
    if (l_bSbufTx2Busy)
    {
        S2_Int_Disable();         /* Disable serial interrupt */
        l_a_cTx2Buffer[l_uTx2WrIndex] = cData;
        l_uTx2WrIndex++;
        if (l_uTx2WrIndex >= TX2_BUFFER_SIZE)
        {
            l_uTx2WrIndex=0;
        }
        l_uTx2Counter++;
        S2_Int_Enable();          /* Enable serial interrupt */
    }
    else
    {
      #ifdef RS485_TE2
        while (l_bRS485TransmitDelayFlag2 && ((uint8_t)((uint8_t)u32GetSysTicks()-l_u8RxTimerRecord2) < UART2_FRAME_INTERVAL))
        {
            SystemTimerUpdate();
        }
        S2_RX_Disable();            /* Disable UART receive */
        RS485_TE2 = true;        /* Enable RS485 transmit */
        l_bRS485TransmitDelayFlag2 = false;
      #endif
        l_bSbufTx2Busy = true;
        S2BUF = cData;
    }
    return cData;
}

/*----------------------------------------------
Function: UART interrupt service routine
Parameter: void
Return: void
----------------------------------------------*/
void uart2_rx_tx_isr(void) interrupt UART2_VECTOR
{
/* UART Receiver interrupt service routine */
    if (RI2)
    {
        l_a_cRx2Buffer[l_uRx2WrIndex] = S2BUF;
        CLR_RI2();
        l_uRx2WrIndex++;
        if (l_uRx2WrIndex >= RX2_BUFFER_SIZE)
        {
            l_uRx2WrIndex = 0;
        }
        if (l_uRx2Counter < RX2_BUFFER_SIZE)
        {
            l_uRx2Counter++;
        }
        else
        {
            l_bRx2BufferOverflow = true;
            l_uRx2RdIndex = l_uRx2WrIndex;
        }
      #ifdef RS485_TE2
        l_bRS485TransmitDelayFlag2 = true;
        l_u8RxTimerRecord2 = u32GetSysTicks();
      #endif
    }
/* UART Transmitter interrupt service routine */
    if (TI2)
    {
        CLR_TI2();
        if (0 != l_uTx2Counter)
        {
            l_uTx2Counter--;
            S2BUF = l_a_cTx2Buffer[l_uTx2RdIndex];
            l_uTx2RdIndex++;
            if (l_uTx2RdIndex >= TX2_BUFFER_SIZE)
            {
                l_uTx2RdIndex = 0;
            }
        }
        else
        {
          #ifdef RS485_TE2
            RS485_TE2 = false;   /* Disable RS485 transmit for receive */
            S2_RX_Enable();         /* Enable UART receive */
          #endif
            l_bSbufTx2Busy = false;
        }
    }
}
#endif

#ifdef UART3
/*----------------------------------------------
Function: Get the number of bytes (characters)
    available for reading from the serial port.
Parameter: void
Return: The number of bytes
----------------------------------------------*/
#if RX3_BUFFER_SIZE<256
uint8_t UART3_Available(void)
#else
uint16_t UART3_Available(void)
#endif
{
    return l_uRx3Counter;
}

/*----------------------------------------------
Function: Get a character from the UART Receiver buffer
Parameter: void
Return: Character received
----------------------------------------------*/
char _getkey3(void)
{
    char_t cData;
    while (0 == l_uRx3Counter)
    {
        ;
    }
    S3_Int_Disable();         /*  Disable serial interrupt */
    cData = l_a_cRx3Buffer[l_uRx3RdIndex];
    l_uRx3RdIndex++;
    if (l_uRx3RdIndex >= RX3_BUFFER_SIZE)
    {
        l_uRx3RdIndex = 0;
    }
    l_uRx3Counter--;
    S3_Int_Enable();          /*  Enable serial interrupt */
    return cData;
}

/*----------------------------------------------
Function: Write a character to the UART Transmitter buffer
Parameter: Character to transmit
Return: Character transmitted
----------------------------------------------*/
char putchar3(char cData)
{
    while (l_uTx3Counter >= TX3_BUFFER_SIZE)
    {
        ;
    }
    if (l_bSbufTx3Busy)
    {
        S3_Int_Disable();         /* Disable serial interrupt */
        l_a_cTx3Buffer[l_uTx3WrIndex] = cData;
        l_uTx3WrIndex++;
        if (l_uTx3WrIndex >= TX3_BUFFER_SIZE)
        {
            l_uTx3WrIndex=0;
        }
        l_uTx3Counter++;
        S3_Int_Enable();          /* Enable serial interrupt */
    }
    else
    {
      #ifdef RS485_TE3
        while (l_bRS485TransmitDelayFlag3 && ((uint8_t)((uint8_t)u32GetSysTicks()-l_u8RxTimerRecord3) < UART3_FRAME_INTERVAL))
        {
            SystemTimerUpdate();
        }
        S3_RX_Disable();            /* Disable UART receive */
        RS485_TE3 = true;        /* Enable RS485 transmit */
        l_bRS485TransmitDelayFlag3 = false;
      #endif
        l_bSbufTx3Busy = true;
        S3BUF = cData;
    }
    return cData;
}

/*----------------------------------------------
Function: UART interrupt service routine
Parameter: void
Return: void
----------------------------------------------*/
void uart3_rx_tx_isr(void) interrupt UART3_VECTOR
{
/* UART Receiver interrupt service routine */
    if (RI3)
    {
        l_a_cRx3Buffer[l_uRx3WrIndex] = S3BUF;
        CLR_RI3();
        l_uRx3WrIndex++;
        if (l_uRx3WrIndex >= RX3_BUFFER_SIZE)
        {
            l_uRx3WrIndex = 0;
        }
        if (l_uRx3Counter < RX3_BUFFER_SIZE)
        {
            l_uRx3Counter++;
        }
        else
        {
            l_bRx3BufferOverflow = true;
            l_uRx3RdIndex = l_uRx3WrIndex;
        }
      #ifdef RS485_TE3
        l_bRS485TransmitDelayFlag3 = true;
        l_u8RxTimerRecord3 = u32GetSysTicks();
      #endif
    }
/* UART Transmitter interrupt service routine */
    if (TI3)
    {
        CLR_TI3();
        if (0 != l_uTx3Counter)
        {
            l_uTx3Counter--;
            S3BUF = l_a_cTx3Buffer[l_uTx3RdIndex];
            l_uTx3RdIndex++;
            if (l_uTx3RdIndex >= TX3_BUFFER_SIZE)
            {
                l_uTx3RdIndex = 0;
            }
        }
        else
        {
          #ifdef RS485_TE3
            RS485_TE3 = false;   /* Disable RS485 transmit for receive */
            S3_RX_Enable();         /* Enable UART receive */
          #endif
            l_bSbufTx3Busy = false;
        }
    }
}
#endif

#ifdef UART4
/*----------------------------------------------
Function: Get the number of bytes (characters)
    available for reading from the serial port.
Parameter: void
Return: The number of bytes
----------------------------------------------*/
#if RX4_BUFFER_SIZE<256
uint8_t UART4_Available(void)
#else
uint16_t UART4_Available(void)
#endif
{
    return l_uRx4Counter;
}

/*----------------------------------------------
Function: Get a character from the UART Receiver buffer
Parameter: void
Return: Character received
----------------------------------------------*/
char _getkey4(void)
{
    char_t cData;
    while (0 == l_uRx4Counter)
    {
        ;
    }
    S4_Int_Disable();         /*  Disable serial interrupt */
    cData = l_a_cRx4Buffer[l_uRx4RdIndex];
    l_uRx4RdIndex++;
    if (l_uRx4RdIndex >= RX4_BUFFER_SIZE)
    {
        l_uRx4RdIndex = 0;
    }
    l_uRx4Counter--;
    S4_Int_Enable();          /*  Enable serial interrupt */
    return cData;
}

/*----------------------------------------------
Function: Write a character to the UART Transmitter buffer
Parameter: Character to transmit
Return: Character transmitted
----------------------------------------------*/
char putchar4(char cData)
{
    while (l_uTx4Counter >= TX4_BUFFER_SIZE)
    {
        ;
    }
    if (l_bSbufTx4Busy)
    {
        S4_Int_Disable();         /* Disable serial interrupt */
        l_a_cTx4Buffer[l_uTx4WrIndex] = cData;
        l_uTx4WrIndex++;
        if (l_uTx4WrIndex >= TX4_BUFFER_SIZE)
        {
            l_uTx4WrIndex=0;
        }
        l_uTx4Counter++;
        S4_Int_Enable();          /* Enable serial interrupt */
    }
    else
    {
      #ifdef RS485_TE4
        while (l_bRS485TransmitDelayFlag4 && ((uint8_t)((uint8_t)u32GetSysTicks()-l_u8RxTimerRecord4) < UART4_FRAME_INTERVAL))
        {
            SystemTimerUpdate();
        }
        S4_RX_Disable();            /* Disable UART receive */
        RS485_TE4 = true;        /* Enable RS485 transmit */
        l_bRS485TransmitDelayFlag4 = false;
      #endif
        l_bSbufTx4Busy = true;
        S4BUF = cData;
    }
    return cData;
}

/*----------------------------------------------
Function: UART interrupt service routine
Parameter: void
Return: void
----------------------------------------------*/
void uart4_rx_tx_isr(void) interrupt UART4_VECTOR
{
/* UART Receiver interrupt service routine */
    if (RI4)
    {
        l_a_cRx4Buffer[l_uRx4WrIndex] = S4BUF;
        CLR_RI4();
        l_uRx4WrIndex++;
        if (l_uRx4WrIndex >= RX4_BUFFER_SIZE)
        {
            l_uRx4WrIndex = 0;
        }
        if (l_uRx4Counter < RX4_BUFFER_SIZE)
        {
            l_uRx4Counter++;
        }
        else
        {
            l_bRx4BufferOverflow = true;
            l_uRx4RdIndex = l_uRx4WrIndex;
        }
      #ifdef RS485_TE4
        l_bRS485TransmitDelayFlag4 = true;
        l_u8RxTimerRecord4 = u32GetSysTicks();
      #endif
    }
/* UART Transmitter interrupt service routine */
    if (TI4)
    {
        CLR_TI4();
        if (0 != l_uTx4Counter)
        {
            l_uTx4Counter--;
            S4BUF = l_a_cTx4Buffer[l_uTx4RdIndex];
            l_uTx4RdIndex++;
            if (l_uTx4RdIndex >= TX4_BUFFER_SIZE)
            {
                l_uTx4RdIndex = 0;
            }
        }
        else
        {
          #ifdef RS485_TE4
            RS485_TE4 = false;   /* Disable RS485 transmit for receive */
            S4_RX_Enable();         /* Enable UART receive */
          #endif
            l_bSbufTx4Busy = false;
        }
    }
}
#endif
