#include "MY_I2C.h"

/* i2c setting */
#define SDA_pin 21
#define SCL_pin 22
#define I2C_freq 400000

/* expander init */
#define expander_slave_addr     (uint8_t)0x20
#define who_am_i                (uint8_t)0x2E

void expander_20_40_60(void)
{
  uint8_t temp;
  if (MY_I2C_read_reg(expander_slave_addr, who_am_i, 1, &temp))
    printf("it is 0x%02x, CY8C95%02xA\n", temp, temp);
  else
    printf("read fail\n");

  return;
}

void setup()
{
  /* uart init */
  Serial.begin(115200);

  /* i2c init */
  MY_I2C_init(SDA_pin, SCL_pin, I2C_freq);

  /* whether expander_slave_addr can found */
  /*
  for (uint8_t i = 0x00; i < 0x7f; i++)
  {
    uint8_t error = MY_slave_address_research(i);
    if (error == 0)
      Serial.printf("slave addr 0x%02X can found\n", i);
  }
*/
  /* check expander type */
  expander_20_40_60();
}

void loop() {



}
