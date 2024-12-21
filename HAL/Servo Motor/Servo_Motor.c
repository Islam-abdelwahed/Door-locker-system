#include "Servo_Motor.h"

void ServoMotor_Init(void){
	DIO_setPinDir(SERVO_PWM_PORT,SERVO_PWM_PIN,DIO_PIN_OUTPUT);
	PWM1_Init();
}

void ServoMotor_SetDegree(uint8 Deg){
	uint16 Duty= 5+(Deg * .36);
	PWM1_Generate(Duty);
}

void ServoMotor_Start(void){
	PWM1_Start();
}

void ServoMotor_Stop(void){
	//PWM1_Stop();
}
