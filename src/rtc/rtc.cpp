#include "rtc.h"
#include "RTClib.h"
RTC_DS3231 rtc;

rtc_result_return_t rtc_init()
{
  /* rtc.begin() will try to re initialize our I2c bus, which is very bad habit of this library, all the previous config made by
     us will lose, we need to modify internal library
  */
  if(!rtc.begin()) return RTC_INIT_FAIL;
  if(rtc.lostPower()){ // the RTC is fresh 
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // set to the time this project is built
  }
  return RTC_OK;
}
rtc_result_return_t rtc_get_time(time_t * time)
{
  DateTime now = rtc.now();
  time->hour   = now.hour();
  time->minute = now.minute();
  time->second = now.second();
  time->year   = now.year();
  time->month  = now.month();
  time->day    = now.day();
  time->weekday= now.dayOfTheWeek();
  return RTC_OK;
}
rtc_result_return_t rtc_set_time(time_t * time)
{
  DateTime now(time->year, time->month, time->day,
               time->hour, time->minute, time->second);
  rtc.adjust(now);
  return RTC_OK;
}