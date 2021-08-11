#pragma once
#ifdef __cplusplus
extern "C"{
#endif
#include "config.h"
#if CONFIG_DISPLAY_20X4
#include "display_20x4.h"
#endif
#define UI_MAX_MAIN_SCREEN  1
typedef enum{
    UI_MAIN_SCREEN,
    UI_MENU_SCREEN,
    UI_BOOTUP_SCREEN,
    NUM_OF_UI_SCREEN
} ui_screen_t;
enum {
  BUTTON_NO_EVENT = 0,
  BUTTON_LEFT_SHORT_PRESS,
  BUTTON_RIGHT_SHORT_PRESS,
  BUTTON_ENTER_SHORT_PRESS,
  BUTTON_ENTER_LONG_PRESS, // a.k.a back
} ui_button_event;
void ui_init();
void ui_update();

/*        PRIVATE PROTOTYPE         */
void change_1_step_then_check(uint16_t * var,uint8_t is_increase, uint32_t high_bound, uint32_t low_bound);
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