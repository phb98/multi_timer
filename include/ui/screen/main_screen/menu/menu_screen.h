#pragma once
#include "ui.h"
#include "main_screen.h"
typedef enum
{
  UI_MENU_MENU_SCREEN, // for turning back to menu
  UI_MENU_SETTING_TIME_SCREEN,
  UI_MENU_SETTING_TIMER_SCREEN,
  UI_MENU_MANUAL_OUTPUT_SCREEN,
  UI_MENU_SETTING_BACKLIGHT_SCREEN,
  UI_MENU_FACTORY_RESET_SCREEN,
  NUM_OF_MENU_ITEM
}ui_menu_screen_t;
ui_main_screen_t ui_menu_screen();