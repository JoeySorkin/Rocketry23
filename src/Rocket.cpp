#include "Rocket.h"
#include "arduino.h"
#include "Altimeter.h"
#include "Decoupler.h"
#include "Logger.h"
Rocket *Rocket::INSTANCE = nullptr;

void Rocket::init()
{
    state = INITIALIZING;
    Serial.println("Initializing....");

    // Startup Sound --> end of init
    beep(300, 300);
    delay(150);
    beep(300, 300);
    delay(150);
    beep(300, 300);
    delay(150);

    sAltimeter->init();
    beep(300, 100);
    delay(300);
    sDecoupler->init();
    beep(550, 100);
    delay(300);
    sLogger->init();
    beep(800, 100);
    delay(300);

    beep(300, 300);
    delay(150);
    beep(550, 300);
    delay(150);
    beep(800, 300);
    delay(150);
    //sDecoupler->lock();
    //while(true){
      //  delay(500);
    //}

    sLogger->log("rocket", "message", "startup complete");

    // // delay(500);
    // // sDecoupler->unlock();
    // // delay(750);
    // sDecoupler->lock();

    state = PRELAUNCH;
}
void Rocket::prelaunch()
{

    Serial.println("PRELAUNCH \t Height: " + String(sAltimeter->getHeight()) + "\t Velocity: " + String(sAltimeter->getVelocity()));
    sLogger->log("prelaunch", "data", "," + String(sAltimeter->getHeight()) + "," + String(sAltimeter->getVelocity()));
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
    sLogger->log("flight", "data", "," + String(sAltimeter->getHeight()) + "," + String(sAltimeter->getVelocity()));
    // #1 time decouple
    if ((millis() - launch_start_time_ms) > TIME_TO_DECOUPLE)
    {
        Serial.println("TIME DECOUPLE");
        sLogger->log("flight", "message", "TIME DECOUPLED");
        sDecoupler->unlock();
        state = RocketState::DECOUPLED;
    }
    // #2 altitude decouple
    else if (sAltimeter->getHeight() >= ALT_TO_DECOUPLE)
    {
        Serial.println("ALTITUDE DECOUPLE");
        sLogger->log("flight", "message", "ALTITIUDE DECOUPLE");
        sDecoupler->unlock();
        state = RocketState::DECOUPLED;
    }
    // #3 velocity decouple
    else if (sAltimeter->getVelocity() <= VEL_TO_DECOUPLE)
    {
        Serial.println("VELOCITY DECOUPLE");
        sLogger->log("flight", "message", "VELOCITY DECOUPLED");
        sDecoupler->unlock();
        state = RocketState::DECOUPLED;
    }
}

void Rocket::decoupled()
{

    Serial.println("POST-DECOUPLED \t Height: " + String(sAltimeter->getHeight()) + "\t Velocity: " + String(sAltimeter->getVelocity()));
    sLogger->log("decoupled", "data", "," + String(sAltimeter->getHeight()) + "," + String(sAltimeter->getVelocity()));
}
void Rocket::run()
{
    sAltimeter->update();
    sLogger->update();
    switch (state)
    {
    case (PRELAUNCH):
        prelaunch();
        break;
    case (LAUNCHED):
        flight();
        break;
    case (DECOUPLED):
        decoupled();
        break;
    default:
        break;
    }
}
void Rocket::beep(int frq, int length)
{
    tone(BuzzerPort, frq, length);
}
