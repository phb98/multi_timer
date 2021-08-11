#pragma once
#include "menu_screen.h"
typedef enum {
  UI_SETTING_TIMER_MENU_SCREEN,
  UI_SETTING_TIMER_CHOOSE_TIMER_SCREEN,
  UI_SETTING_TIMER_SET_TIMER_SCREEN,
  NUM_OF_UI_SETTING_TIMER_SCREEN
} ui_setting_timer_screen_t;
ui_menu_screen_t ui_setting_timer_screen();