#pragma once
#include "ui.h"
typedef enum
{
  UI_MAIN_MAIN_SCREEN,
  UI_MAIN_MENU_SCREEN,
  UI_MAIN_CURRENT_TIME_SCREEN,
  NUM_OF_MAIN_SCREEN
}ui_main_screen_t;
ui_screen_t ui_main_screen();