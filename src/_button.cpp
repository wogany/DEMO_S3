#include "_button.h"

const uint8_t ROW_PINS[2] = {36, 37}; // 按键矩阵行引脚，输出
const uint8_t COL_PINS[2] = {38, 39}; // 按键矩阵列引脚，上拉输入
const uint8_t KEY_PIN = 16;           // 独立按键引脚， 上拉输入

_Bool ButtonStates[2][2] = {{false, false}, {false, false}};
_Bool KeyState = false;

hw_timer_t *timer_button = NULL;

/* 更新按键模块状态，定时器中断函数 */
void ButtonInterrupt(void)
{
    for (uint8_t r = 0; r < 2; r++)
    {
        digitalWrite(ROW_PINS[r], LOW); // 激活行

        for (uint8_t c = 0; c < 2; c++)
        {
            _Bool ButtonState = !digitalRead(COL_PINS[c]);
            if (ButtonState != ButtonStates[r][c]) // 检测是否按下
            {
                ButtonStates[r][c] = ButtonState;
            }
        }

        digitalWrite(ROW_PINS[r], HIGH); // 关闭行
    }

    KeyState = !digitalRead(KEY_PIN);
}

/* 初始化按键模块 */
void ButtonInit(void)
{
    pinMode(KEY_PIN, INPUT_PULLUP);
    for (uint8_t i = 0; i < 2; i++)
    {
        pinMode(ROW_PINS[i], OUTPUT);
        pinMode(COL_PINS[i], INPUT_PULLUP);
    }

    timer_button = timerBegin(0, 80, true);                    // 初始化定时器
    timerAttachInterrupt(timer_button, ButtonInterrupt, true); // 配置中断函数
    timerAlarmWrite(timer_button, 100, true);                  // 设置定时模式
    timerAlarmEnable(timer_button);                            // 启动定时器
}

/* 
    按键矩阵测试

    0 -> [0][0]
    1 -> [0][1]
    2 -> [1][0]
    3 -> [1][1]
    4 -> 未按下
 */
int ButtonTest(void)
{
    for (uint8_t r = 0; r < 2; r++)
    {
        for (uint8_t c = 0; c < 2; c++)
        {
            if (ButtonStates[r][c] == true)
            {
                return r * 2 + c;
            }
        }
    }
    return 4;
}

/*
    独立按键测试
    
    0 -> 未按下
    1 -> 已按下
 */
int KeyTest(void)
{
    return KeyState;
}