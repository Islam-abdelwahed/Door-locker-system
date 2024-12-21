#include "../HAL/LCD/LCD.h"
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/Servo Motor/Servo_Motor.h"
#include "../HAL/Buzzer/Buzzer.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/eeprom.h>

void controlDoor(uint8* msg,uint16 deg);
void enterSystem();
void getPSW(uint8* msg,uint8* pass);


void enterSystem(){
	controlDoor("Door will open in ",600);
block:
	LCD_CLR();
	LCD_WRITE_STRING("1.Change Password");
	LOCATE_CURSOR(1,0);
	LCD_WRITE_STRING("2.Lock Door");
	_bool_ s=true;
	while(s){
		uint8 key=keypadGetValue();
		if(key){
			BUZZER_SHORT_BEEP();
			switch(key){
				case '1':
					{
					uint8 newPass[8];
					getPSW("Enter new Password",newPass);
					eeprom_update_block(newPass,(void*)100,8);
					goto block;
					}
				break;
				
				case '2':
				controlDoor("Door will lock in ",130);
				s=false;
				break;
			}
			
		}
	}
}

void controlDoor(uint8* msg,uint16 deg){
	for(uint8 x=3;x>0;x--){
		LCD_CLR();
		LOCATE_CURSOR(1,0);
		LCD_WRITE_STRING(msg);
		LCD_WRITE_INTEGER(x);
		LCD_WRITE_CHAR('s');
		_delay_ms(1000);
	}
	ServoMotor_Start();
	OCR1A = deg;
	
}

void getPSW(uint8* msg,uint8* pass){
	LCD_CLR();
	LOCATE_CURSOR(1,0);
	LCD_WRITE_STRING(msg);
	LOCATE_CURSOR(3,5);
	uint8 cont=0;
	while(cont<8){
		uint8 key=keypadGetValue();
		if(key){
			BUZZER_SHORT_BEEP();
			if(key=='c'){
				LCD_CLR();
				LOCATE_CURSOR(1,0);
				LCD_WRITE_STRING(msg);
				LOCATE_CURSOR(3,5);
				cont=0;
				pass[0]='\0';
				}else{
				LCD_WRITE_CHAR('*');
				pass[cont]=key;
				cont++;
			}
		}
	}
	
}

uint8 strcomp(uint8* readed, uint8* enpass)
{
	for (uint8 i=0;i<8;i++)
	{
		if(readed[i]!=enpass[i])
		return 0;
	}
	return 1;
}

int main(void)
{
	DDRD|=0x20;
	uint8 try=2;
	LCD_INIT();
	KEYPAD_INIT();
	BUZZER_Init();
	ServoMotor_Init();
	LOCATE_CURSOR(1,6);
	LCD_WRITE_STRING("Welcome");
	
	_delay_ms(3000);
	LCD_CLR();
	/* Replace with your application code */
	while (1)
	{
		uint8 readed[8];
			eeprom_read_block(readed,(void*)100,8);
			if(readed[0]==255 && readed[1]==255)
			{
				
				getPSW("Set Door Password",readed);
				eeprom_write_block(readed,(void*)100,8);
				LCD_CLR();
				LOCATE_CURSOR(1,1);
				LCD_WRITE_STRING("Password Saved :)");
				_delay_ms(1500);
			}
		
		uint8 enpass[8];
		LCD_CLR();
		getPSW("Enter Door Password",enpass);
		
		if(strcomp(readed, enpass)){
			try=2;
			enterSystem();
		}
		else if(try==0){
			LCD_CLR();
			LOCATE_CURSOR(1,3);
			LCD_WRITE_STRING("You are Blocked");
			for(uint8 x=5;x>0;x--){
				BUZZER_LONG_BEEP();
				_delay_ms(1000);
				try=2;
			}
			}else{
			LCD_CLR();
			LOCATE_CURSOR(1,3);
			LCD_WRITE_STRING("Wrong Password");
			_delay_ms(2000);
			try--;
		}
	}
}

