#include <Arduino.h>
#include "button_lib.h"
#include "24CXX.h"
void setup() {
  Serial.begin(115200);
  Serial.println(EEPROM_24CXX_init());
  button_initialize(10,10);
  uint8_t temp[64];
  for(int i=0; i<64;i++) temp[i]=i*2;
  EEPROM_24CXX_write_multi(20,temp,64);
  for(int i=0; i<64;i++) temp[i]=0;
  EEPROM_24CXX_read_multi(20,temp,64);
  for(int i=0; i<64;i++) Serial.println(temp[i]);
}

void loop() {
  // put your main code here, to run repeatedly:
}