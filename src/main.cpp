#include <Arduino.h>
#include "_led.h"
#include "_rgb.h"
#include "_button.h"
#include "_joystick.h"

void setup()
{
    Serial.begin(115200);

    LedInit();
    RgbInit();
    ButtonInit();
    JoyInit();
}

void loop()
{
    
}