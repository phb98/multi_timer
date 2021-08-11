#include "ui.h"
#include "stdint.h"
#include "rtc.h"
#include "timer.h"
#include "config.h"
#include "button_lib.h"
#include "string.h"
#include "avr/io.h"
/* include main screens */
#include "main_screen.h"
#include "menu_screen.h"
/*
    The logic in each UI screen is simple
    Each screen first will process the user input first.
    After that it will call proper display function
    depends on user input and current UI screen, it will return the next screen it wants the UI to display(which can be itself)
*/

ui_screen_t ui_main_screen();
ui_screen_t ui_bootup_screen();
ui_screen_t (*ui_screen[NUM_OF_UI_SCREEN]) () = {
    [UI_MAIN_SCREEN]            = ui_main_screen,
    [UI_BOOTUP_SCREEN]          = ui_bootup_screen
};
/* button callback here */
void enter_single_press_cb();
void enter_long_press_cb();
void left_single_press_cb();
void right_single_press_cb();
int  button_enter_custom_read(uint8_t dummy);
static button_result_t * enter_button_result;
static button_result_t * right_button_result;
static button_result_t * left_button_result;

/*     helper function      */
void change_1_step_then_check(uint16_t * var,uint8_t is_increase, uint32_t high_bound, uint32_t low_bound); 

/*                                      PUBLIC FUNCTIONS                                        */
void ui_init()
{
  ui_bootup_screen();
  ui_button_event = BUTTON_NO_EVENT;
  /* Register button */
  button_register_t button;
  memset(&button, 0x0, sizeof(button_register_t));
  button.active_logic = CONFIG_BUTTON_ACTIVE_LOGIC;
  button.pin          = CONFIG_BUTTON_ENTER_PIN;
  button.callback[0]  = enter_single_press_cb;
  button.trigger_result[0].click_count = 1;
  button.trigger_result[0].is_hold     = 0;
  button.callback[1]  = enter_long_press_cb;
  button.trigger_result[1].click_count = 0;
  button.trigger_result[1].is_hold     = 1;
  button.callback_length               = 2;
  button.read_fp = button_enter_custom_read; 
  button_register(button, &enter_button_result); // enter 
  button.read_fp = NULL;
  button.pin          = CONFIG_BUTTON_LEFT_PIN;
  button.active_logic = CONFIG_BUTTON_ACTIVE_LOGIC;
  button.callback[0]  = left_single_press_cb;
  button.trigger_result[0].click_count = 1;
  button.trigger_result[0].is_hold     = 0;
  button.callback_length = 1;
  button_register(button, &left_button_result); // left
  button.pin          = CONFIG_BUTTON_RIGHT_PIN;
  button.active_logic = CONFIG_BUTTON_ACTIVE_LOGIC;
  button.callback[0]  = right_single_press_cb;
  button.trigger_result[0].click_count = 1;
  button.trigger_result[0].is_hold     = 0;
  button.callback_length = 1;
  button_register(button, &right_button_result); // right
}
void ui_update()
{
  static ui_screen_t current_screen = UI_MAIN_SCREEN;
  current_screen = ui_screen[current_screen]();
  return;
}
/*                                      PRIVATE FUNCTIONS                                       */


/* button callback here */
void enter_single_press_cb()
{
  ui_button_event = BUTTON_ENTER_SHORT_PRESS;
}
void enter_long_press_cb()
{
  ui_button_event = BUTTON_ENTER_LONG_PRESS;
}
void left_single_press_cb()
{
  ui_button_event = BUTTON_LEFT_SHORT_PRESS;
}
void right_single_press_cb()
{
  ui_button_event = BUTTON_RIGHT_SHORT_PRESS;
}
int  button_enter_custom_read(uint8_t dummy)
{
    return ((PINB >> 1) & 0x1);
}
/* helper function to increase or decrease variable 1 step and rollover if overflow */
void change_1_step_then_check(uint16_t * var,uint8_t is_increase, uint32_t high_bound, uint32_t low_bound){
    if(is_increase){
        if((*var) >= high_bound) (*var) = low_bound;
        else (*var)++;
        return;
    }
    else{
        if((*var) <= low_bound) (*var) = high_bound;
        else (*var)--;
    }
}
