#include <Arduino.h>
#include "button_lib.h"
#include "24CXX.h"
#include "display_20x4.h"
#include "timer.h"
#include "Wire.h"
#include "config.h"
#include "rtc.h"
#include "ui.h"
volatile uint8_t ui_need_update = 0;
void setup() {
 // Serial.begin(115200);
  Wire.begin();
  #if (I2C_FAST_SPEED)
  Wire.setClock(400000L); // Set clock to 400khz
  #endif
  display_init();
  button_initialize(25,100); 
  EEPROM_24CXX_init();
  timer_init();
  rtc_init();
  // Setup GPIO
  pinMode(CONFIG_BUTTON_ENTER_PIN, INPUT_PULLUP);
  pinMode(CONFIG_BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(CONFIG_BUTTON_RIGHT_PIN, INPUT_PULLUP);
  /* setup timer 2 for 10ms tick */
  /* this setup is for 16MHz atmega */
  TCCR2A = (1<<WGM21); // CTC mode
  TCCR2B = 0x7; // 16000/1024 = 15.625 khz tick rate ->0.064ms per tick
  OCR2A  = 157; // 10ms
  ui_init(); // must init after display init and button init
  //wait for a while for user
  delay(CONFIG_BOOT_TIME);
  TIMSK2 = (1 << OCIE2A);
}

void loop()
{
  time_t now;
  static uint8_t last_sec;
  uint8_t need_timer_result = 0;
  timer_result_t result;
  while(1)
  {
    if(need_timer_result)
    {
      for(uint16_t i = 0; i < CONFIG_NUM_OF_TIMER; i++)
      {
        timer_get_result(i, now, &result);
      }
      need_timer_result = 0;
    }
    if(ui_need_update)
    {
      //get current time
      rtc_get_time(&now);
      // new second, need to get new result from timer
      if(now.second != last_sec)
      {
        need_timer_result = 1;
        last_sec = now.second;
      }
      ui_update();
      ui_need_update = 0;
    }
  }
}

ISR(TIMER2_COMPA_vect)
{
  static uint8_t count;
  button_update(); // poll button
  if(count >= 10)
  {
    //ui will run at 10x slower than polling rate, which is 10hz
    ui_need_update = 1;
    count = 0;
  }
  else count++;
} 