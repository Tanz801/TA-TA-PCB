#include "driver/gpio.h"
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "queues.h"
#include "iot_button.h"
#include "button_gpio.h"

#include "power_handle.h"


uint64_t pin_mask = 1ULL << BUTTON_ON_OFF;

void button_setup() {
    button_config_t button_config = {
        .long_press_time = 2000,
        .short_press_time = 50
    };


    gpio_config_t button_input_config = {
        .pin_bit_mask = pin_mask,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    gpio_config(&button_input_config);
}


void power_handle_main(void* args) {
    button_setup();

    for (;;) {
    

        if (false) {
            esp_sleep_enable_gpio_wakeup_on_hp_periph_powerdown(pin_mask, ESP_SLEEP_WAKEUP_GPIO);
            esp_deep_sleep_start();
        }
    }
}