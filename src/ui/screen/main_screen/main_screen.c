#include "main_screen.h"
#include "menu_screen.h"
#include "current_time_screen.h"
ui_main_screen_t (*main_screen[NUM_OF_MAIN_SCREEN]) () = 
{
  [UI_MAIN_MENU_SCREEN] = ui_menu_screen,
  [UI_MAIN_CURRENT_TIME_SCREEN] = ui_current_time_screen
};
ui_screen_t ui_main_screen()
{
  ui_screen_t return_screen = UI_MAIN_SCREEN;
  static uint16_t cursor = UI_MAIN_CURRENT_TIME_SCREEN;
  static uint8_t in_menu = 0;
  const  uint8_t min_cursor_pos = UI_MAIN_CURRENT_TIME_SCREEN;
  const  uint8_t max_cursor_pos = NUM_OF_MAIN_SCREEN - 1;
  if(in_menu)
  {
    if((main_screen[UI_MAIN_MENU_SCREEN]) () == UI_MAIN_MAIN_SCREEN)
    {
      in_menu = 0;
    }
  }
  else
  {
    /* Process input */
    switch(ui_button_event)
    {
      case BUTTON_ENTER_SHORT_PRESS:
          in_menu = 1;
          break;
      case BUTTON_ENTER_LONG_PRESS:
          break;
      case BUTTON_LEFT_SHORT_PRESS:
          change_1_step_then_check(&cursor, 1, max_cursor_pos, min_cursor_pos);
          break;
      case BUTTON_RIGHT_SHORT_PRESS:
         change_1_step_then_check(&cursor, 0, max_cursor_pos, min_cursor_pos);
          break;
      case BUTTON_NO_EVENT:
          break;
      default:
          break;
    }
    // Reset input
    ui_button_event = BUTTON_NO_EVENT;
    main_screen[cursor]();
  }
  return return_screen;
}
