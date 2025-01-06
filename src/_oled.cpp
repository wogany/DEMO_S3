#include "_oled.h"

const uint8_t SCL_PIN = 9;
const uint8_t SDA_PIN = 10;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);

/*
    @brief OLED≥ı ºªØ
*/
void OledInit(void)
{
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
}

/*
    @brief OLED≤‚ ‘
*/
void OledTest(void)
{
    u8g2.drawBox(0, 0, 128, 64);
    u8g2.sendBuffer();
    delay(1000);
    u8g2.clearBuffer();
    u8g2.drawFrame(31, 15, 64, 32);
    u8g2.drawStr(33, 37, "Hello World!");
    u8g2.sendBuffer();
    delay(1000);
}