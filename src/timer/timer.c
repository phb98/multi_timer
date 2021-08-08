#include "timer.h"
#include "config.h"
#include "24CXX.h"
#include "string.h"
/*        Public functions        */
timer_result_return_t timer_init()
{
  return TIMER_OK;
}

timer_result_return_t timer_get_result(uint8_t id, time_t current_time, timer_result_t * result)
{
  timer_t check_timer;
  if(timer_get_instant(id, &check_timer) != TIMER_OK) return TIMER_ERROR;
  if(current_time.hour == check_timer.trigger_time.hour &&
     current_time.minute == check_timer.trigger_time.minute &&
     current_time.second == check_timer.trigger_time.second &&
     check_timer.state == TIMER_ENABLE)
     {
       result->channel       = check_timer.ch;
       result->trigger_state = TIMER_TRIGGERED;
       result->value         = check_timer.value;
       if(check_timer.mode == TIMER_ONESHOT)
       {
         check_timer.state = TIMER_DISABLE;
         timer_store_instant(id, &check_timer); 
       }
     }
  else result->trigger_state = TIMER_NOT_TRIGGERED;
  return TIMER_OK;
}

/* get 1 instant from EEPROM memory */
timer_result_return_t timer_get_instant(uint8_t id, timer_t * timer)
{
  if(id >= CONFIG_NUM_OF_TIMER) return TIMER_INVALID_ID;
  uint32_t eep_addr = sizeof(timer_t) * id;
  uint8_t eep_data[sizeof(timer_t)];
  EEPROM_24CXX_read_multi(eep_addr, eep_data, sizeof(timer_t));
  memcpy(timer, eep_data, sizeof(timer_t));
  return TIMER_OK; 
}

/* store 1 instant to EEPROM memory */
timer_result_return_t timer_store_instant(uint8_t id, timer_t * timer)
{
  if(id >= CONFIG_NUM_OF_TIMER) return TIMER_INVALID_ID;
  uint32_t eep_addr = sizeof(timer_t) * id;
  uint8_t eep_data[sizeof(timer_t)];
  memcpy(eep_data, timer, sizeof(timer_t));
  EEPROM_24CXX_write_multi(eep_addr, eep_data, sizeof(timer_t));
  return TIMER_OK; 
}