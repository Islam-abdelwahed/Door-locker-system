
#ifndef KEY_PAD_H_
#define KEY_PAD_H_

#include "KEYPAD_CFG.h"
#define F_CPU 16000000
#include <util/delay.h>
#include "../../LIB/STD.h"
#include "../../MCAL/DIO/DIO.h"

#define Col_INIT  7
#define Col_FINAL 3

#define Row_INIT  5
#define Row_FINAL 2


void KEYPAD_INIT(void);
uint8 keypadGetValue(void);


#endif /* KEY_PAD_H_ */