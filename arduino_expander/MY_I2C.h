#ifndef MY_I2C_H
#define MY_I2C_H

/* i2c init */
void MY_I2C_init(int sda = 21, int scl = 22, uint32_t freq = 400000);

/* read data from register */
bool MY_I2C_read_reg(uint8_t slave_addr, uint8_t reg_addr, uint8_t size, uint8_t* rx_buffer);

/* write data to register */
bool MY_I2C_write_reg(uint8_t slave_addr, uint8_t reg_addr, uint8_t data);

/* whether i2c slave addr can research */
uint8_t MY_slave_address_research(uint8_t slave_addr);

#endif //MY_I2C_H
