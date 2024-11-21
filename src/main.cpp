#include <Arduino.h>
// #include "_led.h"
// #include "_rgb.h"
// #include "_button.h"
// #include "_joystick.h"
// #include "_oled.h"
// #include "_mpu6050.h"

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    // LedInit();
    // RgbInit();
    // ButtonInit();
    // JoyInit();
    // OledInit();
    // MpuInit();
}

void loop()
{
    // LedTest();
    // RgbTest();
    // OledTest();
    // GetJoyValue();
    // Serial.printf("Button %d\n", ButtonTest());
    // Serial.printf("X = %d, Y = %d, B = %d\n", XValue, YValue, SWState);

    Serial.println("Serial.println");
    log_e("log_e");
    delay(1000);
}