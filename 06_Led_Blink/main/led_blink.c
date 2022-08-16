#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED 14

TaskHandle_t led_task_handle;

void led_blink(void *data)
{
    while (1)
    {
        gpio_set_level(LED, 1);
        printf("LED is ON\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED, 0);
        printf("LED is OFF\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    BaseType_t res;
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    res = xTaskCreate(led_blink, "LED Blink", 2048, NULL, 3, &led_task_handle);
    if (res == pdPASS)
    {
        printf("Task Created Successfully\n");
    }
}
