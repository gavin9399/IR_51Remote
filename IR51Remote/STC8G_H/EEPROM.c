/*====================================================
File    : eeprom.c
Version : V1.12
Date    : 2022.10.14
Author  : Gavin Hu
Company : ZJOU
Comments: 
IDE     : 
MCU type: STC8G
====================================================*/

#include "eeprom.h"
#include <intrins.h>

/*----------------------------------------------
Function: Disable ISP/IAP/EEPROM function
    Make MCU in a safe state
Parameter: void
Return: void
----------------------------------------------*/
void IapIdle(void)
{
    IAP_CONTR = 0;      /*Close IAP function*/
    IAP_CMD = 0;        /*Clear command to standby*/
    IAP_TRIG = 0;       /*Clear trigger register */
    IAP_ADDRH = 0x80;   /*Data ptr point to non-EEPROM area*/
    IAP_ADDRL = 0;      /*Clear IAP address to prevent misuse*/
}

/*----------------------------------------------
Function: Read one byte from ISP/IAP/EEPROM area
    Make MCU in a safe state
Parameter: u16Address (ISP/IAP/EEPROM address)
Return: EEPROM data
----------------------------------------------*/
#ifndef u8IapReadByte
uint8_t u8IapReadByte(uint16_t u16Address)
{
    uint8_t u8Data;                 /*Data buffer*/
    IAP_CONTR = ENABLE_IAP;         /*Open IAP function, and set wait time*/
    IAP_TPS = (FOSC+500000) / 1000000L;
    IAP_CMD = CMD_READ;             /*Set ISP/IAP/EEPROM READ command*/
    IAP_ADDRL = (uint8_t)u16Address;/*Set ISP/IAP/EEPROM address low*/
    IAP_ADDRH = u16Address >> 8;    /*Set ISP/IAP/EEPROM address high*/
    IAP_TRIG = 0x5A;                /*Send trigger command1 (0x5A)*/
    IAP_TRIG = 0xA5;                /*Send trigger command2 (0xA5)*/
    _nop_();                        /*MCU will hold here until ISP/IAP/EEPROM*/
    /*operation complete*/
    u8Data = IAP_DATA;              /*Read ISP/IAP/EEPROM data */
    IapIdle();                      /*Close ISP/IAP/EEPROM function*/
    return u8Data;                  /*Return Flash data */
}
#endif

/*----------------------------------------------
Function: Program one byte to ISP/IAP/EEPROM area
Parameter: u16Address (ISP/IAP/EEPROM address)
    u8Data (ISP/IAP/EEPROM data)
Return: void
----------------------------------------------*/
void IapWriteByte(uint16_t u16Address, uint8_t u8Data)
{
    IAP_CONTR = ENABLE_IAP;         /*Open IAP function, and set wait time*/
    IAP_TPS = (FOSC+500000) / 1000000L;
    IAP_CMD = CMD_PROGRAM;          /*Set ISP/IAP/EEPROM PROGRAM command*/
    IAP_ADDRL = (uint8_t)u16Address;/*Set ISP/IAP/EEPROM address low*/
    IAP_ADDRH = u16Address >> 8;    /*Set ISP/IAP/EEPROM address high*/
    IAP_DATA = u8Data;              /*Write ISP/IAP/EEPROM data */
    IAP_TRIG = 0x5A;                /*Send trigger command1 (0x5A)*/
    IAP_TRIG = 0xA5;                /*Send trigger command2 (0xA5)*/
    _nop_();                        /*MCU will hold here until ISP/IAP/EEPROM*/
    /*operation complete*/
    IapIdle();
}

/*----------------------------------------------
Function: Erase one sector area
Parameter: u16Address (ISP/IAP/EEPROM address)
Return: void
----------------------------------------------*/
void IapEraseSector(uint16_t u16Address)
{
    IAP_CONTR = ENABLE_IAP;         /*Open IAP function, and set wait time*/
    IAP_TPS = (FOSC+500000) / 1000000L;
    IAP_CMD = CMD_ERASE;            /*Set ISP/IAP/EEPROM ERASE command*/
    IAP_ADDRL = (uint8_t)u16Address;/*Set ISP/IAP/EEPROM address low*/
    IAP_ADDRH = u16Address >> 8;    /*Set ISP/IAP/EEPROM address high*/
    IAP_TRIG = 0x5A;                /*Send trigger command1 (0x5A)*/
    IAP_TRIG = 0xA5;                /*Send trigger command2 (0xA5)*/
    _nop_();                        /*MCU will hold here until ISP/IAP/EEPROM*/
    /*operation complete*/
    IapIdle();
}

/*----------------------------------------------
Function: Read n byte from ISP/IAP/EEPROM area
    Make MCU in a safe state
Parameter: u16Address (ISP/IAP/EEPROM address),
    data pointer, number to read
Return: void
----------------------------------------------*/
void EEPROM_Read_n_Byte(uint16_t u16Address, uint8_t* p_u8Data, uint16_t u16Number)
{
  #ifndef u8IapReadByte
    IAP_CONTR = ENABLE_IAP;         /*Open IAP function, and set wait time*/
    IAP_TPS = (FOSC+500000) / 1000000L;
    IAP_CMD = CMD_READ;             /*Set ISP/IAP/EEPROM READ command*/
    while (u16Number != 0)
    {
        IAP_ADDRL = (uint8_t)u16Address;/*Set ISP/IAP/EEPROM address low*/
        IAP_ADDRH = u16Address >> 8;    /*Set ISP/IAP/EEPROM address high*/
        IAP_TRIG = 0x5A;                /*Send trigger command1 (0x5A)*/
        IAP_TRIG = 0xA5;                /*Send trigger command2 (0xA5)*/
//        _nop_();                        /*MCU will hold here until ISP/IAP/EEPROM*/
        /*operation complete*/
        *p_u8Data = IAP_DATA;              /*Read ISP/IAP/EEPROM data */
        u16Address++;
        p_u8Data++;
        u16Number--;
    }
    IapIdle();                      /*Close ISP/IAP/EEPROM function*/
  #else
    u16Address += EEPROM_START_ADDRESS;
    while (u16Number != 0)
    {
        *p_u8Data = *((uint8_t code*)u16Address);
        u16Address++;
        p_u8Data++;
        u16Number--;
    }
  #endif
}

/*----------------------------------------------
Function: Write n byte to ISP/IAP/EEPROM area
Parameter: u16Address (ISP/IAP/EEPROM address),
    data pointer, number to read
Return: void
----------------------------------------------*/
void EEPROM_Write_n_Byte(uint16_t u16Address, uint8_t* p_u8Data, uint16_t u16Number)
{
    IAP_CONTR = ENABLE_IAP;         /*Open IAP function, and set wait time*/
    IAP_TPS = (FOSC+500000) / 1000000L;
    IAP_CMD = CMD_PROGRAM;          /*Set ISP/IAP/EEPROM PROGRAM command*/
    while (u16Number != 0)
    {
        IAP_ADDRL = (uint8_t)u16Address;/*Set ISP/IAP/EEPROM address low*/
        IAP_ADDRH = u16Address >> 8;    /*Set ISP/IAP/EEPROM address high*/
        IAP_DATA = *p_u8Data;              /*Write ISP/IAP/EEPROM data */
        IAP_TRIG = 0x5A;                /*Send trigger command1 (0x5A)*/
        IAP_TRIG = 0xA5;                /*Send trigger command2 (0xA5)*/
//        _nop_();                        /*MCU will hold here until ISP/IAP/EEPROM*/
        u16Address++;
        p_u8Data++;
        u16Number--;
    }
    /*operation complete*/
    IapIdle();
}

