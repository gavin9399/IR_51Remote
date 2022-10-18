/*====================================================
File    : uart.h
Version : V1.3
Date    : 2022.8.7
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     :
MCU type: STC8G/H
====================================================*/

#ifndef _UART_H_
#define _UART_H_ 1

#include "typedef.h"
#include "cpu.h"

#define    UART1    1
//#define    UART2    2
//#define    UART3    3
//#define    UART4    4

#ifdef UART1
/* RS485 transmit enable port */
  #if 0
    sbit RS485_TE_PORT1=P1^1;
    #define RS485_TE1   RS485_TE_PORT1
    #define UART1_FRAME_INTERVAL  (2000/960)
  #endif
    /* UART Receiver buffer size */
    #define RX1_BUFFER_SIZE 2
    /* UART Transmitter buffer size */
    #define TX1_BUFFER_SIZE 2
  #if RX1_BUFFER_SIZE<256
    extern uint8_t UART1_Available(void);
  #else
    extern uint16_t UART1_Available(void);
  #endif
    extern char putchar(char cData);
    extern char _getkey(void);
#endif

#ifdef UART2
/* RS485 transmit enable port */
  #if 0
    sbit RS485_TE_PORT2=P1^2;
    #define RS485_TE2   RS485_TE_PORT2
    #define UART2_FRAME_INTERVAL  (2000/60)
  #endif
    /* UART Receiver buffer size */
    #define RX2_BUFFER_SIZE 8
    /* UART Transmitter buffer size */
    #define TX2_BUFFER_SIZE 8
  #if RX2_BUFFER_SIZE<256
    extern uint8_t UART2_Available(void);
  #else
    extern uint16_t UART2_Available(void);
  #endif
    extern char putchar2(char cData);
    extern char _getkey2(void);
#endif

#ifdef UART3
/* RS485 transmit enable port */
  #if 0
    sbit RS485_TE_PORT3=P1^3;
    #define RS485_TE3   RS485_TE_PORT3
    #define UART3_FRAME_INTERVAL  (2000/60)
  #endif
    /* UART Receiver buffer size */
    #define RX3_BUFFER_SIZE 8
    /* UART Transmitter buffer size */
    #define TX3_BUFFER_SIZE 8
  #if RX3_BUFFER_SIZE<256
    extern uint8_t UART3_Available(void);
  #else
    extern uint16_t UART3_Available(void);
  #endif
    extern char putchar3(char cData);
    extern char _getkey3(void);
#endif

#ifdef UART4
/* RS485 transmit enable port */
  #if 0
    sbit RS485_TE_PORT4=P1^4;
    #define RS485_TE4   RS485_TE_PORT4
    #define UART4_FRAME_INTERVAL  (2000/60)
  #endif
    /* UART Receiver buffer size */
    #define RX4_BUFFER_SIZE 8
    /* UART Transmitter buffer size */
    #define TX4_BUFFER_SIZE 8
  #if RX4_BUFFER_SIZE<256
    extern uint8_t UART4_Available(void);
  #else
    extern uint16_t UART4_Available(void);
  #endif
    extern char putchar4(char cData);
    extern char _getkey4(void);
#endif

#define    UART_SHIFT           0         /* ͬ����λ��� */
#define    UART_8BIT_BRTX       (1<<6)    /* 8λ����,�ɱ䲨���� */
#define    UART_9BIT_FIX        (2<<6)    /* 9λ����,�̶������� */
#define    UART_9BIT_BRTX       (3<<6)    /* 9λ����,�ɱ䲨���� */

#define    UART1_SW_P30_P31    0
#define    UART1_SW_P36_P37    (1<<6)
#define    UART1_SW_P16_P17    (2<<6)
#define    UART1_SW_P43_P44    (3<<6)
#define    UART2_SW_P10_P11    0
#define    UART2_SW_P46_P47    1
#define    UART3_SW_P00_P01    0
#define    UART3_SW_P50_P51    2
#define    UART4_SW_P02_P03    0
#define    UART4_SW_P52_P53    4

#define    BRT_TIMER1    1
#define    BRT_TIMER2    2
#define    BRT_TIMER3    3
#define    BRT_TIMER4    4

typedef struct
{ 
    uint8_t    UART_Mode;            /* ģʽ,         UART_SHIFT,UART_8BIT_BRTX,UART_9BIT_FIX,UART_9BIT_BRTX */
    uint8_t    UART_BRT_Use;        /* ʹ�ò�����,   BRT_TIMER1,BRT_TIMER2 */
    uint32_t    UART_BaudRate;        /* ������ */
    /* FunctionalState    MultiCommunicate;    ���ͨѶ����, ENABLE,DISABLE */
    FunctionalState_TypeDef    UART_RxEnable;        /* �������,   ENABLE,DISABLE */
    FunctionalState_TypeDef    BaudRateDouble;        /* �����ʼӱ�, ENABLE,DISABLE */
    FunctionalState_TypeDef    UART_Interrupt;        /* �жϿ���,   ENABLE,DISABLE */
    uint8_t    UART_Priority;        /* ���ȼ�,     Priority_0,Priority_1,Priority_2,Priority_3 */
    uint8_t    UART_P_SW;            /* �л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44 */
} UART_ConfInf_t;

extern uint8_t u8UART_Configuration(uint8_t UARTx, UART_ConfInf_t *Inf);

#endif  /* _UART_H_ */
