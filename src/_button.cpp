#include "_button.h"

const uint8_t ROW_PINS[2] = {36, 37}; // 按键矩阵行引脚，输出
const uint8_t COL_PINS[2] = {38, 39}; // 按键矩阵列引脚，上拉输入

_Bool ButtonStates[2][2] = {{false, false}, {false, false}};

hw_timer_t *timer_button = NULL;

/* 更新按键矩阵状态，定时器中断函数 */
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
}

/* 初始化按键矩阵 */
void ButtonInit(void)
{

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
    按键矩阵测试，单个按键是否按下

    0 -> [0][0]
    1 -> [0][1]
    2 -> [1][0]
    3 -> [1][1]
    4 -> ALL FALSE
 */
int ButtonOnceTest(void)
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