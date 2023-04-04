#include "Altimeter.h"

Altimeter *Altimeter::INSTANCE = nullptr;

void Altimeter::init()
{
    Serial.println("Initializing BMP...");
    // wait for BMP to I2Calize
    bmp.begin_I2C();
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_100_HZ);
    for (int i = 0; i < 4; i++)
    {
        bmp.readAltitude(SEALEVELPRESSURE_HPA);
    }
    delay(50);
    bmp.performReading();
    zero();

    Serial.println("BMP initialized.");
}

void Altimeter::update()
{
    last_height = getHeight();
    last_time = millis();

    bmp.performReading();
    temperature = bmp.temperature;                                // temperature (celsius)
    pressure = bmp.pressure / 100.0;                              // pressure (hPa)
    altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA) - height_0; // altitude (m)
    AltBuffa.add(altitude);
}
float Altimeter::getHeight()
{
    return AltBuffa.getAverage();
}

float Altimeter::getVelocity()
{
    return (getHeight() - last_height) / ((millis() - last_time) / 1000.0);
}

void Altimeter::zero()
{
    height_0 = bmp.readAltitude(SEALEVELPRESSURE_HPA);
};