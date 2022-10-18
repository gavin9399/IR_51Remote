/*====================================================
File    : eeprom.h
Version : V1.12
Date    : 2022.10.14
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G
====================================================*/

#ifndef _EEPROM_H_
#define _EEPROM_H_ 1

#include "typedef.h"
#include "cpu.h"

/*Define ISP/IAP/EEPROM command*/
#define CMD_IDLE 0      /*Stand-By*/
#define CMD_READ 1      /*Byte-Read*/
#define CMD_PROGRAM 2   /*Byte-Program*/
#define CMD_ERASE 3     /*Sector-Erase*/

#define ENABLE_IAP 0x80

/*EEPROM start address*/
/************************** ISP/IAP *****************************
   型号    大小  扇区数  开始地址    结束地址   MOVC读偏移地址
STC8X1K08   4K   8扇区   0x0000  ~  0x0FFF       0x2000
STC8X1K16  12K   24扇区  0x0000  ~  0x2FFF       0x4000
STC8XxK32  32K   64扇区  0x0000  ~  0x7FFF       0x8000
STC8XxK60   4K   8扇区   0x0000  ~  0x0FFF       0xF000
*/
#define EEPROM_START_ADDRESS 0x2C00

#define u8IapReadByte(u16Address) (*((uint8_t code*)(u16Address+EEPROM_START_ADDRESS)))

extern void IapIdle(void);
extern void IapWriteByte(uint16_t u16Address, uint8_t u8Data);
extern void IapEraseSector(uint16_t u16Address);
extern void EEPROM_Write_n_Byte(uint16_t u16Address, uint8_t* p_u8Data, uint16_t u16Number);
extern void EEPROM_Read_n_Byte(uint16_t u16Address, uint8_t* p_u8Data, uint16_t u16Number);

#ifndef u8IapReadByte
extern uint8_t u8IapReadByte(uint16_t u16Address);
#endif

#endif  /* _EEPROM_H_ */
