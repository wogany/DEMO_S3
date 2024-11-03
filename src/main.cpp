#include <Arduino.h>
#include "_led.h"
#include "_button.h"
#include "_joystick.h"

void setup()
{
    Serial.begin(115200);

    LedInit();
    ButtonInit();
    JoyInit();
}

void loop()
{
    GetJoyValue();
    Serial.printf("X = %d, Y = %d, SW = %d\n", XValue, YValue, SWState);
    delay(100);
}