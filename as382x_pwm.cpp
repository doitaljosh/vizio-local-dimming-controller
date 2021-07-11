#include "as382x.h"

/*
 *  Sets the PWM parameters, given the chip address, channel, period, relative delay, and high time. 
 */
void setPwmParams(uint8_t chipAddr, int channel, long period, long delayValue, long highTime)
{

  regLockUnlock(chipAddr, 3);
  
  if(
  inRange(0, MAX_PWM_PD, period) && 
  inRange(0, MAX_PWM_DEL, delayValue) && 
  inRange(0, MAX_PWM_HT, highTime)
  ) {
    
    char pwmPeriodData[5] = {
      chipAddr, 
      0x02, 
      PWM_PERIOD_LSB, 
      (period & 0xFF), 
      (period & 0xF00)
    };

    spiWriteData(pwmPeriodData);
    
    // If the channel value is zero, set all PWM channels to the same parameters.
    bool writeToAllChannels = (channel != 0) ? true : false;
  
    if (writeToAllChannels)
    {
      
      char data[35];
      
      data[0] = chipAddr;
      data[1] = 32;
      data[2] = PWM_DEL_BASE;
      
      for (int i = 3; i <= 33; i+=2) {
  
        data[i] = delayValue & 0xff;
        data[i+1] = delayValue & 0x700;
        
      }
      
      spiWriteData(data);
  
      data[2] = PWM_HT_BASE;
  
      for (int i = 3; i <= 33; i+=2) {
  
        data[i] = highTime & 0xff;
        data[i+1] = highTime & 0x700;
        
      }
  
      spiWriteData(data);
      
    } else {
  
      char data[5];
  
      data[0] = chipAddr;
      data[1] = 5;
      
      data[2] = (PWM_DEL_BASE - 2) + (2 * channel);
      data[3] = delayValue & 0xff;
      data[4] = delayValue & 0x700;
  
      spiWriteData(data);
  
      data[2] = (PWM_HT_BASE - 2) + (2 * channel);
      data[3] = highTime & 0xff;
      data[4] = highTime & 0x700;
  
      spiWriteData(data);

    }
    
  }

  regLockUnlock(chipAddr, 0);
  
}

void analogWriteAs382x(uint8_t chipAddr, int channel, int value)
{
 
  setPwmParams(
    chipAddr,
    channel,
    PWM_DEFAULT_PERIOD,
    PWM_DEFAULT_DELAY,
    map(value, 0, 255, 0, PWM_DEFAULT_PERIOD)
  );

}
