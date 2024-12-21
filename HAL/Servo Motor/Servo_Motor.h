#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_
#include "../../MCAL/TIMER/Timer.h"
#include "../../MCAL/DIO/DIO.h"

#define SERVO_PWM_PIN	DIO_PIN5
#define SERVO_PWM_PORT	DIO_PORTD

void ServoMotor_Init(void);

void ServoMotor_SetDegree(uint8 Deg);

void ServoMotor_Start(void);

void ServoMotor_Stop(void);

#endif /* SERVO_MOTOR_H_ */