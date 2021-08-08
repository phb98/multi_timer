#pragma once
#ifdef __cplusplus
extern "C"{
#endif
#include "stdint.h"
typedef struct
{
  uint8_t  hour;
  uint8_t  minute;
  uint8_t  second;
  uint8_t  weekday;
  uint8_t  day;
  uint8_t  month;
  uint16_t year;
} time_t;
typedef enum {
  TIMER_DISABLE = 0,
  TIMER_ENABLE
} timer_state_t;
typedef enum{
  TIMER_ONESHOT,
  TIMER_AUTO_RELOAD
} timer_mode_t;
typedef enum{
  TIMER_TRIGGERED,
  TIMER_NOT_TRIGGERED
} timer_trigger_t;
typedef struct 
{
  time_t trigger_time;
  timer_state_t state;
  timer_mode_t mode;
  uint16_t ch;
  uint16_t value;
} timer_t;
typedef struct
{
  timer_trigger_t trigger_state;
  uint16_t channel;
  uint16_t value;
} timer_result_t;
typedef enum{
  TIMER_OK,
  TIMER_INVALID_ID,
  TIMER_ERROR
} timer_result_return_t;
timer_result_return_t timer_init();
timer_result_return_t timer_get_result(uint8_t id, time_t current_time, timer_result_t * result);
timer_result_return_t timer_get_instant(uint8_t id, timer_t * timer);
timer_result_return_t timer_store_instant(uint8_t id, timer_t * timer);
#ifdef __cplusplus
}
#endif