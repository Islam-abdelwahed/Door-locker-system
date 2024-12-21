/*
 * EEPROM.c
 *
 * Created: 8/3/2021 4:14:26 PM
 *  Author: ahmed
 */

#include "EEPROM.h"

#include <stdlib.h>

#define F_CPU 16000000

#include <util/delay.h>

#define Null (void * )(0)

void EEPROM_INIT(void) {
        I2C_Init_Master();
}

void EEPROM_WriteByte(uint8 Device_Page, uint8 Data_Add, uint8 Data) {
        if (Device_Page > 7)
                Device_Page = 7;

        //Device address calculation
        uint8 Device_Add = 0X50 | Device_Page;

        //Sending start condition
        I2C_Start_Cond();

        //sending slave address with write operation
        I2C_Send_SlaveAddress_Operation(Device_Add,Write);

        //sending data byte address
        I2C_Write_Byte(Data_Add);

        //sending the data byte
        I2C_Write_Byte(Data);

        //Sending stop condition
        I2C_Stop_Cond();

        _delay_ms(10);
}

void EEPROM_WriteMultiBytes(uint8 Device_Page, uint8 Data_Add, uint8 * Data, uint8 Data_Size) {
        if (Device_Page > 7)
                Device_Page = 7;

        //Device address calculation
        uint8 Device_Add = 0X50 | Device_Page;

        //Sending start condition
        I2C_Start_Cond();

        //sending slave address with write operation
        I2C_Send_SlaveAddress_Operation(Device_Add,Write);

        //sending data byte address
        I2C_Write_Byte(Data_Add);

        //sending the data byte
        I2C_SendMultiData(Data, Data_Size);

        //Sending stop condition
        I2C_Stop_Cond();

        _delay_ms(10);
}
void EEPROM_WriteString(uint8 Device_Page, uint8 Data_Add, uint8 * Data) {
        if (Device_Page > 7)
                Device_Page = 7;

        //Device address calculation
        uint8 Device_Add = 0X50 | Device_Page;

        //Sending start condition
        I2C_Start_Cond();

        //sending slave address with write operation
        I2C_Send_SlaveAddress_Operation(Device_Add,Write);

        //sending data byte address
        I2C_Write_Byte(Data_Add);

        //sending the data byte
        I2C_SendString(Data);

        //Sending stop condition
        I2C_Stop_Cond();

        _delay_ms(10);
}

uint8 EEPROM_ReadByte(uint8 Device_Page, uint8 Data_Add) {
        uint8 Data = 0;
        if (Device_Page > 7)
                Device_Page = 7;

        //Device address calculation
        uint8 Device_Add = 0X50 | Device_Page;

        //Sending start condition
        I2C_Start_Cond();

        //sending slave address with write operation
        I2C_Send_SlaveAddress_Operation(Device_Add,Write);

        //sending data byte address
        I2C_Write_Byte(Data_Add);

        //Sending repeated start condition
        I2C_Repeated_Start();

        //sending slave address with read operation
        I2C_Send_SlaveAddress_Operation(Device_Add,Read);

        //Receiving the data byte
        Data = I2C_Read_Byte();

        //Sending stop condition
        I2C_Stop_Cond();

        return Data;
}
void EEPROM_ReadMultiByte(uint8 Device_Page, uint8 Data_Add, uint8 * Rec_Loc, uint8 Data_Size) {
        uint8 i;
        if (Device_Page > 7)
                Device_Page = 7;

        //Device address calculation
        uint8 Device_Add = 0X50 | Device_Page;

        //Sending start condition
        I2C_Start_Cond();

        //sending slave address with write operation
        I2C_Send_SlaveAddress_Operation(Device_Add,Write);

        //sending data byte address
        I2C_Write_Byte(Data_Add);

        //Sending repeated start condition
        I2C_Repeated_Start();

        //sending slave address with read operation
        I2C_Send_SlaveAddress_Operation(Device_Add,Read);

        //Receiving the data byte
        for (i = 0; i < Data_Size; i++) {
                Rec_Loc[i] = I2C_Read_Byte();
        }

        //Sending stop condition
        I2C_Stop_Cond();
}