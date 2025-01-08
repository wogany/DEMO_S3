#ifndef __OLED_H
#define __OLED_H

#include <U8g2lib.h>
#include <u8g2_wqy.h>

void OledInit(void);
void OledTest(void);
void GluttonousSnake(_Bool ButtonState[2][2], _Bool JoyStates[4],  void(*JoyUpdate)(void));

#endif // __OLED_H