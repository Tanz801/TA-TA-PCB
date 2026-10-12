#include "imu_handle.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "i2cdev.h"
#include "esp_log.h"
#include "esp_check.h"
#include "mpu6050.h"
#include <math.h>

#include "config.h"
#include "i2c_handle.h"
#include "imu_handle.h"

static const char *TAG = "MPU6050";

static mpu6050_dev_t mpu_dev = {0};

mpu6050_acceleration_t raw_accel;
mpu6050_rotation_t raw_gyro;

void imu_setup() {

    esp_err_t err = mpu6050_init_desc(
        &mpu_dev,
        MPU6050_I2C_ADDRESS_LOW,
        I2C_NUM_0,
        I2C_SDA_PIN,
        I2C_SCL_PIN
    );

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Initialization failed for MPU6050: %s", esp_err_to_name(err));
        return;
    }

    mpu_dev.i2c_dev.cfg.master.clk_speed = I2C_CLOCK_SPEED;

    err = mpu6050_init(&mpu_dev);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Initialization failed for MPU6050: %s", esp_err_to_name(err));
        return;
    } else {
        ESP_LOGI(TAG, "IMU initialized successfully");
    }

    mpu6050_set_full_scale_accel_range(&mpu_dev, MPU6050_ACCEL_RANGE_4);
    mpu6050_set_full_scale_gyro_range(&mpu_dev, MPU6050_GYRO_RANGE_500);
}

void imu_update() {
    if (mpu6050_get_motion(&mpu_dev, &raw_accel, &raw_gyro) == ESP_OK) {
        float accel_g_x = raw_accel.x / 8192.0f;
        float accel_g_y = raw_accel.y / 8192.0f;
        float accel_g_z = raw_accel.z / 8192.0f;
        float total_g = sqrtf((accel_g_x * accel_g_x) + (accel_g_y * accel_g_y) + (accel_g_z * accel_g_z));

        //float dps_x = raw_gyro.x / 65.5f;
        //float dps_y = raw_gyro.y / 65.5f;
        //float dps_z = raw_gyro.z / 65.5f;

    } else {
        ESP_LOGE(TAG, "failed to collect IMU data");
    }
}