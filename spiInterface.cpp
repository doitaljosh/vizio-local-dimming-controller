#include "spiInterface.h"

void spiWriteData(char* data)
{
  
  digitalWrite(cs, LOW);

  for (int i = 0; i <= sizeof(data); i++) {
    SPI.transfer(data[i]);
  }

  digitalWrite(cs, HIGH);
  
}

char* spiRead(uint8_t chipAddr, uint8_t baseReg, uint8_t numRegs)
{

  int overhead;
  
  digitalWrite(cs, LOW);

  SPI.transfer(chipAddr);
  if (numRegs > 1) {
    SPI.transfer(numRegs);
    SPI.transfer(baseReg);
    overhead = 3;
  } else {
    SPI.transfer(baseReg);
    SPI.transfer(0x00);
    overhead = 2;
  }

  char readData[numRegs + overhead];

  for (int i=0; i<=numRegs + overhead; i++) {
    readData[i] = SPI.transfer(0x00);
  }

  digitalWrite(cs, HIGH);

  return readData;
}

void spiWriteMultipleReg(uint8_t chipAddr, uint8_t numRegs, uint8_t reg, char* regData)
{   
  char data[numRegs + 3];

  data[0] = chipAddr;
  data[1] = numRegs;
  data[2] = reg;

  for (int i=0; i<=numRegs; i++) {
    data[i+3] = regData[i];
  }

  printHexString(data);
  spiWriteData(data);
}

void spiWriteSingleReg(uint8_t chipAddr, uint8_t reg, uint8_t regData)
{
  char data[5] = {
      chipAddr,
      reg,
      regData,
      0x00,
      0x00
    };

  printHexString(data);
  spiWriteData(data);  
}
