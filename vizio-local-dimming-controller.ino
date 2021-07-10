/*
 * Demo code for controlling Vizio local dimming LED backlight
 * driver boards over SPI.
 * This example will turn on all LED channels at full brightness.
 */

#include "as382x.h"

char* readData;

void init()
{

  // Provide a clock reference for the PWM generators
  analogWrite(vsync, 127);
  analogWriteFrequency(24000);

  // Unlock registers
  spiWriteSingleReg(0x00, LOCKUNLOCK, 0x03);

  // CUR_ON_1, CUR_ON_2, FAULT_1, GPIO_CTRL register values respectively
  char data[4] = {0xFF, 0xFF, 0x84, 0x01};

  // Set current output states, fault modes, and GPIO states
  spiWriteMultipleReg(0x00, 4, CUR_ON_1, data);
  // Set PWM controller settings to defaults
  spiWriteSingleReg(0x00, PWM_CTRL, 0x00);
  
  // Set PWM parameters
  setPwmParams(0x00, 0, 2048, 2048, 0);

  // Re-lock registers.
  spiWriteSingleReg(0x00, LOCKUNLOCK, 0x00);
  
}

void setup()
{
  Serial.begin(115200);
  init(); 
}

void loop()
{  
  
  char* readData = spiRead(0x01, STATUS_REG, 1);

  Serial.print("Status register value: ");
  Serial.println(readData);

  delay(100);
  
}
