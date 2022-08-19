#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

TaskHandle_t task1_handle, task2_handle, task3_handle, task4_handle;
EventGroupHandle_t event_flag;

void task_1(void *data)
{
    printf("Task 1\n");
    while (1)
    {
        xEventGroupSetBits(event_flag, (1 << 0));
        printf("Task 1 : Setting event --> event generated\n");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    printf("Task 2\n");
    while (1)
    {
        xEventGroupSetBits(event_flag, (1 << 1));
        printf("Task 2 : Setting event --> event generated\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void task_3(void *data)
{
    printf("Task 3\n");
    while (1)
    {
        xEventGroupWaitBits(event_flag, (1 << 0) | (1 << 1), pdTRUE, pdFALSE, portMAX_DELAY);
        printf("Task 3: Received Event\n");
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("Main Task\n");
    event_flag = xEventGroupCreate();
    xTaskCreate(task_1, "First Task", 2048, NULL, 3, &task1_handle);
    xTaskCreate(task_2, "Second Task", 2048, NULL, 5, &task2_handle);
    xTaskCreate(task_3, "Third Task", 2048, NULL, 8, &task3_handle);
}
