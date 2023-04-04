#pragma once
#include "SD.h"
#include "Arduino.h"
#define sLogger Logger::getInstance()
#include <Servo.h>

#define SERVO_PIN 10
// class Logger
// {
//     // private:
//     //     static Logger *INSTANCE;
//     //     const char filename[] = "logs.txt";
//     //     File logFile;
//     //     String buffer;
//     //     long lastMillis = 0;

//     // public:
//     //     void init();
//     //     void update();
//     //     void log(String msg);
//     //     static Logger *getInstance()
//     //     {
//     //         if (!INSTANCE)
//     //         {
//     //             INSTANCE = new Logger();
//     //         }
//     //         return INSTANCE;
//     //     }
// };
