#include <Arduino.h>
#include "utils.h"

void printHexString(char* data)
{
  for (int i=0; i<=sizeof(data); i++)
  {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
