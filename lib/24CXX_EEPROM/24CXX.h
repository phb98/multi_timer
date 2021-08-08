#pragma once
#include "config.h"
#ifdef __cplusplus
extern "C"{
#endif
#define EEPROM_ADDR (CONFIG_EEPROM_ADDR)
#define EEPROM_SIZE (CONFIG_EEPROM_SIZE) // bytes
#define EEPROM_I2C_FAST_SPEED CONFIG_EEPROM_FAST_MODE
#define EEPROM_PAGE_SIZE 32
typedef enum{
  EEPROM_OK = 0,
  EEPROM_ADDR_INVALID,
  EEPROM_ERROR_INIT,
  EEPROM_ERROR_GENERAL
} eeprom_result_return_t;

/* public functions */
eeprom_result_return_t EEPROM_24CXX_init();
eeprom_result_return_t EEPROM_24CXX_write_single(uint32_t addr, uint8_t data);
eeprom_result_return_t EEPROM_24CXX_write_multi(uint32_t addr, uint8_t * data, uint32_t size);
eeprom_result_return_t EEPROM_24CXX_read_single(uint32_t addr, uint8_t * data);
eeprom_result_return_t EEPROM_24CXX_read_multi(uint32_t addr, uint8_t * data, uint32_t size);
#ifdef __cplusplus
}
#endif