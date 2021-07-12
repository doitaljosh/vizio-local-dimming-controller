#include <Arduino.h>
#include "as382x_regdefs.h"
#include "as382x_spi.h"
#include "as382x_pwm.h"
#include "as382x_fault_det.h"
#include "pins.h"
#include "utils.h"

// For determining chip addresses
#define NUM_CHIPS_PER_BOARD 2 // The number of AS382x chips on each board (usually two).
#define NUM_BOARDS 1 // The number of boards connected to the SPI bus ().

// GPIO polarity settings
#define DCDC_GPIO_MODE 0
#define MODE3D_GPIO_MODE 0
#define FAULT_GPIO_MODE 0

// VSYNC frequency
#define F_VSYNC_HZ 24000

void regLockUnlock(uint8_t chipAddr, unsigned state);
char* getAsicId(uint8_t chipAddr);
void setCurrentOutputState(uint8_t chipAddr, int ctx, unsigned state);
void setGpioState(uint8_t chipAddr, bool dcdcState, bool mode3dState);
void as382xPowerOn(void);
void as382xPowerOff(void);

union
{
  unsigned char fault1Byte;
  struct
  {
    unsigned autoOffOnOpenLed : 1, // Turn off channels on open LED channel
             openLedDetEn : 1, // Enable open LED detection
             autoOffOnOverTemp : 1, // Turn off channels on over temp condition
             retryOpenLedDet : 1, // Retry open LED detection after autoOffOnOpenLed is triggered
             shortDetCmpEn : 2, // Enable short detection using comparators
             shortDetBistEn : 1, // Start BIST for short detection
             uvLockoutEn : 1; // Turn off channels on undervoltage
  };
} fault1;

union
{
  unsigned char gpioCtrlByte;
  struct
  {
    unsigned dcdcEnable : 1, // DCDC enable GPIO state
             dcdcConfig : 2, // DCDC enable GPIO mode
             mode3d : 1, // mode3d GPIO state
             mode3dConfig : 2, // mode3d GPIO mode
             xFaultConfig : 2; // xFault GPIO mode
  };
} gpioCtrl;

union
{
  unsigned char currentCtrlByte;
  struct
  {
    unsigned slewRate : 2, // Slew rate of output drivers
             dacRef : 1, // DAC reference voltage select
             dacRefBufOff : 1, // Disable DAC output buffering 
             biasCurComp : 1, // Enable bias current compensation
             acFbOff : 1; // Disable AC feedback
  };
} currentCtrl;
