#include "_oled.h"

const uint8_t SCL_PIN = 9;
const uint8_t SDA_PIN = 10;

const uint8_t MAINMENU_MAX = 3;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);

/*
    @brief OLED初始化
*/
void OledInit(void)
{
    u8g2.begin();
    u8g2.enableUTF8Print();
}

/*
    @brief OLED测试
*/
void OledTest(void)
{
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    u8g2.drawBox(0, 0, 128, 64);
    u8g2.sendBuffer();
    delay(1000);
    u8g2.clearBuffer();
    u8g2.drawFrame(31, 15, 64, 32);
    u8g2.drawStr(33, 37, "Hello World!");
    u8g2.sendBuffer();
    delay(1000);
}

/*
    @brief 绘制贪吃蛇游戏界面
    @param Grade[] 得分
    @param Level[] 等级
    @param SnakeCrood[100][2] 贪吃蛇蛇身坐标值
    @param SnakeLen 贪吃蛇长度
    @param FoodCrood[2] 食物坐标
*/
void SnakeGameInterface(uint8_t GradeVal, uint8_t LevelVal, uint8_t SnakeCrood[100][2], uint8_t SnakeLen, uint8_t FoodCrood[2])
{
    char Grade[4], Level[4];
    itoa(GradeVal, Grade, 10);
    itoa(LevelVal, Level, 10);

    u8g2.drawStr(95, 15, "Grade");
    u8g2.drawStr(102, 30, Grade);
    u8g2.drawStr(95, 44, "Level");
    u8g2.drawStr(102, 59, Level);
    u8g2.drawFrame(1, 1, 92, 62);

    for (uint8_t i = 0; i < SnakeLen; i++)
    {
        u8g2.drawBox(SnakeCrood[i][0], SnakeCrood[i][1], 2, 2);
    }

    u8g2.drawBox(FoodCrood[0], FoodCrood[1], 2, 2);
}

