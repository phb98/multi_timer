#pragma once
#ifdef __cplusplus
extern "C"{
#endif
#include "stdint.h"
#include "timer.h"
void display_init();
void display_boot_screen();
void display_current_time(time_t cur_time);
void display_menu(const char * title[], uint8_t cursor, uint8_t max_cursor_pos);
#ifdef __cplusplus
}
#endif