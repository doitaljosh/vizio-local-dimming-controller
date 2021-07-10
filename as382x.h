#include "regdefs.h"
#include "spiInterface.h"
#include "pins.h"
#include "utils.h"

// For determining chip addresses

#define NUM_CHIPS_PER_BOARD 2
#define NUM_BOARDS 1

#define MAX_PWM_PD 4096
#define MAX_PWM_DEL 4096
#define MAX_PWM_HT 4096

void setPwmParams(uint8_t chipAddr, int channel, long period, long delayValue, long highTime);

struct fault1
{
  unsigned autoOffOnOpenLed : 1; // Turn off channels on open LED channel
  unsigned openLedDetEn : 1; // Enable open LED detection
  unsigned autoOffOnOverTemp : 1; // Turn off channels on over temp condition
  unsigned retryOpenLedDet : 1; // Retry open LED detection after autoOffOnOpenLed is triggered
  unsigned shortDetCmpEn : 2; // Enable short detection using comparators
  unsigned shortDetBistEn : 1; // Start BIST for short detection
  unsigned uvLockoutEn : 1; // Turn off channels on undervoltage
};

struct gpioCtrl
{
  unsigned dcdcEnable : 1; // DCDC enable GPIO state
  unsigned dcdcConfig : 2; // DCDC enable GPIO mode
  unsigned mode3d : 1; // mode3d GPIO state
  unsigned mode3dConfig : 2; // mode3d GPIO mode
  unsigned xFaultConfig : 2; // xFault GPIO mode
};

struct currentCtrl
{
  unsigned slewRate : 2; // Slew rate of output drivers
  unsigned dacRef : 1; // DAC reference voltage select
  unsigned dacRefBufOff : 1; // Disable DAC output buffering 
  unsigned biasCurComp : 1; // Enable bias current compensation
  unsigned acFbOff : 1; // Disable AC feedback
};
