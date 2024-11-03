#include <Arduino.h>
#include "_led.h"
#include "_button.h"

void setup()
{
    Serial.begin(115200);

    LedInit();
    ButtonInit();
}

void loop()
{
    Serial.println(ButtonOnceTest());
    delay(100);
}