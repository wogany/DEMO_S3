#ifndef __RGB_H
#define __RGB_H

#include <Adafruit_NeoPixel.h>

void RgbInit(void);
void RgbTest(void);
void RgbGradient(uint8_t Numbers, uint32_t ColorA, uint32_t ColorB, uint8_t Step);

/* ��ɫ�궨�� */
#define COLOR_RED 0xFF0000   // ��ɫ
#define COLOR_GREEN 0x00FF00 // ��ɫ
#define COLOR_BLUE 0x0000FF  // ��ɫ
/* ɫ�Ų�ѯ��https://www.rapidtables.org/zh-CN/web/color/RGB_Color.html */


#endif // __RGB_H