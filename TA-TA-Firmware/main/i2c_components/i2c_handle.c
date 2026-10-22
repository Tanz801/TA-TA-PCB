#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "esp_check.h"
#include "u8g2.h"
#include "i2cdev.h"

#include "config.h"
#include "i2c_handle.h"
#include "screen_handle.h"
#include "imu_handle.h"

static const char *TAG = "MPU6050";

const uint32_t I2C_CLOCK_SPEED = 400000;

void i2c_setup(void* args) {
    i2cdev_init();

    imu_setup();

    screen_setup();

    ESP_LOGI(TAG, "All I2C systems initalized successfully");

    for (;;) {
        screen_update();
        imu_update();

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
