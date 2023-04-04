
#pragma once
#define sRocket Rocket::getInstance()

#define BuzzerPort 1
#define LAUNCH_VELOCITY_THRESHOLD 4 // m/s
#define TIME_TO_DECOUPLE 4000       // ms
#define ALT_TO_DECOUPLE 2.5         // m
#define VEL_TO_DECOUPLE -4          // m/s

class Rocket
{
public:
    enum RocketState
    {
        INITIALIZING,
        PRELAUNCH,
        LAUNCHED,
        DECOUPLED
    };

private:
    static Rocket *INSTANCE;
    RocketState state;

    void prelaunch();

    int launch_start_time_ms;
    void flight();

public:
    void beep(int frq, int length);
    void init();
    void run();

    static Rocket *getInstance()
    {
        if (!INSTANCE)
        {
            INSTANCE = new Rocket();
        }
        return INSTANCE;
    }
};
