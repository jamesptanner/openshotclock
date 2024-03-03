#include "max7219.h"
#include "clock.h"

#include "pico/stdlib.h"
#include "stdio.h"

#define MAX_LOAD 6
#define MAX_DIN 13
#define MAX_CLK 12
#define CTRL_ADD 8
#define CTRL_RST 10
#define CTRL_STR_STOP 11 

void setupTimer(){
  gpio_set_irq_enabled_with_callback(CTRL_ADD, GPIO_IRQ_EDGE_RISE, true, &addSecondToTimerCallback);
  gpio_set_irq_enabled_with_callback(CTRL_RST, GPIO_IRQ_EDGE_RISE, true, &resetTimerCallback);
  gpio_set_irq_enabled_with_callback(CTRL_STR_STOP, GPIO_IRQ_EDGE_RISE, true, &startStopTimerCallback);
  timerSetup();
}

int main(){
  stdio_init_all();
  
  //load -> gpio6 -> pin9
  //clock -> gpio12 -> pin16
  //data in -> gpio13 -> pin17
  configureMax7219(MAX_DIN,MAX_LOAD,MAX_CLK,2);
  setupTimer();

  uint8_t num = 0;
  while (true){ 
    num = getSecondsLeft();
    setNumber(num);
    sleep_ms(100);

  }
  return 0;
}