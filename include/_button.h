#ifndef __BUTTON_H
#define __BUTTON_H

#include <Arduino.h>

extern _Bool ButtonStates[2][2];

void ButtonInit(void);
int ButtonOnceTest(void);

#endif // __BUTTON_H