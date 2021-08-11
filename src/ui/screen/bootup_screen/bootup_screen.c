#include "bootup_screen.h"
ui_screen_t ui_bootup_screen(){
  display_boot_screen();
  // boot screen does not handle any input
  return UI_MAIN_SCREEN;
}