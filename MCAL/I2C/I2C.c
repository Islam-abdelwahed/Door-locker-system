#include "I2C.h"

void I2C_Init_Master(void){
	TWBR =0x0C;
			SREG |= 1 << 7;
	CLR_BIT(TWSR,0);
	CLR_BIT(TWSR,1);
			
	//enable I2C
			SET_BIT(TWCR,0);
	SET_BIT(TWCR,2);
}
void I2C_Init_Slave(void){
	TWAR =(0x01<<1);
	
	//enable I2C
	SET_BIT(TWCR,2);
}
void I2C_Start_Cond(void){
	
	SET_BIT(TWCR,5);
	SET_BIT(TWCR,2);
	SET_BIT(TWCR,7);
	
	while(GET_BIT(TWCR,7)==0);
	
	while((TWSR& 0xF8)==START_ACK);
}
void I2C_Repeated_Start(void){
	
	SET_BIT(TWCR,5);
	SET_BIT(TWCR,2);
	SET_BIT(TWCR,7);
	
	while(GET_BIT(TWCR,7)==0);
	
	while((TWSR& 0xF8)==REP_START_ACK);

}
void I2C_Send_SlaveAddress_Operation(uint8 addr,Operation op){
	#if op == Write
	
		TWDR=(addr<<1);
		SET_BIT(TWCR,2);
		SET_BIT(TWCR,7);
	
		while(GET_BIT(TWCR,7)==0);
	
		while((TWSR& 0xF8)==SLAVE_ADD_AND_WR_ACK);
	
	#elif op == Read
	
		TWDR=(addr<<1) | (0x01);
		SET_BIT(TWCR,2);
		SET_BIT(TWCR,7);
		
		while(GET_BIT(TWCR,7)==0);
		
		while((TWSR & 0xF8)==SLAVE_ADD_AND_RD_ACK);
	
	#endif
}
void I2C_Write_Byte(uint8 data){
	
	TWDR=data;
	SET_BIT(TWCR,2);
	SET_BIT(TWCR,7);
	
	while(GET_BIT(TWCR,7)==0);
	
	while((TWSR & 0xF8)==WR_BYTE_ACK);
	
}
uint8 I2C_Read_Byte(void){
	SET_BIT(TWCR,2);
	SET_BIT(TWCR,7);
	
	while(GET_BIT(TWCR,7)==0);
	
	while((TWSR & 0xF8)==RD_BYTE_WITH_NACK);
	return TWDR;
}
void I2C_Stop_Cond(void){
	
	SET_BIT(TWCR,4);
	SET_BIT(TWCR,2);
	SET_BIT(TWCR,7);
	
	while(GET_BIT(TWCR,7)==0);
}
void I2C_SendString(uint8 * Data) {
	uint8 i = 0;
	while (Data[i] != '\0') {
		I2C_Write_Byte(Data[i]);
		i++;
	}
}
void I2C_SendMultiData(uint8 * Data, uint8 Data_Size) {
	uint8 i = 0;
	for (i = 0; i < Data_Size; i++) {
		I2C_Write_Byte(Data[i]);
	}
}
