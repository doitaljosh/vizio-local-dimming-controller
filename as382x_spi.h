#include <SPI.h>

unsigned * spiReadMultiReg(uint8_t chipAddr, uint8_t baseReg, uint8_t numRegs);
unsigned spiReadSingleReg(uint8_t chipAddr, uint8_t reg);
void spiWriteData(char* data);
void spiWriteMultiReg(uint8_t chipAddr, uint8_t numRegs, uint8_t reg, unsigned* regData);
void spiWriteSingleReg(uint8_t chipAddr, uint8_t reg, unsigned regData);
