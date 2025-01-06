#include "_mpu6050.h"

const uint8_t SCL_PIN = 9;
const uint8_t SDA_PIN = 10;

Adafruit_MPU6050 mpu;

/* MPU6050��ʼ�� */
void MpuInit(void)
{
    Wire.begin(SDA_PIN, SCL_PIN, 100000);
    if (!mpu.begin(0x68, &Wire))
    {
        Serial.println("�޷���ʼ�� MPU6050 ��������");
        while (1)
        delay(5);    ; // �����ʼ��ʧ�ܣ���ͣ���ڴ˴�
    }
    Serial.println("MPU6050 ��ʼ���ɹ���");
}