#include <Arduino.h>

// Maximum values for PWM controller (12 bit)
#define MAX_PWM_PD 8191
#define MAX_PWM_DEL 4095
#define MAX_PWM_HT 4095

// Default PWM settings
#define PWM_DEFAULT_PERIOD 100
#define PWM_DEFAULT_DELAY 0

void setPwmParams(uint8_t chipAddr, int channel, long period, long delayValue, long highTime);
void analogWriteAs382x(uint8_t chipAddr, int channel, int value);

union
{
  unsigned char pwmCtrlByte;
  struct
  {
    unsigned clockSrc0 : 1, // Clock source for internal PWM generators: 0: internal, 1: HSYNC
             updateMode : 1, // When PWM registers are updated: 0: rising edge of xCS, 1: VSYNC edge
             directPwmEnable : 1, // External or internal PWM signal: 0: internal, 1: VSYNC
             vsyncEdge : 1, // VSYNC trigger: 0: rising, 1: falling
             vsyncDetEnable : 1, // VSYNC detection: 0: off, 1: on
             invertPwm : 1, // PWM signal inversion: 0: normal, 1: inverted
             clockSrc1 : 1, // Clock source for internal PWM generators: 0: clockSrc0, 1: PLL output
             periodSrc : 1; // DPLL frequency generation: 0: VSYNC*PWMperiod, 1: VSYNC*PLLmulti
  };
} pwmCtrl;
