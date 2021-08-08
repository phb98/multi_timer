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
  Serial.begin(115200);
  Wire.begin();
  #if (I2C_FAST_SPEED)
  Wire.setClock(400000L); // Set clock to 400khz
  #endif
  display_init();
  button_initialize(50,200); 
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
  OCR2A  = 78; // 5ms
  ui_init(); // must init after display init and button init
  //wait for a while for user
  delay(CONFIG_BOOT_TIME);
  TIMSK2 = (1 << OCIE2A);
}

void loop() {
  time_t now;
  //get result for each timer
  timer_result_t result;
  uint32_t t = millis();
  for(uint16_t i = 0; i < CONFIG_NUM_OF_TIMER; i++)
  {
    timer_get_result(i, now, &result);
    if(result.trigger_state == TIMER_TRIGGERED)
    {

    }
  }
  Serial.println(((PINB >> 1) & 0x1));
  if(ui_need_update)
  {
    //get current time
    rtc_get_time(&now);
    ui_update();
    ui_need_update = 0;
  }
}

ISR(TIMER2_COMPA_vect)
{
  static uint8_t count;
  button_update(); // poll button
  if(count >= 20)
  {
    //ui will run at 10x slower than polling rate, which is 10hz
    ui_need_update = 1;
    count = 0;
  }
  else count++;
} 