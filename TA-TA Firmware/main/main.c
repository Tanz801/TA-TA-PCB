#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "esp_check.h"
#include "config.h"
#include "queues.h"

#include "power_handle.h"
#include "tmp_handle.h"
#include "buzzer_handle.h"
#include "i2c_handle.h"

const gpio_num_t I2C_SDA_PIN = 6;
const gpio_num_t I2C_SCL_PIN = 7;

const gpio_num_t TMP_PIN = 4;

QueueHandle_t gpio_evt_queue = NULL;

void app_main(void) {
    gpio_evt_queue = xQueueCreate(10, sizeof(uint8_t));
    //xTaskCreate(power_handle_main, "power_handle_main", 1024, NULL, 6, NULL);
    xTaskCreate(i2c_setup, "i2c_setup", 4096, NULL, 6, NULL);
    //xTaskCreate(tmp_main, "tmp_main", 1024, NULL, 5, NULL);
    xTaskCreate(buzzer_main, "buzzer_main", 1024, NULL, 5, NULL);
}
