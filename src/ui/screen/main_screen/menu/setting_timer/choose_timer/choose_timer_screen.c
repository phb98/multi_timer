#include "choose_timer_screen.h"
#include "config.h"
ui_setting_timer_screen_t ui_choose_timer_screen(uint16_t * choosing_timer)
{
  ui_setting_timer_screen_t return_screen = UI_SETTING_TIMER_CHOOSE_TIMER_SCREEN;
  // Process input 
  switch(ui_button_event)
  {
    case BUTTON_ENTER_SHORT_PRESS:
        return_screen = UI_SETTING_TIMER_SET_TIMER_SCREEN;
        break;
    case BUTTON_ENTER_LONG_PRESS:
        return_screen = UI_SETTING_TIMER_MENU_SCREEN;
        break;
    case BUTTON_LEFT_SHORT_PRESS:
        change_1_step_then_check(choosing_timer, 0, CONFIG_NUM_OF_TIMER-1, 0);
        break;
    case BUTTON_RIGHT_SHORT_PRESS:
        change_1_step_then_check(choosing_timer, 1, CONFIG_NUM_OF_TIMER-1, 0);
        break;
    case BUTTON_NO_EVENT:
        break;
    default:
        break;
  }
  // Reset input
  ui_button_event = BUTTON_NO_EVENT;
  display_setting_timer_choose(*choosing_timer, CONFIG_NUM_OF_TIMER-1);
  return return_screen;
}