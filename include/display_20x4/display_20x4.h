#pragma once
#ifdef __cplusplus
extern "C"{
#endif
#include "stdint.h"
#include "timer.h"
void display_init();
void display_boot_screen();
void display_current_time(time_t cur_time);
void display_menu(const char * title[], uint16_t cursor, uint8_t max_cursor_pos);
void display_setting_time(uint16_t * setting, uint8_t cursor);
void display_setting_timer_choose(uint16_t timer_id, , uint16_t max_timer_id);
#ifdef __cplusplus
}
#endif