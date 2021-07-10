#include <Arduino.h>
#include <SPI.h>
#include "pins.h"
#include "utils.h"

void spiWriteData(char* data);
char* spiRead(uint8_t chipAddr, uint8_t baseReg, uint8_t numRegs);
void spiWriteMultipleReg(uint8_t chipAddr, uint8_t numRegs, uint8_t reg, char* regData);
void spiWriteSingleReg(uint8_t chipAddr, uint8_t reg, uint8_t regData);
