// Arduino device driver for Dialog Semiconductor AS382x local dimming LED drivers

#include "as382x.h"

/*
 * @brief Lock and unlock registers
 * @param chipAddr Chip address
 * @param state 0: both locked, 1: group1 unlocked, 2: group2 unlocked, 3: both unlocked
 */
void regLockUnlock(uint8_t chipAddr, unsigned state)
{
  
  if (inRange(0, 3, state))
  {
    
    spiWriteSingleReg(chipAddr, LOCKUNLOCK, state);
    
  }
  
}

/*
 * @brief Returns a 4 byte array containing the ASIC's revision and ID.
 * @param chipAddr Chip address
 */
char* getAsicId(uint8_t chipAddr)
{

  unsigned* idRegData = spiReadMultiReg(chipAddr, 2, ASIC_ID_LSB);

  static char id[4] = {
    idRegData[3] & 0x0F, // Revision number
    idRegData[3] & 0xF0, // ASIC ID 0
    idRegData[4] & 0x0F, // ASIC ID 1
    idRegData[4] & 0xF0  // ASIC ID 2
  };

  return id;
    
}

/*
 * @brief Set current output states
 * @param chipAddr Chip address
 * @param ctx 0: group1, 1: group2, 2: both groups
 * @param state 16 bit value that maps to 16 channels
 */
void setCurrentOutputState(uint8_t chipAddr, int ctx, unsigned state)
{

  regLockUnlock(chipAddr, 3);
  
  switch(ctx)
  {
    
    case 0:
      spiWriteSingleReg(chipAddr, CUR_ON_1, state);
      break;
    case 1:
      spiWriteSingleReg(chipAddr, CUR_ON_2, state);
      break;
    case 2:
    {
      
      unsigned states[2] = 
      {
        
        (uint8_t)(state & 0xff), 
        ((uint16_t)state >> 8) & 0xFF
        
      };
      
      spiWriteMultiReg(chipAddr, 2, CUR_ON_1, states);
      break;
      
    }
    
    default:
      break;
      
  }

  regLockUnlock(chipAddr, 0);
  
}

/*
 * @brief Set control output states
 * @param chipAddr Chip address
 * @param dcdcState DC/DC coverter state
 * @param mode3dState Mode3D output signal state
 */
void setGpioState(uint8_t chipAddr, bool dcdcState, bool mode3dState)
{

  regLockUnlock(chipAddr, 3);
  
  gpioCtrl.dcdcEnable = dcdcState;
  gpioCtrl.dcdcConfig = DCDC_GPIO_MODE;
  gpioCtrl.mode3d = mode3dState;
  gpioCtrl.mode3dConfig = MODE3D_GPIO_MODE;
  gpioCtrl.xFaultConfig = FAULT_GPIO_MODE;

  spiWriteSingleReg(chipAddr, GPIO_CTRL, gpioCtrl.gpioCtrlByte);

  regLockUnlock(chipAddr, 0);
  
}

/*
 * @brief Power on sequence
 */
void as382xPowerOn(void)
{
  
  // Provide a clock reference for the PWM generators
  analogWrite(PIN_VSYNC, 127);
  analogWriteFrequency(F_VSYNC_HZ);

  // Turn DC/DC converters on
  setGpioState(0, 1, 0);

  // Set PWM controller settings to defaults
  spiWriteSingleReg(0, PWM_CTRL, 0);

  // Turn all outputs off
  setCurrentOutputState(0, 2, 0);
  
}

/*
 * @brief Power off sequence
 */
void as382xPowerOff(void)
{

  // Turn off clock reference
  digitalWrite(PIN_VSYNC, 0);

  // Turn DC/DC converters off
  setGpioState(0, 0, 0);

  // Set PWM controller settings to defaults
  spiWriteSingleReg(0, PWM_CTRL, 0);

  // Turn all outputs off
  setCurrentOutputState(0, 2, 0);
  
}
