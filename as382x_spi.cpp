#include "as382x.h"

/*
 * Notes on SPI interface:
 * 
 * There are two acceptable modes of connecting these boards together:
 * 
 * 1. PARALLEL MODE (fastest, not implemented in code): 
 * All SDO, SDI, SCLK lines in parallel with one CS per board.
 * 
 * 2. DAISY CHAIN MODE (slower, but recommended): 
 * SDO of one board connects to the SDI of the next board, then SDO of last board 
 * and SDI of the first board connects to the Arduino, with all SCLK lines still in parallel,
 * but all CS lines are now in parallel as well.
 */

void spiWriteData(char* data)
{
  
  digitalWrite(PIN_xCS, LOW);

  for (int i = 0; i <= sizeof(data); i++) {
    SPI.transfer(data[i]);
  }

  digitalWrite(PIN_xCS, HIGH);
  
}

char* spiRead(uint8_t chipAddr, uint8_t baseReg, uint8_t numRegs)
{

  int overhead;
  
  digitalWrite(PIN_xCS, LOW);

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

  digitalWrite(PIN_xCS, HIGH);

  return readData;
}

void spiWriteMultipleReg(uint8_t chipAddr, uint8_t numRegs, uint8_t reg, unsigned* regData)
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

void spiWriteSingleReg(uint8_t chipAddr, uint8_t reg, unsigned regData)
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
