#include <Arduino.h>
#include "_led.h"

void setup()
{
    Serial.begin(115200);

    LedInit();
}

void loop()
{
    LedFlick();
}