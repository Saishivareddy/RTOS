#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

TaskHandle_t task1_handle, task2_handle;
SemaphoreHandle_t task_signal;

void task_1(void *data)
{
    printf("Task 1: Started\n");
    vTaskDelay(pdMS_TO_TICKS(10000));
    xSemaphoreGive(task_signal);
    printf("Task 1: Released the Semaphore\n");
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    printf("Task 2: Started\n");
    printf("Task 2: Requesting for Semaphore\n");
    xSemaphoreTake(task_signal, pdMS_TO_TICKS(20000));
    printf("Task 2: Got the Semaphore\n");
    vTaskDelete(NULL);
}

void app_main(void)
{
    BaseType_t res1, res2;
    printf("Main Task\n");
    task_signal = xSemaphoreCreateBinary();
    res1 = xTaskCreate(task_1, "first task", 2048, NULL, 3, &task1_handle);
    res2 = xTaskCreate(task_2, "second task", 2048, NULL, 3, &task2_handle);
    if (res1 != pdPASS || res2 != pdPASS)
    {
        perror("Error in creating tasks: ");
    }
}
