#include "set_timer_screen.h"

ui_setting_timer_screen_t ui_set_timer_screen(uint16_t * choose_timer)
{
  ui_setting_timer_screen_t return_screen = UI_SETTING_TIMER_SET_TIMER_SCREEN;
  return_screen = UI_SETTING_TIMER_MENU_SCREEN;
  return return_screen;
}