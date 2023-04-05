#include "Rocket.h"
#include "arduino.h"
#include "Altimeter.h"
#include "Decoupler.h"
Rocket *Rocket::INSTANCE = nullptr;

void Rocket::init()
{
    state = INITIALIZING;
    Serial.println("Initializing....");

    // Startup Sound --> end of init
    beep(300, 300);
    delay(150);
    beep(550, 300);
    delay(150);
    beep(800, 300);
    delay(150);

    sAltimeter->init();
    sDecoupler->init();

    // delay(500);
    // sDecoupler->unlock();
    // delay(750);
    sDecoupler->lock();

    state = PRELAUNCH;
}
void Rocket::prelaunch()
{

    Serial.println("PRELAUNCH \t Height: " + String(sAltimeter->getHeight()) + "\t Velocity: " + String(sAltimeter->getVelocity()));
    if (sAltimeter->getVelocity() > LAUNCH_VELOCITY_THRESHOLD)
    {
        launch_start_time_ms = millis();
        Serial.println("=====LAUNCHED=====");
        state = RocketState::LAUNCHED;
    }
}

void Rocket::flight()
{
    Serial.println("FLIGHT \t Height: " + String(sAltimeter->getHeight()) + "\t Velocity: " + String(sAltimeter->getVelocity()));

    // #1 time decouple
    if ((millis() - launch_start_time_ms) > TIME_TO_DECOUPLE)
    {
        Serial.println("TIME DECOUPLE");
        sDecoupler->unlock();
        state = RocketState::DECOUPLED;
    }
    // #2 altitude decouple
    else if (sAltimeter->getHeight() >= ALT_TO_DECOUPLE)
    {
        Serial.println("ALTITUDE DECOUPLE");
        sDecoupler->unlock();
        state = RocketState::DECOUPLED;
    }
    // #3 velocity decouple
    else if (sAltimeter->getVelocity() <= VEL_TO_DECOUPLE)
    {
        Serial.println("VELOCITY DECOUPLE");
        sDecoupler->unlock();
        state = RocketState::DECOUPLED;
    }
}

void Rocket::run()
{
    sAltimeter->update();
    switch (state)
    {
    case (PRELAUNCH):
        prelaunch();
        break;
    case (LAUNCHED):
        flight();
        break;
    case (DECOUPLED):
        break;
    default:
        break;
    }
}
void Rocket::beep(int frq, int length)
{

    tone(BuzzerPort, frq, length);
}
