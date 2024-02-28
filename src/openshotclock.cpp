#include "max7219.h"
#include "pico/stdlib.h"
#include "stdio.h"

#define MAX_LOAD 6
#define MAX_DIN 13
#define MAX_CLK 12
#define CTRL_ADD 8
#define CTRL_RST 10
#define CTRL_STR_STOP 11 

int main(){
  stdio_init_all();

  //load -> gpio6 -> pin9
  //clock -> gpio12 -> pin16
  //data in -> gpio13 -> pin16
  configureMax7219(MAX_DIN,MAX_LOAD,MAX_CLK);
  setShutdown(false);
  setNumOfDigits(2);
  setDecodeMode(0xff);
  // setNumber(0);
  setBrightness(1);
  setShutdown(true);
  setTestMode(false);
  uint8_t num = 0;
  while (true){ 
    sleep_ms(1000);
    setNumber(num);
    num++;
  }
  return 0;
}