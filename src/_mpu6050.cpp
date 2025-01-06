#include "_mpu6050.h"

const uint8_t SCL_PIN = 9;
const uint8_t SDA_PIN = 10;

Adafruit_MPU6050 mpu;

/* MPU6050初始化 */
void MpuInit(void)
{
    Wire.begin(SDA_PIN, SCL_PIN, 100000);
    if (!mpu.begin(0x68, &Wire))
    {
        Serial.println("无法初始化 MPU6050 传感器！");
        while (1)
        delay(5);    ; // 如果初始化失败，则停留在此处
    }
    Serial.println("MPU6050 初始化成功！");
}