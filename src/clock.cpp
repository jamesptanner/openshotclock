#include "clock.h"
#include "hardware/rtc.h"
#include "stdio.h"

#define DURATION 25

enum CURRENT_TIMER_STATE{
    RUNNING, 
    PAUSED
};

CURRENT_TIMER_STATE state;

int64_t timeLeftInUs;

absolute_time_t timeRunningStarted;

int hardwareAlarmId;

void resetTimer(void){
    timeLeftInUs =25*1000000;
    timeRunningStarted = get_absolute_time();
    hardware_alarm_set_target(hardwareAlarmId,delayed_by_us(timeRunningStarted,timeLeftInUs));
    state = RUNNING;
}

void alarmCallback(uint alarm_num){
    timeLeftInUs = 0;
    state = PAUSED;
    hardware_alarm_cancel(hardwareAlarmId);
    printf("beep\n");
}


void timerSetup(void){
    rtc_init();
    state = PAUSED;
    hardwareAlarmId = hardware_alarm_claim_unused(true);
    hardware_alarm_set_callback(hardwareAlarmId,alarmCallback);
    timeLeftInUs =25*1000000;
}


void addSecondToTimerCallback(){
    printf("Add 1 second\n");
    timeLeftInUs += 1000000;
    if(state == RUNNING){
        hardware_alarm_cancel(hardwareAlarmId);
        hardware_alarm_set_target(hardwareAlarmId,delayed_by_us(timeRunningStarted,timeLeftInUs));
    }
}
void resetTimerCallback(){
    printf("Resetting Timer\n");
    resetTimer();
}

void startStopTimerCallback(){
    if (state == PAUSED){
        printf("Resuming Timer\n");

        timeRunningStarted = get_absolute_time();
        hardware_alarm_set_target(hardwareAlarmId,delayed_by_us(timeRunningStarted,timeLeftInUs));
        state = RUNNING;
    }
    else {
        printf("Stopping Timer\n");
        absolute_time_t stopTime = get_absolute_time();
        hardware_alarm_cancel(hardwareAlarmId);
        timeLeftInUs = absolute_time_diff_us(timeRunningStarted,stopTime);
        state = PAUSED;
    }
}

int8_t getSecondsLeft(){

    if (state == PAUSED){
        return (int8_t) (timeLeftInUs/1000000);
    }

    return (int8_t) ((timeLeftInUs - absolute_time_diff_us(timeRunningStarted,get_absolute_time()))/1000000);
}