// Arduino device driver for Dialog Semiconductor AS382x local dimming LED drivers

#include "as382x.h"

void regLockUnlock(uint8_t chipAddr, unsigned state)
{
  
  if (inRange(0, 3, state))
  {
    
    spiWriteSingleReg(chipAddr, LOCKUNLOCK, state);
    
  }
  
}

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
      
      spiWriteMultipleReg(chipAddr, 2, CUR_ON_1, states);
      break;
      
    }
    
    default:
      break;
      
  }

  regLockUnlock(chipAddr, 0);
  
}

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
