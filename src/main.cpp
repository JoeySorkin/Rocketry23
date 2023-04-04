#include <Arduino.h>
#include "Rocket.h"
#include "Decoupler.h"
void setup()
{
  sRocket->init();

  // put your setup code here, to run once:
}

void loop()
{
  sRocket->run();
  delay(10);
  // put your main code here, to run repeatedly:
}