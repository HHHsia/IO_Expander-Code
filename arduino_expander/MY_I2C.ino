#include <Wire.h>
#include "MY_I2C.h"

/* i2c init */
void MY_I2C_init(int sda, int scl, uint32_t freq)
{
  /* set i2c pin */
  Wire.setPins(SDA_pin, SCL_pin);

  /* set i2c frequency */
  Wire.setClock(I2C_freq);

  /* start i2c */
  Wire.begin();
}

/* read data from register */
bool MY_I2C_read_reg(uint8_t slave_addr, uint8_t reg_addr, uint8_t size, uint8_t* rx_buffer)
{
  /* rcv debug */
  int rcv_size = 0;

  /* send register with we want to read */
  Wire.beginTransmission(slave_addr); // open the device
  Wire.write(reg_addr); // specify the starting register address
  Wire.endTransmission(false);

  /* data read back with data size (can read continue data【ex: acc x,y,z】) */
  rcv_size = Wire.requestFrom(slave_addr, size); // specify the number of bytes to receive

  /* check data size send back is our request */
  if (rcv_size != size)
    return false;

  /* get data from i2c buffer */
  for (uint8_t i = 0; i < size; i++)
    rx_buffer[i] = Wire.read();

  return true;
}

/* write data to register */
bool MY_I2C_write_reg(uint8_t slave_addr, uint8_t reg_addr, uint8_t data)
{
  /* send debug */
  uint8_t buffer[21] = {};

  /* send register with we want to write, and data we want to write down together */
  Wire.beginTransmission(slave_addr); // open the device
  Wire.write(reg_addr); // write the register address
  Wire.write(data); // write the data
  Wire.endTransmission();

  /* wait for data write finished */
  delay(10);

  /* read back the register to check the data is same as we write */
  MY_I2C_read_reg(slave_addr, reg_addr, 1, buffer);
  if (buffer[0] == data)
    return true;
  else
    return false;
}

/* whether i2c slave addr can research */
uint8_t MY_slave_address_research(uint8_t slave_addr)
{
  uint8_t error;
  /* if data can transmission, then the slave addr is exist, or return error code */
  Wire.beginTransmission(slave_addr);
  error = Wire.endTransmission();
  return error;
}
