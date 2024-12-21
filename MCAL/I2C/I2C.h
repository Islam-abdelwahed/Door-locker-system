#ifndef I2C_H_
#define I2C_H_
#include "../../LIB/STD.h"
#include "../../LIB/Atmega32_Registers.h"
#include "../../LIB/BIT_MATH.h"

typedef enum{
	Write,
	Read
}Operation;

#define START_ACK				0x08
#define REP_START_ACK			0x10
#define SLAVE_ADD_AND_WR_ACK	0x18
#define SLAVE_ADD_AND_RD_ACK	0x40
#define WR_BYTE_ACK				0x28
#define RD_BYTE_WITH_NACK		0x58
#define RD_BYTE_WITH_ACK		0x50
#define SLAVE_ADD_RCVD_RD_REQ	0xA8
#define SLAVE_ADD_RCVD_WR_REQ	0x60
#define SLAVE_DATA_RECEIVED		0x80
#define SLAVE_BYTE_TRANSMITTED	0xC0

void I2C_Init_Master(void);
void I2C_Init_Slave(void);
void I2C_Start_Cond(void);
void I2C_Repeated_Start(void);
void I2C_Send_SlaveAddress_Operation(uint8 addr,Operation op);
void I2C_Write_Byte(uint8 data);
uint8 I2C_Read_Byte(void);
void I2C_Stop_Cond(void);
void I2C_SendString(uint8* Data);
void I2C_SendMultiData(uint8 * Data, uint8 Data_Size);

#endif /* I2C_H_ */