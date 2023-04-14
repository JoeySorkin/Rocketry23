
#pragma once
#define sRocket Rocket::getInstance()

#define BuzzerPort 1
#define LAUNCH_VELOCITY_THRESHOLD 10 // m/s
#define TIME_TO_DECOUPLE 5650       // ms
#define ALT_TO_DECOUPLE 100         // m
#define VEL_TO_DECOUPLE -6          // m/s

// #define LAUNCH_VELOCITY_THRESHOLD 3 // m/s
// #define TIME_TO_DECOUPLE 5650       // ms
// #define ALT_TO_DECOUPLE 2           // m
// #define VEL_TO_DECOUPLE -3          // m/s

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
    void decoupled();

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
