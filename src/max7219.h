#include "pico/stdlib.h"

void configureMax7219(const uint8_t data, const uint8_t load, const uint8_t clock);
void blankScreen();
void setCustomDigit(const uint8_t index, const uint8_t digit) ;
void setNumber(int32_t num) ;
void setDigit(const uint8_t index, const uint8_t digit, const bool dp);
void setShutdown(const bool shutdown) ;
void setBrightness(const uint8_t intensity) ;
void setDecodeMode(const uint8_t digitsToDecode) ;
void setNumOfDigits(const int num) ;
void setTestMode(const bool testModeOn) ;
