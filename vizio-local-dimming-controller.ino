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
  
}

void loop()
{  
  
  char* readData = spiRead(0x01, 1, STATUS_REG);

  Serial.print("Status register value: ");
  Serial.println(readData);

  delay(100);
  
}
