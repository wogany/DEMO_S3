#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include <Arduino.h>

extern uint32_t JoyValue[2];
extern _Bool JoyStates[4];
extern _Bool SWState;

void JoyInit(void);
void GetJoyValue(void);
void JoyUpdate(void);

#endif // __JOYSTICK_H