#include <Arduino.h>
#include "_led.h"
#include "_rgb.h"
#include "_button.h"
#include "_joystick.h"
#include "_oled.h"

void setup()
{
    Serial.begin(115200);

    LedInit();
    RgbInit();
    ButtonInit();
    JoyInit();
    OledInit();
}

void loop()
{
    OledTest();
}