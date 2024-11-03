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
    Serial.print(ButtonTest());
    Serial.println(KeyTest());
    delay(100);
}