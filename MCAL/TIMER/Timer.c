#include "Timer.h"

volatile uint8 Timer0_OVF=0;
volatile uint8 Init_Val=0;

volatile uint32 Timer1_OVF=0;
volatile uint32 ICU_CaptValue_1=0;
volatile uint32 ICU_CaptValue_2=0;
volatile uint32 ICU_CaptValue_3=0;

volatile uint8 Cap_Counter=0;
void Timer0_Init(void){
	
	#if TIMER0_MODE == TIMER0_NORMAL_MODE
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	
	#elif TIMER0_MODE == TIMER0_PWM_MODE
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	
	#elif TIMER0_MODE == TIMER0_CTC_MODE
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	
	#elif TIMER0_MODE == TIMER0_FAST_PWM_MODE
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	
	#endif
	
	TIMSK |= 0x01;

	SREG  |= 0x80;

};

void Timer0_Start(void){
	TCCR0 =0x05;
	
};


void Timer0_Stop(void){
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
};

void Timer0_SetDelay(uint32 Delay_Ms){
	
	uint8 Tick_Time =(1024/16);
	
	uint32 Total_Ticks= (Delay_Ms*1000) /Tick_Time;
	
	Init_Val= 256 - (Total_Ticks%256);
	
	Timer0_OVF =Total_Ticks/256 ;
	
	TCNT0=Init_Val;
	Timer0_OVF++;
};


void Timer1_Init(void){
	TCCR1B |= 0x08;
	TIMSK |= 0x10;
	SREG |=0x80;
}

void Timer1_Start(void){
	TCCR1B |= 0x05;
}

void Timer1_Stop(void){
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}

void Timer1_SetDelay(uint32 Delay_Ms){
	if(Delay_Ms<=4000){
		
		uint8 Tick_Time=1024/16;
		
		uint8 Num_Ticks=(Delay_Ms*1000) /Tick_Time;
		
		OCR1A=Num_Ticks-1;
	}
}

void PWM0_Init(void){
	DDRB |= 0x08;
	TCCR0 |= 0x68;
}

void PWM0_Generate(uint16 Duty_Cycle){
	OCR0= ((Duty_Cycle*256)/100)-1;
}

void PWM0_Start(void){
	TCCR0 |=0x03;
}

void PWM0_Stop(void){
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	
}

void PWM1_Init(void){
	
	TCCR1A |= 0x82;
	TCCR1B |= 0x18;
	TCNT1=0;
	ICR1 =2499; //1250
}

void PWM1_Generate(uint16 Duty_Cycle){
	OCR1A =((Duty_Cycle*2499)/100) -1;
}

void PWM1_Start(void){
	TCCR1B |= 0x03;	//Presc 256
}

void PWM1_Stop(void){
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}


void ICU_Init(void){
	CLR_BIT(DDRD,6);
	
	ICR1=0x0000;
	TCCR1B |=0x41;
	TIMSK |= 0x24;
	SREG |=0x80;
	
}

void PWM2_Init(void){
	DDRD |=0x80;
	TCCR2 |=0x68;
}

void PWM2_Generate(uint16 Duty_Cycle){
	OCR2=((Duty_Cycle*256)/100)-1;
}

void PWM2_Start(void){
	//TCCR2 |=0x02; //8
	//TCCR2 |=0x03;//32
	TCCR2 |=0x04;//64
	//TCCR2 |=0x05;//128
	//TCCR2 |=0x06;//256
	//TCCR2 |=0x07;//1024
}

void PWM2_Stop(void){
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}



ISR(TIMER1_CAPT_vect){
	Cap_Counter++;
	if(Cap_Counter==1){
		
		ICU_CaptValue_1=ICR1;
		Timer1_OVF=0;
		CLR_BIT(TCCR1B,6);
		
	}
	else if(Cap_Counter==2){
		
		ICU_CaptValue_2=ICR1 + (Timer1_OVF*65536);
		SET_BIT(TCCR1B,6);
		
	}else if(Cap_Counter==3){
		ICU_CaptValue_3=ICR1 + (Timer1_OVF*65536);
		CLR_BIT(TIMSK,5);
	}
}

ISR(TIMER1_OVF_vect)
{
	Timer1_OVF++;
}