#include "Logger.h"
#include "Rocket.h"
#include <SPI.h>
#include <SD.h>

Logger *Logger::INSTANCE = nullptr;
void Logger::init()
{
    buffer.reserve(2048);
    if (!SD.begin(chipSelect))
    {
        Serial.println("Card failed, or not present");
        sRocket->beep(500, 9000);
        while (1)
            ;

        logFile = SD.open(filename.c_str(), FILE_WRITE);
        if (!logFile)
        {
            Serial.print("error opening ");
            Serial.println(filename);
            while (1)
                ;
        }
        logFile.println("TIME,SUBSYSTEM,TYPE,MESSAGE");
    }
}
void Logger::log(String subsystem, String type, String msg)
{
    logFile = SD.open(filename, FILE_WRITE);

    // if the file opened okay, write to it:

    String log = String(millis()) + "," + subsystem + type + msg + "\n";
    // buffer += log;
    logFile.println(log);
    logFile.close();
}
void Logger::update()
{
    // logFile.flush();
    // unsigned int chunkSize = logFile.availableForWrite();
    // if (chunkSize && buffer.length() >= chunkSize)
    // {
    //     logFile.write(buffer.c_str(), chunkSize);
    //     buffer.remove(0, chunkSize);
    // }
}
