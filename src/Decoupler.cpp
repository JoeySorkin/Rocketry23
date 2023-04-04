#include "Decoupler.h"
#include "Rocket.h"
#include "Arduino.h"
Decoupler *Decoupler::INSTANCE = nullptr;

void Decoupler::init()
{
    // servo setup
    servo.attach(SERVO_PIN);
}
void Decoupler::lock()
{
    servo.write(180);
    delay(15);
    for (int i = 0; i < 1; i++)
    {
        sRocket->beep(600, 200);
        delay(500);
    }
}
void Decoupler::unlock()
{
    servo.write(0);
    delay(15);
    for (int i = 0; i < 1; i++)
    {
        sRocket->beep(500, 200);
        delay(500);
    }
}