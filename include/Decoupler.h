#pragma once

#define sDecoupler Decoupler::getInstance()
#include <Servo.h>
#define SERVO_PIN 10
class Decoupler
{
private:
    static Decoupler *INSTANCE;
    Servo servo;

public:
    void init();
    void lock();
    void unlock();

    static Decoupler *getInstance()
    {
        if (!INSTANCE)
        {
            INSTANCE = new Decoupler();
        }
        return INSTANCE;
    }
};
