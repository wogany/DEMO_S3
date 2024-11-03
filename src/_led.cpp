#include "_led.h"

const uint8_t LED_CPIN = 8;                   // PNP�����ܻ������͵�ƽ����
const uint8_t LED_OPIN[4] = {11, 12, 13, 14}; // LED�������͵�ƽ����

/* LED���ų�ʼ�� */
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

/* ��������״̬���������� */
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

/* ������ */
void LedBreath(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        digitalWrite(LED_OPIN[i], LOW);
    }
    for (uint8_t i = 0; i < 256; i++)
    {
        analogWrite(LED_CPIN, i);
        delay(10);
    }
}

/* ��˸�� */
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