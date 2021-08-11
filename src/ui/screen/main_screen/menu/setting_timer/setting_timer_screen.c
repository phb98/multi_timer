#include "setting_timer_screen.h"
#include "choose_timer_screen.h"
#include "set_timer_screen.h"
ui_setting_timer_screen_t (*setting_timer_screen[NUM_OF_UI_SETTING_TIMER_SCREEN]) (uint16_t *choosing_timer)=
{
  [UI_SETTING_TIMER_CHOOSE_TIMER_SCREEN] = ui_choose_timer_screen,
  [UI_SETTING_TIMER_SET_TIMER_SCREEN]    = ui_set_timer_screen
};
ui_menu_screen_t ui_setting_timer_screen()
{
  ui_menu_screen_t return_screen = UI_MENU_SETTING_TIMER_SCREEN;
  static ui_setting_timer_screen_t current_screen = UI_SETTING_TIMER_CHOOSE_TIMER_SCREEN;
  static uint16_t choose_timer;
  current_screen = setting_timer_screen[current_screen](&choose_timer);

  if(current_screen == UI_SETTING_TIMER_MENU_SCREEN)
  {
    return_screen  = UI_MENU_MENU_SCREEN;
    current_screen = UI_SETTING_TIMER_CHOOSE_TIMER_SCREEN;
    choose_timer   = 0;
  }
  return return_screen;
}