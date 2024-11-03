#include "_rgb.h"

const uint8_t DATA_PIN = 7;

Adafruit_NeoPixel RGB(4, DATA_PIN, NEO_GRB + NEO_KHZ800);

/* RGB模块初始化 */
void RgbInit(void)
{
    RGB.begin();
    RGB.setBrightness(50);
}

/* RGB模块测试，红绿蓝 */
void RgbTest(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        RGB.setPixelColor(i, COLOR_RED);
    }
    RGB.show();
    delay(1000);

    for (uint8_t i = 0; i < 4; i++)
    {
        RGB.setPixelColor(i, COLOR_GREEN);
    }
    RGB.show();
    delay(1000);

    for (uint8_t i = 0; i < 4; i++)
    {
        RGB.setPixelColor(i, COLOR_BLUE);
    }
    RGB.show();
    delay(1000);
}

/* 拆解RGB值 */
void RgbExtract(uint32_t RgbColorValue, uint8_t &R, uint8_t &G, uint8_t &B)
{
    R = (RgbColorValue >> 16) & 0xFF;
    G = (RgbColorValue >> 8) & 0xFF;
    B = RgbColorValue & 0xFF;
}

/* 合并RGB值 */
void RgbCombine(uint8_t R, uint8_t G, uint8_t B, uint32_t &RgbColorValue)
{
    RgbColorValue = (R << 16) + (G << 8) + B;
}

/* 渐变色 */
void RgbGradient(uint8_t Numbers, uint32_t ColorA, uint32_t ColorB, uint8_t Step)
{
    uint8_t Gradient_RGB[3];
    uint8_t ColorA_RGB[3], ColorB_RGB[3];

    RgbExtract(ColorA, ColorA_RGB[0], ColorA_RGB[1], ColorA_RGB[2]);
    RgbExtract(ColorB, ColorB_RGB[0], ColorB_RGB[1], ColorB_RGB[2]);

    for (uint8_t i = 0; i <= Step; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            Gradient_RGB[j] = ColorA_RGB[j] + (ColorB_RGB[j] - ColorA_RGB[j]) * i / Step;
        }

        for (uint8_t j = 0; j < Numbers; j++)
        {
            RGB.setPixelColor(j, Gradient_RGB[0], Gradient_RGB[1], Gradient_RGB[2]);
        }
        RGB.show();
        delay(10);
    }
}