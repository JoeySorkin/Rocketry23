#include "Logger.h"
#include "Rocket.h"
// void Logger::init()
// {
//     buffer.reserve(1024);
//     if (!SD.begin())
//     {
//         Serial.println("Card failed, or not present");
//         sRocket->beep(90, 5000);
//         while (1)
//             ;

//         logFile = SD.open(filename, FILE_WRITE);
//         if (!logFile)
//         {
//             Serial.print("error opening ");
//             Serial.println(filename);
//             while (1)
//                 ;
//         }
//     }
// }

// void Logger::update()
// {
//     unsigned int chunkSize = logFile.availableForWrite();
//     if (chunkSize && buffer.length() >= chunkSize)
//     {
//         // write to file and blink LED
//         digitalWrite(LED_BUILTIN, HIGH);
//         logFile.write(buffer.c_str(), chunkSize);
//         digitalWrite(LED_BUILTIN, LOW);

//         // remove written data from buffer
//         buffer.remove(0, chunkSize);
//     }
// }
