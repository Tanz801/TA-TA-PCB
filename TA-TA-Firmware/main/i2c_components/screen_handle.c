#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "i2cdev.h"
#include "u8g2.h"
#include "esp_log.h"
#include "esp_check.h"

#include "config.h"
#include "screen_handle.h"
#include "face_elements.h"
#include "i2c_handle.h"


static const char *TAG = "Screen";
static const uint16_t I2C_ADDRESS = 0x3C;

static i2c_dev_t display_dev = {0};

static uint8_t u8x8_byte_i2c_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    static uint8_t buffer[132];
    static uint8_t buf_idx;

    switch (msg) {
    case U8X8_MSG_BYTE_INIT:

        break;

    case U8X8_MSG_BYTE_START_TRANSFER:
        buf_idx = 0;
        break;

    case U8X8_MSG_BYTE_SET_DC:
        break;

    case U8X8_MSG_BYTE_SEND:
        /* Add data bytes to buffer */
        for (size_t i = 0; i < arg_int; ++i) {
            buffer[buf_idx++] = *((uint8_t*)arg_ptr + i);
        }
        break;

    case U8X8_MSG_BYTE_END_TRANSFER:
        /* Transmit data using new I2C driver */
        if (i2c_dev_write(&display_dev, NULL, 0, buffer, buf_idx) != ESP_OK) {
            return 0;
        }
        break;

    default:
        return 0;
    }
    return 1;
}

static uint8_t u8x8_gpio_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    switch (msg) {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
        ESP_LOGI(TAG, "GPIO and delay initialization completed");
        break;

    case U8X8_MSG_DELAY_MILLI:
        /* Millisecond delay */
        vTaskDelay(pdMS_TO_TICKS(arg_int));
        break;

    case U8X8_MSG_DELAY_10MICRO:
        /* 10 microsecond delay */
        esp_rom_delay_us(arg_int * 10);
        break;

    case U8X8_MSG_DELAY_100NANO:
        /* 100 nanosecond delay - use minimal delay on ESP32 */
        __asm__ __volatile__("nop");
        break;

    case U8X8_MSG_DELAY_I2C:
        /* I2C timing delay: 5us for 100KHz, 1.25us for 400KHz */
        esp_rom_delay_us(5 / arg_int);
        break;

    case U8X8_MSG_GPIO_RESET:
        /* GPIO reset control (optional for most display controllers) */
        break;

    default:
        /* Other GPIO messages not handled */
        return 0;
    }
    return 1;
}

u8g2_t u8g2;

int left_eye_x = 26;
int left_eye_y = 29;
int right_eye_x = 128 - 26;
int right_eye_y = 29;
int mouth_x = 64;
int mouth_y = 45;

void screen_setup() {
    display_dev.port = I2C_NUM_0;
    display_dev.addr = I2C_ADDRESS;
    display_dev.cfg.sda_io_num = I2C_SDA_PIN;
    display_dev.cfg.scl_io_num = I2C_SCL_PIN;
    display_dev.cfg.master.clk_speed = I2C_CLOCK_SPEED;

    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0,
        u8x8_byte_i2c_cb,
        u8x8_gpio_delay_cb
    );

    ESP_LOGI(TAG, "initalizing display");

    u8x8_SetI2CAddress(&u8g2.u8x8, I2C_ADDRESS << 1);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    ESP_LOGI(TAG, "display initalized");
}


void screen_update() {
    u8g2_ClearBuffer(&u8g2);
    draw_eye(&u8g2, left_eye_x, left_eye_y, 1);
    draw_eye(&u8g2, right_eye_x, right_eye_y, 1);
    draw_mouth(&u8g2, mouth_x, mouth_y, 0);
    u8g2_SendBuffer(&u8g2);
}
