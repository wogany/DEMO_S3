#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include <Arduino.h>

extern uint32_t JoyXValue, JoyYValue;
extern _Bool SWState;

void JoyInit(void);
void GetJoyValue(void);

#endif // __JOYSTICK_H