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
    servo.write(127);
}
void Decoupler::unlock()
{
    servo.write(68);
}