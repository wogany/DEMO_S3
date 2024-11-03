#include "_button.h"

const uint8_t ROW_PINS[2] = {36, 37}; // �������������ţ����
const uint8_t COL_PINS[2] = {38, 39}; // �������������ţ���������

_Bool ButtonStates[2][2] = {{false, false}, {false, false}};

hw_timer_t *timer_button = NULL;

/* ���°�������״̬����ʱ���жϺ��� */
void ButtonInterrupt(void)
{
    for (uint8_t r = 0; r < 2; r++)
    {
        digitalWrite(ROW_PINS[r], LOW); // ������

        for (uint8_t c = 0; c < 2; c++)
        {
            _Bool ButtonState = !digitalRead(COL_PINS[c]);
            if (ButtonState != ButtonStates[r][c]) // ����Ƿ���
            {
                ButtonStates[r][c] = ButtonState;
            }
        }

        digitalWrite(ROW_PINS[r], HIGH); // �ر���
    }
}

/* ��ʼ���������� */
void ButtonInit(void)
{

    for (uint8_t i = 0; i < 2; i++)
    {
        pinMode(ROW_PINS[i], OUTPUT);
        pinMode(COL_PINS[i], INPUT_PULLUP);
    }

    timer_button = timerBegin(0, 80, true);                    // ��ʼ����ʱ��
    timerAttachInterrupt(timer_button, ButtonInterrupt, true); // �����жϺ���
    timerAlarmWrite(timer_button, 100, true);                  // ���ö�ʱģʽ
    timerAlarmEnable(timer_button);                            // ������ʱ��
}

/*
    ����������ԣ����������Ƿ���

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