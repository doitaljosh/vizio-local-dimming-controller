// Register addresses

// Control and status registers
#define CUR_ON_1 0x01
#define CUR_ON_2 0x02
#define FAULT_1 0x03
#define GPIO_CTRL 0x04
#define FB_SEL_1 0x05
#define FB_SEL_2 0x06
#define CURR_CTRL 0x07
#define SHORTLED_1 0x08
#define SHORTLED_2 0x09
#define OPENLED_1 0x0a
#define OPENLED_2 0x0b
#define VDAC_H 0x0c
#define VDAC_L 0x0d
#define FB_ON_1 0x0e
#define FB_ON_2 0x0f
#define IDAC_FB1_COUNTER 0x10
#define IDAC_FB2_COUNTER 0x11
#define FBLOOP_CTRL 0x12
#define LOCKUNLOCK 0x36
#define ASIC_ID_LSB 0x57
#define ASIC_ID_MSB 0x58
#define STATUS_REG 0x60
#define PLL_MULTI_MSB 0x61
#define PLL_MULTI_LSB 0x62
#define SHORT_BIST_CTRL1 0x63
#define SHORT_BIST_MAXSTEP 0x64
#define SHORT_BIST_CTRL2 0x65
#define COMP_REG_1 0x6c
#define COMP_REG_2 0x6d

// PWM registers
#define PWM_CTRL 0x13
// Period
#define PWM_PERIOD_LSB 0x14
#define PWM_PERIOD_MSB 0x15
// Delay
#define PWM_DEL_BASE 0x16
// High time
#define PWM_HT_BASE 0x37
