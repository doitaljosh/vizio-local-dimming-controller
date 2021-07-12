/*
 * Demo code for controlling Vizio local dimming LED backlight
 * driver boards over SPI.
 * This example will turn on all LED channels at full brightness.
 */

#include "as382x.h"

char* readData;

void setup()
{
  
  Serial.begin(115200);
  
  as382xPowerOn(); 

  // Turn all 32 outputs on
  setCurrentOutputState(0, 2, 0xFFFF);

  // Set PWM parameters
  setPwmParams(0, 0, 2048, 2048, 0);

  sequence(500);
}

void sequence(int interval)
{
  while(1)
  {
    setCurrentOutputState(0, 2, 0x5555);
    delay(interval);
    setCurrentOutputState(0, 2, 0xAAAA);
    delay(interval);  

    Serial.print("Open LED's on chip 1: ");
    Serial.print(getOpenLeds(1), HEX);
    Serial.print(", chip 2: ");
    Serial.println(getOpenLeds(2), HEX);
  }
}

void loop()
{  
  
}
