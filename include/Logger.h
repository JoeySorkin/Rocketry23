#pragma once
#include "SD.h"
#include "Arduino.h"
#define sLogger Logger::getInstance()

class Logger
{
private:
    static Logger *INSTANCE;
    String filename = String("aunch.txt");
    File logFile;
    String buffer;
    long lastMillis = 0;
    const int chipSelect = 4;

public:
    void init();
    void update();
    void log(String subsystem, String type, String msg);
    static Logger *getInstance()
    {
        if (!INSTANCE)
        {
            INSTANCE = new Logger();
        }
        return INSTANCE;
    }
};
