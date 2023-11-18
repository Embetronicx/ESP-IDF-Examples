#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "ETX_BLINKY";

#define BLINK_GPIO_1 2
#define BLINK_GPIO_2 25

void app_main(void)
{
    /* Reset the pin */
    gpio_reset_pin(BLINK_GPIO_1);
    gpio_reset_pin(BLINK_GPIO_2);

    /* Set the GPIOs to Output mode */
    gpio_set_direction(BLINK_GPIO_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO_2, GPIO_MODE_OUTPUT);

    while (1) 
    {
        gpio_set_level(BLINK_GPIO_1, 1);
        gpio_set_level(BLINK_GPIO_2, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "Turning the LED %s!","ON");

        gpio_set_level(BLINK_GPIO_1, 0);
        gpio_set_level(BLINK_GPIO_2, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "Turning the LED %s!","OFF");
    }
}