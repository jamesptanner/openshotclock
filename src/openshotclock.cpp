#include "max7219.h"
#include "pico/stdlib.h"
#include "stdio.h"
int main(){
  stdio_init_all();

  //load -> gpio6 -> pin9
  //clock -> gpio12 -> pin16
  //data in -> gpio13 -> pin16
  configureMax7219(13,6,12);
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