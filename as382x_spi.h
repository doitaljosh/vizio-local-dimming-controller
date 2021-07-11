#include <SPI.h>

void spiWriteData(char* data);
char* spiRead(uint8_t chipAddr, uint8_t baseReg, uint8_t numRegs);
void spiWriteMultipleReg(uint8_t chipAddr, uint8_t numRegs, uint8_t reg, unsigned* regData);
void spiWriteSingleReg(uint8_t chipAddr, uint8_t reg, unsigned regData);
