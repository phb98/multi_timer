#pragma once
#include "timer.h"
#include "assert.h"
#define BUILD_BUG_ON(condition) ((size_t)sizeof(char[1 - 2*!!(condition)])) // from SO so we can evaluate sizeof in pre compile time
#define CONFIG_MAJOR_VER 0
#define CONFIG_MINOR_VER 0
#define I2C_FAST_SPEED   1
#define CONFIG_BOOT_TIME 2000
/* EEPROM config */
#define CONFIG_EEPROM_SIZE (4096)
#define CONFIG_EEPROM_ADDR (0x57)

/* Timer Config */
#define CONFIG_NUM_OF_TIMER (5)
#define CONFIG_SIZE_OF_SINGLE_TIMER (sizeof(timer_t))
#define CONFIG_TIMER_EEPROM_START_ADDR 0
#define CONFIG_SIZE_OF_TIMER (CONFIG_NUM_OF_TIMER*CONFIG_SIZE_OF_SINGLE_TIMER)
static_assert(sizeof(timer_t)*CONFIG_NUM_OF_TIMER <= CONFIG_EEPROM_SIZE, "Error in config: No space left");
/* Output config */
#define CONFIG_MAX_OUTPUT_VALUE 0xff
#define CONFIG_NUM_OF_OUTPUT    5
/* Button config */
#define CONFIG_BUTTON_ACTIVE_LOGIC 0
#define CONFIG_BUTTON_ENTER_PIN    9
#define CONFIG_BUTTON_LEFT_PIN     5
#define CONFIG_BUTTON_RIGHT_PIN    6