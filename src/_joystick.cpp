#include "_joystick.h"

const uint8_t XPIN = 5;
const uint8_t YPIN = 4;
const uint8_t SWPIN = 6; // ������������

uint32_t JoyXValue, JoyYValue;
_Bool SWState = false;

/*
    @brief ҡ�˳�ʼ��
*/
void JoyInit(void)
{
    pinMode(XPIN, INPUT);
    pinMode(YPIN, INPUT);
    pinMode(SWPIN, INPUT_PULLDOWN);
}

/*
    @brief ��ȡҡ����ֵ
*/
void GetJoyValue(void)
{
    JoyXValue = analogRead(XPIN);
    JoyYValue = analogRead(YPIN);
    SWState = digitalRead(SWPIN);
}
