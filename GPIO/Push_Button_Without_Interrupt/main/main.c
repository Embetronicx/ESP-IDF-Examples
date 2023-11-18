#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "ETX_PUSH_BUTTON";

#define BLINK_GPIO_1 2
#define BLINK_GPIO_2 25

void app_main(void)
{
    /* Reset the pin */
    gpio_reset_pin(BLINK_GPIO_1);
    gpio_reset_pin(BLINK_GPIO_2);

    /* Set the GPIOs to Output mode */
    gpio_set_direction(BLINK_GPIO_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO_2, GPIO_MODE_INPUT);

    /* Enable Pullup for Input Pin */
    gpio_pullup_en(BLINK_GPIO_2);
    
    while (1) 
    {
        if( gpio_get_level(BLINK_GPIO_2) == 0 )
        {
            /* Button is pressed. Turn on the LED */
            gpio_set_level(BLINK_GPIO_1, 1);
            ESP_LOGI(TAG, "Turning the LED %s!","ON");
        }
        else
        {
            /* Button is released. Turn off the LED */
            gpio_set_level(BLINK_GPIO_1, 0);
        }
    }
}