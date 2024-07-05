#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char *TAG = "i2c-simple-example";

#define I2C_MASTER_SCL_IO           CONFIG_I2C_MASTER_SCL      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           CONFIG_I2C_MASTER_SDA      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          25000                      /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       100000

#define IO_expander_slave_address     0x20         /*!< Slave address of the MPU9250 sensor 20*/
#define IO_expander_chip_ID           0x2E         /*!< Register addresses of the "who am I" register 2E*/




static esp_err_t IO_expander_read_transcation(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(I2C_MASTER_NUM, IO_expander_slave_address, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}


static esp_err_t IO_expander_write_transcation(uint8_t reg_addr, uint8_t data)
{
    int ret;
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(I2C_MASTER_NUM, IO_expander_slave_address, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);

    return ret;
}

/**
 * i2c master initialization
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}


void app_main(void)
{


    uint8_t data[32];
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    /*uint8_t temp_addr = 0x00;
    for(temp_addr = 0x00 ; temp_addr < 0xFF ; temp_addr++){
        IO_expander_read_transcation(temp_addr,data,1);
        ESP_LOGI(TAG, "current temp_addr = %d", temp_addr);
        ESP_LOGI(TAG, "WHO_AM_I = %X", data[0]);
    }*/


    /* Read the MPU9250 WHO_AM_I register, on power up the register should have the value 0x71 */
    //ESP_ERROR_CHECK(IO_expander_read_transcation(IO_expander_chip_ID, data, 1));
    IO_expander_read_transcation(IO_expander_chip_ID, data, 1);
    ESP_LOGI(TAG, "WHO_AM_I = %X", data[0]);
    vTaskDelay(10000);


    /* Demonstrate writing by reseting the MPU9250 */
    //ESP_ERROR_CHECK(IO_expander_write_transcation(MPU9250_PWR_MGMT_1_REG_ADDR, 1 << MPU9250_RESET_BIT));

    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(TAG, "I2C unitialized successfully");

    vTaskDelay(1000);
}
