/*====================================================
File    : gpio.h
Version : V1.1
Date    : 2021.1.5
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G/H
====================================================*/

#ifndef _GPIO_H_
#define _GPIO_H_ 1

#include "typedef.h"

/**
  * @brief  Definition of the GPIO pins. Used by the @ref GPIO_Init function in
  * order to select the pins to be initialized.
  */

typedef enum
{
  GPIO_P0_0    = ((uint8_t)0x00),  /*!< Pin 0 selected */
  GPIO_P0_1    = ((uint8_t)0x01),  /*!< Pin 1 selected */
  GPIO_P0_2    = ((uint8_t)0x02),  /*!< Pin 2 selected */
  GPIO_P0_3    = ((uint8_t)0x03),  /*!< Pin 3 selected */
  GPIO_P0_4    = ((uint8_t)0x04),  /*!< Pin 4 selected */
  GPIO_P0_5    = ((uint8_t)0x05),  /*!< Pin 5 selected */
  GPIO_P0_6    = ((uint8_t)0x06),  /*!< Pin 6 selected */
  GPIO_P0_7    = ((uint8_t)0x07),  /*!< Pin 7 selected */
  GPIO_P0_LNIB = ((uint8_t)0x08),  /*!< Low nibble pins selected */
  GPIO_P0_HNIB = ((uint8_t)0x09),  /*!< High nibble pins selected */
  GPIO_P0_ALL  = ((uint8_t)0x0A),   /*!< All pins selected */
  GPIO_P1_0    = ((uint8_t)0x10),  /*!< Pin 0 selected */
  GPIO_P1_1    = ((uint8_t)0x11),  /*!< Pin 1 selected */
  GPIO_P1_2    = ((uint8_t)0x12),  /*!< Pin 2 selected */
  GPIO_P1_3    = ((uint8_t)0x13),  /*!< Pin 3 selected */
  GPIO_P1_4    = ((uint8_t)0x14),  /*!< Pin 4 selected */
  GPIO_P1_5    = ((uint8_t)0x15),  /*!< Pin 5 selected */
  GPIO_P1_6    = ((uint8_t)0x16),  /*!< Pin 6 selected */
  GPIO_P1_7    = ((uint8_t)0x17),  /*!< Pin 7 selected */
  GPIO_P1_LNIB = ((uint8_t)0x18),  /*!< Low nibble pins selected */
  GPIO_P1_HNIB = ((uint8_t)0x19),  /*!< High nibble pins selected */
  GPIO_P1_ALL  = ((uint8_t)0x1A),   /*!< All pins selected */
  GPIO_P2_0    = ((uint8_t)0x20),  /*!< Pin 0 selected */
  GPIO_P2_1    = ((uint8_t)0x21),  /*!< Pin 1 selected */
  GPIO_P2_2    = ((uint8_t)0x22),  /*!< Pin 2 selected */
  GPIO_P2_3    = ((uint8_t)0x23),  /*!< Pin 3 selected */
  GPIO_P2_4    = ((uint8_t)0x24),  /*!< Pin 4 selected */
  GPIO_P2_5    = ((uint8_t)0x25),  /*!< Pin 5 selected */
  GPIO_P2_6    = ((uint8_t)0x26),  /*!< Pin 6 selected */
  GPIO_P2_7    = ((uint8_t)0x27),  /*!< Pin 7 selected */
  GPIO_P2_LNIB = ((uint8_t)0x28),  /*!< Low nibble pins selected */
  GPIO_P2_HNIB = ((uint8_t)0x29),  /*!< High nibble pins selected */
  GPIO_P2_ALL  = ((uint8_t)0x2A),   /*!< All pins selected */
  GPIO_P3_0    = ((uint8_t)0x30),  /*!< Pin 0 selected */
  GPIO_P3_1    = ((uint8_t)0x31),  /*!< Pin 1 selected */
  GPIO_P3_2    = ((uint8_t)0x32),  /*!< Pin 2 selected */
  GPIO_P3_3    = ((uint8_t)0x33),  /*!< Pin 3 selected */
  GPIO_P3_4    = ((uint8_t)0x34),  /*!< Pin 4 selected */
  GPIO_P3_5    = ((uint8_t)0x35),  /*!< Pin 5 selected */
  GPIO_P3_6    = ((uint8_t)0x36),  /*!< Pin 6 selected */
  GPIO_P3_7    = ((uint8_t)0x37),  /*!< Pin 7 selected */
  GPIO_P3_LNIB = ((uint8_t)0x38),  /*!< Low nibble pins selected */
  GPIO_P3_HNIB = ((uint8_t)0x39),  /*!< High nibble pins selected */
  GPIO_P3_ALL  = ((uint8_t)0x3A),   /*!< All pins selected */
  GPIO_P4_0    = ((uint8_t)0x40),  /*!< Pin 0 selected */
  GPIO_P4_1    = ((uint8_t)0x41),  /*!< Pin 1 selected */
  GPIO_P4_2    = ((uint8_t)0x42),  /*!< Pin 2 selected */
  GPIO_P4_3    = ((uint8_t)0x43),  /*!< Pin 3 selected */
  GPIO_P4_4    = ((uint8_t)0x44),  /*!< Pin 4 selected */
  GPIO_P4_5    = ((uint8_t)0x45),  /*!< Pin 5 selected */
  GPIO_P4_6    = ((uint8_t)0x46),  /*!< Pin 6 selected */
  GPIO_P4_7    = ((uint8_t)0x47),  /*!< Pin 7 selected */
  GPIO_P4_LNIB = ((uint8_t)0x48),  /*!< Low nibble pins selected */
  GPIO_P4_HNIB = ((uint8_t)0x49),  /*!< High nibble pins selected */
  GPIO_P4_ALL  = ((uint8_t)0x4A),   /*!< All pins selected */
  GPIO_P5_0    = ((uint8_t)0x50),  /*!< Pin 0 selected */
  GPIO_P5_1    = ((uint8_t)0x51),  /*!< Pin 1 selected */
  GPIO_P5_2    = ((uint8_t)0x52),  /*!< Pin 2 selected */
  GPIO_P5_3    = ((uint8_t)0x53),  /*!< Pin 3 selected */
  GPIO_P5_4    = ((uint8_t)0x54),  /*!< Pin 4 selected */
  GPIO_P5_5    = ((uint8_t)0x55),  /*!< Pin 5 selected */
  GPIO_P5_6    = ((uint8_t)0x56),  /*!< Pin 6 selected */
  GPIO_P5_7    = ((uint8_t)0x57),  /*!< Pin 7 selected */
  GPIO_P5_LNIB = ((uint8_t)0x58),  /*!< Low nibble pins selected */
  GPIO_P5_HNIB = ((uint8_t)0x59),  /*!< High nibble pins selected */
  GPIO_P5_ALL  = ((uint8_t)0x5A)   /*!< All pins selected */
}GPIO_Pin_TypeDef;

/**
  * @brief  GPIO modes
  *
  * Bits definitions:
  * - Bit 2: Pn
  * - Bit 1: PnM1
  * - Bit 0: PnM0
  */
typedef enum
{
  GPIO_MODE_IN_FL       = (uint8_t)0x06,  /*!< Input floating */
  GPIO_MODE_IN_PU       = (uint8_t)0x04,  /*!< Input pull-up */
  GPIO_MODE_OUT_OD_LOW  = (uint8_t)0x03,  /*!< Output open-drain, low level */
  GPIO_MODE_OUT_PP_LOW  = (uint8_t)0x01,  /*!< Output push-pull, low level */
  GPIO_MODE_OUT_OD_HIZ  = (uint8_t)0x07,  /*!< Output open-drain, high-impedance level */
  GPIO_MODE_OUT_PP_HIGH = (uint8_t)0x05   /*!< Output push-pull, high level */
}GPIO_Mode_TypeDef;

extern void GPIO_Init(GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode);
extern void GPIO_Write(GPIO_Pin_TypeDef GPIO_Pin, uint8_t u8Value);

#endif  /* _GPIO_H_ */
