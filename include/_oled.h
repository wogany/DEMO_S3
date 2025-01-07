#ifndef __OLED_H
#define __OLED_H

#include <U8g2lib.h>
#include <u8g2_wqy.h>

void OledInit(void);
void OledTest(void);
void GluttonousSnake(_Bool *UP, _Bool *Down, _Bool *Left, _Bool *Right);

#endif // __OLED_H