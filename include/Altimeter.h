
#pragma once
#define sAltimeter Altimeter::getInstance()

#define BMP_SCK_PORT = 13
#define BMP_MISO_PORT = 12
#define BMP_MOSI_PORT = 11
#define BMP_CS_PORT = 10
#define SEALEVELPRESSURE_HPA (1015.2393222666767)

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include "Buffer.h"

class Altimeter
{
private:
    static Altimeter *INSTANCE;
    Adafruit_BMP3XX bmp;
    float height_0 = 0;

    float altitude;
    float pressure;
    float temperature;

    Buffer<5> AltBuffa = Buffer<5>();
    float last_height = 0.0;
    uint32_t last_time = 0;

public:
    void init();
    void update();

    void zero();

    float getHeight();
    float getVelocity();
    float getAcceleration();

    static Altimeter *getInstance()
    {
        if (!INSTANCE)
        {
            INSTANCE = new Altimeter();
        }
        return INSTANCE;
    }
};
