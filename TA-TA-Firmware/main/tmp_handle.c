#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#include "tmp_handle.h"
#include "config.h"

adc_oneshot_unit_handle_t adc1_handle;
adc_oneshot_unit_init_cfg_t init_config = {
    .unit_id = ADC_UNIT_1
};


void tmp_main(void* args) {

    vTaskDelay(pdMS_TO_TICKS(3000));
}