#define FAULT_MODE_SHORTLED_BIST 0x40
#define FAULT_MODE_OPENLED 0x02

void setFaultMode(uint8_t chipAddr, uint8_t mode);
short getShortedLeds(uint8_t chipAddr);
short getOpenLeds(uint8_t chipAddr);
bool isFaultDetected(uint8_t chipAddr);
