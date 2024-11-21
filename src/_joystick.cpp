#include "_joystick.h"

const uint8_t XPIN = 4;
const uint8_t YPIN = 5;
const uint8_t SWPIN = 6; // 上拉

uint32_t XValue, YValue;
_Bool SWState = false;

/* 摇杆初始化 */
void JoyInit(void)
{
    pinMode(XPIN, INPUT);
    pinMode(YPIN, INPUT);
    pinMode(SWPIN, INPUT_PULLUP);
}

/* 获取摇杆数值 */
void GetJoyValue(void)
{
    XValue = analogRead(XPIN);
    YValue = analogRead(YPIN);
    SWState = !digitalRead(SWPIN);
}