/*
    @brief 贪吃蛇游戏
    @param ButtonStates[2][2] 按键状态
    @param JoyStates[4] 摇杆状态
    @param JoyUpdate() 摇杆状态更新函数
    @retval true 游戏继续
    @retval false 游戏结束
*/
_Bool GluttonousSnake(_Bool ButtonStates[2][2], _Bool JoyStates[4], void (*JoyUpdate)(void))
{
    uint8_t Grade = 0, Level = 1;
    uint8_t SnakeCoord[100][2] = {{2}, {2}}; // 蛇身坐标集
    uint8_t SnakeHead[2] = {2, 2};           // 蛇头坐标
    uint8_t SnakeLen = 1;                    // 贪吃蛇长度
    uint8_t FoodCoord[2] = {4, 2};           // 食物坐标
    typedef enum
    {
        GoUp = 0,
        GoLeft,
        GoRight,
        GoDown
    } Direction;
    Direction SnakeMoveState = GoRight; // 贪吃蛇移动方向
    _Bool IsGameOver = false;

    _Bool &KeyUp = ButtonStates[0][0], &KeyLeft = ButtonStates[0][1], &KeyDown = ButtonStates[1][0], &KeyRight = ButtonStates[1][1];
    _Bool &JoyUp = JoyStates[0], &JoyLeft = JoyStates[1], &JoyDown = JoyStates[2], &JoyRight = JoyStates[3];

    /* 初始化游戏界面 */
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    SnakeGameInterface(Grade, Level, SnakeCoord, SnakeLen, FoodCoord);

    /* 游戏正常运行 */
    do
    {
        /* 更新摇杆状态 */
        JoyUpdate();

        /* 更新贪吃蛇运动方向 */
        if ((KeyUp || JoyUp + KeyLeft || JoyLeft + KeyDown || JoyDown + KeyRight || JoyRight) > 1)
        {
            ;
        }
        else
        {
            if ((KeyUp || JoyUp) && SnakeMoveState != GoDown)
            {
                SnakeMoveState = GoUp;
            }
            else if ((KeyDown || JoyDown) && SnakeMoveState != GoUp)
            {
                SnakeMoveState = GoDown;
            }
            else if ((KeyLeft || JoyLeft) && SnakeMoveState != GoRight)
            {
                SnakeMoveState = GoLeft;
            }
            else if ((KeyRight || JoyRight) && SnakeMoveState != GoLeft)
            {
                SnakeMoveState = GoRight;
            }
        }

        /* 更新蛇头位置 */
        switch (SnakeMoveState)
        {
        case GoUp:
            SnakeHead[1] -= 2;
            break;
        case GoLeft:
            SnakeHead[0] -= 2;
            break;
        case GoRight:
            SnakeHead[0] += 2;
            break;
        case GoDown:
            SnakeHead[1] += 2;
        }

        /* 判断是否死亡 */
        if (SnakeHead[0] < 2 || SnakeHead[0] > 90 || SnakeHead[1] < 2 || SnakeHead[1] > 60)
        {
            IsGameOver = true;
            continue;
        }
        else
        {
            for (uint8_t i = 0; i < SnakeLen; i++)
            {
                if (SnakeHead[0] == SnakeCoord[i][0])
                {
                    if (SnakeHead[1] == SnakeCoord[i][1])
                    {
                        IsGameOver = true;
                        break;
                    }
                }
            }
            if (IsGameOver)
            {
                continue;
            }
        }

        /* 更新食物坐标 */
        if (FoodCoord[0] == SnakeHead[0] && FoodCoord[1] == SnakeHead[1])
        {
            Grade++;
            Level = Grade / 10 + 1;
            SnakeLen++;

            uint8_t XFlag;
            _Bool IsSameCoords;
            uint8_t FoodCoorded[2] = {FoodCoord[0], FoodCoord[1]};

            /* 生成食物X坐标 */
            do
            {
                do
                {
                    FoodCoord[0] = rand() % 90 + 1;
                } while (FoodCoord[0] % 2);

                XFlag = 0;
                for (uint8_t i = 0; i < SnakeLen; i++)
                {
                    if (SnakeCoord[i][0] == FoodCoord[0])
                    {
                        XFlag++;
                    }
                }
            } while (XFlag == 30);

            /* 生成食物Y坐标 */
            do
            {
                do
                {
                    FoodCoord[1] = rand() % 60 + 1;
                } while (FoodCoord[1] % 2);

                IsSameCoords = false;
                for (uint8_t i = 0; i < SnakeLen; i++)
                {
                    if (SnakeCoord[i][0] == FoodCoord[0])
                    {
                        if (SnakeCoord[i][1] == FoodCoord[1])
                        {
                            IsSameCoords = true;
                        }
                    }
                }
                if (FoodCoord[0] == FoodCoorded[0] && FoodCoord[1] == FoodCoorded[1])
                {
                    IsSameCoords = true;
                }
            } while (IsSameCoords);
        }

        /* 更新蛇身位置 */
        for (uint8_t i = 0; i < 2; i++)
        {
            for (uint8_t j = SnakeLen; j > 1; j--)
            {
                SnakeCoord[j - 1][i] = SnakeCoord[j - 2][i];
            }
            SnakeCoord[0][i] = SnakeHead[i];
        }

        u8g2.clearBuffer();
        SnakeGameInterface(Grade, Level, SnakeCoord, SnakeLen, FoodCoord);
        u8g2.sendBuffer();
        delay(120 * pow(0.86, Level - 1));
    } while (!IsGameOver);

    /* 游戏结束界面 */
    while (IsGameOver)
    {
        char GradeStr[4], LevelStr[4];
        itoa(Grade, GradeStr, 10);
        itoa(Level, LevelStr, 10);

        u8g2.clearBuffer();
        u8g2.drawStr(42, 15, "Grade");
        u8g2.drawStr(82, 15, GradeStr);
        u8g2.drawStr(42, 31, "Level");
        u8g2.drawStr(82, 31, LevelStr);
        u8g2.drawStr(12, 55, "GoBack <- -> GoOn");
        u8g2.sendBuffer();

        delay(100);
        do
        {
            delay(10);
            if (KeyLeft)
            {
                return false;
            }
            else if (KeyRight)
            {
                return true;
            }
        } while (1);
    }
}

/*
    @brief 主菜单（一级）
    @param MainFlag 主菜单标志位，作为菜单选项指示
    @param ButtonStates[2][2] 按键状态
    @return 所处菜单选项
*/
int MainMenu(uint8_t &MainFlag, _Bool ButtonStates[2][2])
{
    _Bool &Up = ButtonStates[0][0], &Left = ButtonStates[0][1], &Down = ButtonStates[1][0], &Right = ButtonStates[1][1];
    u8g2.setFont(u8g2_font_wqy16_t_gb2312);

    /* 主菜单正常运行 */
    do
    {
        /* 判断标志位是否移动 */
        if (Up + Left + Down + Right > 1)
        {
            ;
        }
        else
        {
            if (Up && MainFlag > 1)
            {
                MainFlag--;
            }
            else if (Down && MainFlag < MAINMENU_MAX)
            {
                MainFlag++;
            }
            else if (Right)
            {
                return MainFlag;
            }
        }

        u8g2.clearBuffer();

        /* 绘制基本界面 */
        u8g2.drawStr(40, 17, "GameTime");
        u8g2.drawStr(40, 37, "LED");
        u8g2.drawStr(40, 57, "RGB");
        u8g2.drawFrame(20, 5, 12, 12);
        u8g2.drawFrame(20, 25, 12, 12);
        u8g2.drawFrame(20, 45, 12, 12);

        /* 绘制菜单指针指示 */
        u8g2.drawBox(20, 20 * MainFlag - 15, 12, 12);

        u8g2.sendBuffer();
        delay(100);
    } while (1);

    return 0;
}
