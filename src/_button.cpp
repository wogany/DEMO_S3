#include "_button.h"

const uint8_t ROW_PINS[2] = {12, 11}; // 按键矩阵行引脚，输出
const uint8_t COL_PINS[2] = {14, 13}; // 按键矩阵列引脚，上拉输入

_Bool ButtonStates[2][2] = {{false, false}, {false, false}}; // 按键矩阵状态

hw_timer_t *timer_button = NULL;

/*
    @brief 更新按键模块状态（定时器中断函数）
*/
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

/*
    @brief 按键模块初始化
*/
void ButtonInit(void)
{
    for (uint8_t i = 0; i < 2; i++)
    {
        pinMode(ROW_PINS[i], OUTPUT);
        pinMode(COL_PINS[i], INPUT_PULLUP);
    }

    timer_button = timerBegin(0, 80, true);                    // 初始化定时器
    timerAttachInterrupt(timer_button, ButtonInterrupt, true); // 配置中断函数
    timerAlarmWrite(timer_button, 120, true);                  // 设置定时模式
    timerAlarmEnable(timer_button);                            // 启动定时器
}

/*
    @brief 按键矩阵测试
    @return 所按按键
    @retval 0 按键[0][0]
    @retval 1 按键[0][1]
    @retval 2 按键[1][0]
    @retval 3 按键[1][1]
    @retval 4 未按下按键
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