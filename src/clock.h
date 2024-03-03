#include "pico/stdlib.h"

void addSecondToTimerCallback(unsigned int pin, long unsigned int event);
void resetTimerCallback(unsigned int pin, long unsigned int event);
void startStopTimerCallback(unsigned int pin, long unsigned int event);
uint8_t getSecondsLeft();
void timerSetup(void);
