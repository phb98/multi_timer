#pragma once
#ifdef __cplusplus
extern "C"{
#endif
#include "timer.h" // use time_t

typedef enum{
  RTC_OK,
  RTC_INIT_FAIL,
  RTC_ERROR
} rtc_result_return_t;
rtc_result_return_t rtc_init();
rtc_result_return_t rtc_get_time(time_t * time);
rtc_result_return_t rtc_set_time(time_t * time);
#ifdef __cplusplus
}
#endif