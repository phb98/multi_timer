#include "rtc.h"
#include "timer.h"
#include "setting_time_screen.h"
ui_menu_screen_t ui_setting_time_screen()
{
  ui_menu_screen_t return_screen = UI_MENU_SETTING_TIME_SCREEN;
  // prepare variable
  static uint16_t setting[7];
  static uint8_t  is_screen_init = 0; // is this first time we come to this screen ?
  time_t time;
  static uint16_t cursor;
  const  uint8_t max_cursor_pos = 5;
  static uint8_t is_choosing = 0;
  const  uint8_t upper_bound[7] = {23,59,59,31,12,99,6};
  static uint8_t time_modified = 0;
  if(!is_screen_init)
  {
    //get data from RTC and store them to setting array
    rtc_get_time(&time);
    setting[0] = time.hour;
    setting[1] = time.minute;
    setting[2] = time.second;
    setting[3] = time.day;
    setting[4] = time.month;
    setting[5] = time.year;
    setting[6] = time.weekday;
    is_choosing = 0;
    cursor = 0;
    time_modified = 0;
    is_screen_init = 1;
  }
    // Process input 
  switch(ui_button_event)
  {
    case BUTTON_ENTER_SHORT_PRESS:
        is_choosing = !is_choosing;
        break;
    case BUTTON_ENTER_LONG_PRESS:
        time.hour   = setting[0];
        time.minute = setting[1];
        time.second = setting[2];
        time.day    = setting[3];
        time.month  = setting[4];
        time.year   = setting[5];
        time.weekday= setting[6];
        if(time_modified) rtc_set_time(&time); // so that if we accident go into this screen, we wont change RTC time
        is_screen_init = 0;
        //back to menu screen
        return_screen = UI_MENU_MENU_SCREEN;
        break;
    case BUTTON_LEFT_SHORT_PRESS:
        time_modified = 1;
        if(is_choosing)
        {
        change_1_step_then_check(&setting[cursor],0,upper_bound[cursor] + (cursor == 5)*2000,0 + (cursor == 5)*2000); // upper bound of year need offset 2000
        }
        else change_1_step_then_check(&cursor, 0, max_cursor_pos, 0);
        break;
    case BUTTON_RIGHT_SHORT_PRESS:
        time_modified = 1;
        if(is_choosing)
        {
        change_1_step_then_check(&setting[cursor], 1, upper_bound[cursor] + (cursor == 5)*2000, 0 + (cursor == 5)*2000); // upper bound of year need offset 2000
        }
        else change_1_step_then_check(&cursor, 1, max_cursor_pos, 0);
        break;
    case BUTTON_NO_EVENT:
        break;
    default:
        break;
  }
  // Reset input
  ui_button_event = BUTTON_NO_EVENT;
  display_setting_time(setting, cursor);
  return return_screen;
}