#include "_joystick.h"

const uint8_t XPIN = 5;
const uint8_t YPIN = 4;
const uint8_t SWPIN = 6; // 按键下拉电阻

uint32_t JoyValue[2];
int8_t JoyStick[2] = {0, 0};
_Bool SWState = false, JoyStates[4] = {false, false, false, false};

/*
    @brief 摇杆初始化
*/
void JoyInit(void)
{
    pinMode(XPIN, INPUT);
    pinMode(YPIN, INPUT);
    pinMode(SWPIN, INPUT_PULLDOWN);
}

/*
    @brief 获取摇杆数值
*/
void GetJoyValue(void)
{
    JoyValue[0] = analogRead(XPIN);
    JoyValue[1] = analogRead(YPIN);
    SWState = digitalRead(SWPIN);
}

/*
    @brief 更新摇杆模块状态
*/
void JoyUpdate(void)
{
    JoyStick[0] = (analogRead(XPIN) - 2000) / 1500;
    JoyStick[1] = (analogRead(YPIN) - 2000) / 1500;

    if (!JoyStick[0] + !JoyStick[1] == 0)
    {
        JoyStates[0] = false;
        JoyStates[1] = false;
        JoyStates[2] = false;
        JoyStates[3] = false;
    }
    else
    {
        JoyStates[0] = (JoyStick[1] + 1) / 2;
        JoyStates[1] = (JoyStick[0] + 1) / 2;
        JoyStates[2] = (JoyStick[1] - 1) / 2;
        JoyStates[3] = (JoyStick[0] - 1) / 2;
    }
}

