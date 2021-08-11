#include "menu_screen.h"
#include "setting_time_screen.h"
#include "setting_timer_screen.h"
static ui_menu_screen_t (*menu_screen[NUM_OF_MENU_ITEM]) () =
{
  [UI_MENU_SETTING_TIME_SCREEN]  = ui_setting_time_screen,
  [UI_MENU_SETTING_TIMER_SCREEN] = ui_setting_timer_screen
};

static const char * menu_title[NUM_OF_MENU_ITEM] = 
{
  "Setting Time     ",
  "Setting Timer    ",
  "Manual Output    ",
  "Backlight Timeout",
  "Reset All Setting"
};

ui_main_screen_t ui_menu_screen()
{
  ui_main_screen_t return_screen = UI_MAIN_MENU_SCREEN;
  /* Prepare variable for this screen */
  static uint16_t cursor = (uint16_t)UI_MENU_SETTING_TIME_SCREEN;
  const  uint8_t  max_cursor_pos = NUM_OF_MENU_ITEM - 1;
  const  uint8_t  min_cursor_pos = UI_MENU_SETTING_TIME_SCREEN;
  static uint8_t  in_sub_menu = 0; // are we inside submenu
  if(in_sub_menu)
  {
    if(menu_screen[cursor]() == UI_MENU_MENU_SCREEN ) // run to sub menu screen, check if sub menu screen want to turn back
    {
      in_sub_menu = 0;
    }
  }
  else
  {
    /* Process input */
    switch(ui_button_event)
    {
      case BUTTON_ENTER_SHORT_PRESS:
          in_sub_menu = 1; // go to sub menu
          break;
      case BUTTON_ENTER_LONG_PRESS:
          // Back to main screen
          return_screen = UI_MAIN_MAIN_SCREEN;
          // Reset cursor
          cursor = min_cursor_pos;
          break;
      case BUTTON_LEFT_SHORT_PRESS:
          change_1_step_then_check(&cursor, 0, max_cursor_pos, min_cursor_pos);
          break;
      case BUTTON_RIGHT_SHORT_PRESS:
          change_1_step_then_check(&cursor, 1, max_cursor_pos, min_cursor_pos);
          break;
      case BUTTON_NO_EVENT:
          break;
      default:
          break;
    }
    // Reset input
    ui_button_event = BUTTON_NO_EVENT;
    display_menu(menu_title, cursor - min_cursor_pos, max_cursor_pos-min_cursor_pos);
  }
  return return_screen;
}