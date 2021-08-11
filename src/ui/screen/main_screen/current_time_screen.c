#include "current_time_screen.h"
#include "timer.h"
#include "rtc.h"
ui_main_screen_t ui_current_time_screen()
{
  ui_main_screen_t return_screen = UI_MAIN_MAIN_SCREEN;
  time_t time;
  rtc_get_time(&time);
  display_current_time(time);
  return return_screen;
}