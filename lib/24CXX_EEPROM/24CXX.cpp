#include "Wire.h"
#include "24CXX.h"
#include "Arduino.h"
/*    Private functions       */
uint8_t is_ready();

/*      Public Functions       */
eeprom_result_return_t EEPROM_24CXX_init()
{
  Wire.begin();
  //Attempt to communicate to eeprom
  #if (EEPROM_I2C_FAST_SPEED)
  Wire.setClock(400000L); // Set clock to 400khz
  #endif
  Wire.beginTransmission(EEPROM_ADDR);
  if(Wire.endTransmission(EEPROM_ADDR) != 0) return EEPROM_ERROR_INIT;
  else return EEPROM_OK;
}

eeprom_result_return_t EEPROM_24CXX_write_single(uint32_t addr, uint8_t data)
{
  if(addr >= EEPROM_SIZE) return EEPROM_ADDR_INVALID;
  while(!is_ready());// wait for eeprom ready
  Wire.beginTransmission(EEPROM_ADDR);
  uint8_t temp;
  // Write 2 bytes address first
  temp = (addr >> 8) & 0xff;
  Wire.write(temp);
  temp = addr & 0xff;
  Wire.write(temp);
  // Write data
  Wire.write(data);
  Wire.endTransmission();
  return EEPROM_OK;
}

eeprom_result_return_t EEPROM_24CXX_write_multi(uint32_t addr, uint8_t * data, uint32_t size)
{
  if(addr >= EEPROM_SIZE || (addr + size) >= EEPROM_SIZE) return EEPROM_ADDR_INVALID;
  while(!is_ready());// wait for eeprom ready
  uint8_t temp;
  // we used 2 byte for address of 32 bytes buffer of i2c library
  uint8_t byte_count = 2;
  while(size)
  {
    // Writting address
    Wire.beginTransmission(EEPROM_ADDR);
    temp = (addr >> 8) & 0xff;
    Wire.write(temp);
    temp = addr & 0xff;
    Wire.write(temp);
    // Write data
    while(byte_count < 32  && size > 0) 
    {
      Wire.write(*data++);
      addr++;
      byte_count++;
      size--;
      // TODO: Can we use bit manipulation instead of modulo ?
      if((addr % EEPROM_PAGE_SIZE) == 0) break; // check if addr reach a new page, if yes then finish data moving in this page
    }
    Wire.endTransmission(true);
    byte_count = 2;
    while(!is_ready())
    {
      //delayMicroseconds(500);
    } // polling for ACK
  }
  return EEPROM_OK;
}

eeprom_result_return_t EEPROM_24CXX_read_single(uint32_t addr, uint8_t * data)
{
  if(addr >= EEPROM_SIZE) return EEPROM_ADDR_INVALID;
  while(!is_ready());// wait for eeprom ready
  Wire.beginTransmission(EEPROM_ADDR);
  // Write 2 bytes address first
  uint8_t temp;
  temp = (addr >> 8) & 0xff;
  Wire.write(temp);
  temp = addr & 0xff;
  Wire.write(temp);
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ADDR, 1);
  //if(Wire.available() < 1) return EEPROM_ERROR_GENERAL;
  *data = Wire.read();
  return EEPROM_OK;
}

eeprom_result_return_t EEPROM_24CXX_read_multi(uint32_t addr, uint8_t * data, uint32_t size)
{
  if(addr >= EEPROM_SIZE || (addr + size) >= EEPROM_SIZE) return EEPROM_ADDR_INVALID;
  while(!is_ready());// wait for eeprom ready
  Wire.beginTransmission(EEPROM_ADDR);
  // Write 2 bytes address first
  uint8_t temp;
  while(size)
  {
    Wire.beginTransmission(EEPROM_ADDR);
    // write address
    temp = (addr >> 8) & 0xff;
    Wire.write(temp);
    temp = addr & 0xff;
    Wire.write(temp);
    Wire.endTransmission();
    // internal buffer of I2C library has default size of 32 bytes, so maximum we can read in 1 transmission is 32
    if(size >=32)
    {
      Wire.requestFrom(EEPROM_ADDR, 32, true);
      if(Wire.available() != 32) return EEPROM_ERROR_GENERAL;
      while(Wire.available())
      {
        *data = Wire.read();
        data++;
      }
      size -=32;
      addr +=32;
    }
    else
    {
      Wire.requestFrom(EEPROM_ADDR, size, true);
      if((uint32_t)Wire.available() != size) return EEPROM_ERROR_GENERAL;
      while(Wire.available())
      {
        *data = Wire.read();
        data++;
      }
      size = 0;
      addr += size;   
    }
  }
  return EEPROM_OK;
}

/*    Private functions       */

uint8_t is_ready()
{
  Wire.beginTransmission(EEPROM_ADDR);
  if(Wire.endTransmission() != 0) return 0;
  else return 1;
}