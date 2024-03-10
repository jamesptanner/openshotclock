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
#define BUZZER 7

bool ready = false;
int64_t lastButton = 0;
void timerCallback(unsigned int pin, long unsigned int){
  if(!ready) return;
  //debounce the pin

  if(absolute_time_diff_us(from_us_since_boot(lastButton),get_absolute_time()) > 50000){
    lastButton = to_us_since_boot(get_absolute_time());
    printf("pin %d: ", pin);
    switch (pin){
      case CTRL_ADD:
        addSecondToTimerCallback();
        break;
      case CTRL_RST:
        resetTimerCallback();
        break;
      case CTRL_STR_STOP:
        startStopTimerCallback();
        break; 
    }
  }
  else {
    printf("debounce!!!!\n");
  }
}


void setupTimer(){


  gpio_init(CTRL_ADD);
  gpio_set_dir(CTRL_ADD, GPIO_IN);
  gpio_set_pulls(CTRL_ADD,true,false);
  gpio_init(CTRL_RST);
  gpio_set_dir(CTRL_RST, GPIO_IN);
  gpio_set_pulls(CTRL_RST,true,false);
  gpio_init(CTRL_STR_STOP);
  gpio_set_dir(CTRL_STR_STOP, GPIO_IN);
  gpio_set_pulls(CTRL_STR_STOP,true,false);

  gpio_init(BUZZER);
  gpio_set_dir(BUZZER,true);


  // gpio_set_irq_callback();
  gpio_set_irq_enabled_with_callback(CTRL_ADD, GPIO_IRQ_EDGE_RISE, true, &timerCallback);
  gpio_set_irq_enabled(CTRL_RST, GPIO_IRQ_EDGE_RISE, true);
  gpio_set_irq_enabled(CTRL_STR_STOP, GPIO_IRQ_EDGE_RISE, true);
  timerSetup();
  sleep_ms(100); // let the buttons debounce.
  ready = true;
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