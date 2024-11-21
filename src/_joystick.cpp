#include "_joystick.h"

const uint8_t XPIN = 4;
const uint8_t YPIN = 5;
const uint8_t SWPIN = 6; // ����

uint32_t XValue, YValue;
_Bool SWState = false;

/* ҡ�˳�ʼ�� */
void JoyInit(void)
{
    pinMode(XPIN, INPUT);
    pinMode(YPIN, INPUT);
    pinMode(SWPIN, INPUT_PULLUP);
}

/* ��ȡҡ����ֵ */
void GetJoyValue(void)
{
    XValue = analogRead(XPIN);
    YValue = analogRead(YPIN);
    SWState = !digitalRead(SWPIN);
}
