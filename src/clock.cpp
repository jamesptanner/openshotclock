#include "clock.h"
#include "hardware/rtc.h"

#define DURATION 25

enum CURRENT_TIMER_STATE{
    RUNNING, 
    PAUSED
};

CURRENT_TIMER_STATE state;

void resetTimer(void){
    
}

void timerSetup(void){
    rtc_init();
    state = PAUSED;

    resetTimer();
}

void addSecondToTimerCallback(unsigned int, long unsigned int){

}
void resetTimerCallback(unsigned int, long unsigned int){

}
void startStopTimerCallback(unsigned int, long unsigned int){

}

uint8_t getSecondsLeft(){

    return -1;
}