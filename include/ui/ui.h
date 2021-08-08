#pragma once
#ifdef __cplusplus
extern "C"{
#endif
#define UI_MAX_MAIN_SCREEN  1
#define UI_MAX_MENU_ITEM    5
typedef enum{
    UI_MAIN_SCREEN,
    UI_MENU_SCREEN,
    UI_SETTING_TIME_SCREEN,
    UI_SETTING_TIMER_SCREEN,
    UI_BOOTUP_SCREEN,
    NUM_OF_UI_SCREEN
} ui_screen_t;
typedef enum{
    UI_SETTING_TIMER_CHOOSE_SCREEN,
    UI_SETTING_TIMER_SETTING_SCREEN,
    UI_SETTING_TIMER_BACK_TO_MENU,
    NUM_OF_UI_SETTING_TIMER_SCREEN
} ui_setting_timer_screen_t;
void ui_init();
void ui_update();
#ifdef __cplusplus
}
#endif
/*template for checking input switch case

  // Process input 
  switch(ui_button_event)
  {
    case BUTTON_ENTER_SHORT_PRESS:
        break;
    case BUTTON_ENTER_LONG_PRESS:
        break;
    case BUTTON_LEFT_SHORT_PRESS:
        break;
    case BUTTON_RIGHT_SHORT_PRESS:
        break;
    case BUTTON_NO_EVENT:
        break;
    default:
        break;
  }
  // Reset input
  ui_button_event = BUTTON_NO_EVENT;
*/