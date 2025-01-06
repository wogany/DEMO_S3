#include "_led.h"

const uint8_t LED_CPIN = 8;                   // PNP�����ܻ������͵�ƽ����
const uint8_t LED_OPIN[4] = {15, 16, 17, 18}; // LED�������͵�ƽ����

/*
    @brief LED���ų�ʼ��
*/
void LedInit(void)
{
    pinMode(LED_CPIN, OUTPUT);
    digitalWrite(LED_CPIN, HIGH);
    for (uint8_t i = 0; i < 4; i++)
    {
        pinMode(LED_OPIN[i], OUTPUT);
        digitalWrite(LED_OPIN[i], HIGH);
    }
}

/*
    @brief ��������״̬����������
*/
void LedTest(void)
{
    digitalWrite(LED_CPIN, LOW);
    for (uint8_t i = 0; i < 4; i++)
    {
        digitalWrite(LED_OPIN[i], LOW);
        delay(500);
    }
    digitalWrite(LED_CPIN, HIGH);
    delay(1000);
}

/*
    @brief ��˸��
*/
void LedFlick(void)
{
    digitalWrite(LED_CPIN, LOW);
    for (uint8_t i = 0; i < 4; i++)
    {
        digitalWrite(LED_OPIN[i], !digitalRead(LED_OPIN[i]));
        delay(50);
    }
    delay(50);
}