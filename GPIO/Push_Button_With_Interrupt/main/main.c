#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include <inttypes.h>

#define BLINK_GPIO_1 2
#define BLINK_GPIO_2 25

bool gpio_value = false;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    /* 
        TODO - Implement the debouncing algorithm 
        to eliminate the Spurious interrupt trigger.
    */
   
    /* Disable the Interrupt */
    gpio_intr_disable(BLINK_GPIO_2);
    gpio_isr_handler_remove(BLINK_GPIO_2);

    /* Button is pressed. Toggle the LED */
    gpio_set_level(BLINK_GPIO_1, gpio_value);
    gpio_value = !gpio_value;

    /* Re-Enable the Interrupt */
    gpio_isr_handler_add(BLINK_GPIO_2, gpio_isr_handler, NULL);
    gpio_intr_enable(BLINK_GPIO_2);
}

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

    /* Disable pulldown for Input Pin */
    gpio_pulldown_dis(BLINK_GPIO_2);

    /* Configure Raising Edge detection Interrupt for Input Pin */
    gpio_set_intr_type(BLINK_GPIO_2, GPIO_INTR_POSEDGE);

    /* install gpio isr service to default values */
    gpio_install_isr_service(0);

    /* Attach the ISR to the GPIO interrupt */
    gpio_isr_handler_add(BLINK_GPIO_2, gpio_isr_handler, NULL);

    /* Enable the Interrupt */
    gpio_intr_enable(BLINK_GPIO_2);
    
    while (1) 
    {
        /* infinite loop */
    }
}