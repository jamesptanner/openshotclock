
#include "max7219.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include <stdio.h>

uint8_t max_clock, max_data, max_load;

void writeToMax(const int16_t cmd);
int16_t buildCmd(const uint8_t addr, const uint8_t data );

void configureMax7219(const uint8_t data, const uint8_t load, const uint8_t clock, const uint8_t numOfDigits){
  printf("Configuring Max7219. datapin: %d loadpin: %d clockpin: %d\n",data,load,clock);

  max_data=data;
  gpio_init(data);
  gpio_set_dir(data, GPIO_OUT);
  max_clock=clock;
  gpio_init(clock);
  gpio_set_dir(clock, GPIO_OUT);
  max_load=load;
  gpio_init(load);
  gpio_set_dir(load, GPIO_OUT);


  setShutdown(true);
  setNumOfDigits(numOfDigits);
  setDecodeMode(0xff);
  // setNumber(0);
  setBrightness(1);
  setShutdown(false);
  setTestMode(false);
}

void blankScreen(){
  printf("blanking Screen\n");
  for (uint8_t i = 0 ; i < 8; i++){
    setCustomDigit(i,0xf);
  }
}

void setNumber(int32_t num) {
  printf("Writing number %d\n", num);
  blankScreen();
  if (num == 0){
    setDigit(0,0,false);
  }
  uint8_t index;
  while (num != 0) {
    uint8_t digit = num % 10;
    num = num / 10;
    setDigit(index,digit,false);
    index++;
  }
}

void setCustomDigit(const uint8_t index, const uint8_t digit){
  if (index <0) return;

  const uint8_t addr = index;
  const int16_t cmd = buildCmd(addr,digit);
  if (cmd != 0xff){
    writeToMax(cmd);
  }

}

void setDigit (const uint8_t index, const uint8_t digit, const bool dp) {
  // printf("Writing digit %d to %d\n", digit, index);
  if (digit< 0 || digit >9) return;
  if (index <0) return;

  const uint8_t addr = index+1;
  const uint8_t data = digit | (dp ? 0x8000:0);
  const int16_t cmd = buildCmd(addr,data);
  if (cmd != 0xffff){
    writeToMax(cmd);
  }

}

void setShutdown(const bool shutdown) {
  printf("setShutdown %d\n", shutdown);
  const uint8_t addr = 0x0c;
  const uint8_t data = shutdown ? 0x0 : 0x1;
  const int16_t cmd = buildCmd(addr,data);
  if (cmd != 0xffff){
    writeToMax(cmd);
  }
}

void setBrightness(const uint8_t intensity) {
  printf("setBrightness %d\n", intensity);
  if (intensity > 16) return;
  const uint8_t addr = 0x0a;
  const int16_t cmd = buildCmd(addr,intensity);
  if (cmd != 0xffff){
    writeToMax(cmd);
  }

}

void setDecodeMode(const uint8_t digitsToDecode) {
  printf("setDecodeMode %d\n", digitsToDecode);
  const uint8_t addr = 0x09;
  const int16_t cmd = buildCmd(addr,digitsToDecode);
  if (cmd != 0xffff){
    writeToMax(cmd);
  }
}

void setNumOfDigits(const int num) {
  printf("setNumOfDigits %d\n", num);
  const uint8_t addr = 0x0b;
  const uint8_t data = num-1;
  const int16_t cmd = buildCmd(addr,data);
  if (cmd != 0xffff){
    writeToMax(cmd);
  }

}

void setTestMode(const bool testModeOn) {
  printf("setTestMode %d\n", testModeOn);
  const uint8_t addr = 0x0f;
  const uint8_t data = testModeOn ? 0x1: 0x0;
  const int16_t cmd = buildCmd(addr,data);
  if (cmd != 0xffff){
    writeToMax(cmd);
  }

}

int16_t buildCmd(const uint8_t addr, const uint8_t data ) {
  if (addr >= 0x1000) return 0xffff;
  return addr << 8 | data;
}


void writeBit(const int16_t bit) {
  // printf("%d",bit);
  // sleep_us(1);
  gpio_put(max_clock,0);
  // sleep_us(1);
  gpio_put(max_data,bit & 0x1);
  // sleep_us(1);
  gpio_put(max_clock,1);
  // sleep_us(1);
}

void writeToMax(const int16_t cmd) {
  // printf("0x%04x\n",cmd);
  gpio_put(max_load,0);
  int16_t cmdCpy = cmd;
  for (int i = 0; i < 16; i++){
    writeBit((cmdCpy & 0x8000) == 0x8000 ? 1:0 );
    cmdCpy = (cmdCpy << 1) & 0xffff;
  }
  // printf("\n");
  gpio_put(max_load,1);
  sleep_us(1);
  gpio_put(max_load,0);
}