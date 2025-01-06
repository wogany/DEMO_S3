#include "_rgb.h"

const uint8_t DATA_PIN = 7;

Adafruit_NeoPixel RGB(4, DATA_PIN, NEO_GRB + NEO_KHZ800);

/*
    @brief RGBģ���ʼ��
*/
void RgbInit(void)
{
    RGB.begin();
    RGB.setBrightness(50);
    RGB.show();
    RGB.clear();
}

/*
    @brief RGBģ����ԣ���������������
*/
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

/*
    @brief ��RGBֵ���ΪR��G��B��ֵ
    @param[in] RgbColorValue �������RGBֵ
    @param[out] R 8bit Rֵ
    @param[out] G 8bit Gֵ
    @param[out] B 8bit Bֵ
*/
void RgbExtract(uint32_t RgbColorValue, uint8_t &R, uint8_t &G, uint8_t &B)
{
    R = (RgbColorValue >> 16) & 0xFF;
    G = (RgbColorValue >> 8) & 0xFF;
    B = RgbColorValue & 0xFF;
}

/*
    @brief ��R��G��B��ֵ�ϳ�RGBֵ
    @param[in] R 8bit Rֵ
    @param[in] G 8bit Gֵ
    @param[in] B 8bit Bֵ
    @param[out] RgbColorValue �ϳɵ�RGBֵ
*/
void RgbCombine(uint8_t R, uint8_t G, uint8_t B, uint32_t &RgbColorValue)
{
    RgbColorValue = (R << 16) + (G << 8) + B;
}

/*
    @brief ����ɫ�仯
    @param[in] Numbers RGB������
    @param[in] ColorA ���俪ʼ��ɫ
    @param[in] ColorB ���������ɫ
    @param[in] Step ���䲽����Խ��Խƽ��
*/
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