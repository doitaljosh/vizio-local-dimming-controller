#include "as382x.h"

/*
 * @brief Enables fault detection modes on AS382x
 * @param chipAddr Chip address
 * @param mode Bit mask to write to FAULT_1 register
 */
void setFaultMode(uint8_t chipAddr, uint8_t mode)
{

  unsigned faultMode = spiReadSingleReg(chipAddr, FAULT_1);
  faultMode | mode;

  regLockUnlock(chipAddr, 3);

  spiWriteSingleReg(chipAddr, FAULT_1, faultMode);

  regLockUnlock(chipAddr, 0);
  
}

/*
 * @brief Returns a 16 bit value corresponding to any channels on which a short has been detected.
 * @param chipAddr Chip address
 */
short getShortedLeds(uint8_t chipAddr)
{

  setFaultMode(chipAddr, FAULT_MODE_SHORTLED_BIST);
  delay(100);
  unsigned* shortLedRegData = spiReadMultiReg(chipAddr, 2, SHORTLED_1);
  char data[2] = {shortLedRegData[3], shortLedRegData[4]};
  
  return (data[1] << 8) | (data[0] & 0xFF);
  
}

/*
 * @brief Returns a 16 bit value corresponding to any channels that are open.
 * @param chipAddr Chip address
 */
short getOpenLeds(uint8_t chipAddr)
{

  setFaultMode(chipAddr, FAULT_MODE_OPENLED);
  delay(100);
  unsigned* openLedRegData = spiReadMultiReg(chipAddr, 2, OPENLED_1);
  char data[2] = {openLedRegData[3], openLedRegData[4]};
  
  return (data[1] << 8) | (data[0] & 0xFF);
  
}

/*
 * @brief Returns true if there are any shorted or open LED channels. 
 * @param chipAddr Chip address
 */
bool isFaultDetected(uint8_t chipAddr)
{

  return (getShortedLeds(chipAddr) > 0 || getOpenLeds(chipAddr) > 0);
  
}
