/*====================================================
File    : typedef.h
Version : V1.1
Date    : 2015.3.10
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: 8051 series
====================================================*/

#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_ 1

typedef unsigned char char_t;
typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;
typedef float float32_t;
typedef double float64_t;

/* Access DoubleWord as an unsigned long variable or 4 unsigned byte variables */
typedef union DoubleWord
{
    unsigned long Data32;
    unsigned char Byte[4];
} DoubleWord_t;

/* Access Word as an unsigned int variable or 2 unsigned byte variables */
typedef union Word
{ 
    unsigned int Data16;
    unsigned char Byte[2];
} Word_t;

//typedef enum {RESET = 0, SET = !RESET}FlagStatus_TypeDef, ITStatus, BitStatus, BitAction;

typedef enum {DISABLE = 0, ENABLE = !DISABLE}FunctionalState_TypeDef;

#define FALSE 0
#define TRUE  1

#ifndef bool
    typedef unsigned char bool;
    #define true 1
    #define false 0
#endif

#define Bit0 0x01
#define Bit1 0x02
#define Bit2 0x04
#define Bit3 0x08
#define Bit4 0x10
#define Bit5 0x20
#define Bit6 0x40
#define Bit7 0x80

#endif /* _TYPEDEF_H_ */
