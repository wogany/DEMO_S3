#ifndef __BUTTON_H
#define __BUTTON_H

#include <Arduino.h>

extern _Bool ButtonStates[2][2];
extern _Bool KeyState;

void ButtonInit(void);
int ButtonTest(void);
int KeyTest(void);

#endif // __BUTTON_H