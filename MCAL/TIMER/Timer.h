#ifndef TIMER_H_
#define TIMER_H_
#include "Timer_CFG.h"
#include "../../LIB/Atmega32_Registers.h"
#include "../../LIB/Bit_Math.h"
#include <avr/interrupt.h>
#define TIMER0_NORMAL_MODE 0

#define TIMER0_PWM_MODE 1

#define TIMER0_CTC_MODE 2

#define TIMER0_FAST_PWM_MODE 3


/******************************[ Timer0 ]**********************************/

void Timer0_Init(void);

void Timer0_Start(void);

void Timer0_Stop(void);

void Timer0_SetDelay(uint32 Delay_Ms);

void PWM0_Init(void);

void PWM0_Generate(uint16 Duty_Cycle);

void PWM0_Start(void);

void PWM0_Stop(void);

/******************************[ Timer1 ]**********************************/

void Timer1_Init(void);

void Timer1_Start(void);

void Timer1_Stop(void);

void Timer1_SetDelay(uint32 Delay_Ms);

void PWM1_Init(void);

void PWM1_Generate(uint16 Duty_Cycle);

void PWM1_Start(void);

void PWM1_Stop(void);

void ICU_Init(void);

/******************************[ Timer2 ]**********************************/

void PWM2_Init(void);

void PWM2_Generate(uint16 Duty_Cycle);

void PWM2_Start(void);

void PWM2_Stop(void);

#endif /* TIMER_H_ */