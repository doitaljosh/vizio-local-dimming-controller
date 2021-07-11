#include <Arduino.h>
#include "utils.h"

/*
 * @brief Print a string of hex values separated by spaces given an array.
 * @param data Array to decode
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
 * @brief Checks if a value is between two given values.
 * @param minValue Minimum acceptable value
 * @param maxValue Maximum acceptable value
 * @param curValue Value to check
 */
bool inRange(unsigned minValue, unsigned maxValue, unsigned curValue)
{
  return((curValue - minValue) <= (maxValue - minValue));
}
