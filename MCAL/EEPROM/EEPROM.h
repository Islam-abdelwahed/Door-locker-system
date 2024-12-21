/*
 * EEPROM.h
 *
 * Created: 8/3/2021 4:14:42 PM
 *  Author: ahmed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "../../LIB/STD.h"
#include "../../MCAL/I2C/I2C.h"

void EEPROM_INIT(void);

void EEPROM_WriteByte(uint8 Device_Page, uint8 Data_Add, uint8 Data);

void EEPROM_WriteMultiBytes(uint8 Device_Page, uint8 Data_Add, uint8* Data, uint8 Data_Size);

void EEPROM_WriteString(uint8 Device_Page, uint8 Data_Add, uint8* Data);

uint8 EEPROM_ReadByte(uint8 Device_Page, uint8 Data_Add);

void EEPROM_ReadMultiByte(uint8 Device_Page, uint8 Data_Add, uint8* Rec_Loc, uint8 Data_Size);


#endif /* EEPROM_H_ */