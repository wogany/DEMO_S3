#include <Arduino.h>
#include "_led.h"
#include "_rgb.h"
#include "_button.h"
#include "_joystick.h"
#include "_oled.h"
// #include "_mpu6050.h"

uint8_t MainFlag = 1;

void setup()
{
    Serial.begin(115200);

    // LedInit();
    // RgbInit();
    ButtonInit();
    JoyInit();
    OledInit();
    // MpuInit();
}

void loop()
{
    MainMenu(MainFlag, ButtonStates);
    delay(10);
    switch (MainFlag)
    {
    case 1:
        _Bool IsGameGoOn;
        do
        {
            IsGameGoOn = GluttonousSnake(ButtonStates, JoyStates, JoyUpdate);
        } while(IsGameGoOn);
        delay(100);
        break;
    default:
        ;
        break;
    }
}