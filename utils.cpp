#include <Arduino.h>
#include "utils.h"

/*
 * Print a string of hex values separated by spaces given an array.
 */
void printHexString(char* data)
{
  for (int i=0; i<=sizeof(data); i++)
  {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

/*
 * Checks if a value is between two given values.
 */
bool inRange(unsigned minValue, unsigned maxValue, unsigned curValue)
{
  return((curValue - minValue) <= (maxValue - minValue));
}
