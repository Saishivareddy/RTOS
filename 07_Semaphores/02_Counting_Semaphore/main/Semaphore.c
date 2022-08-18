#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

TaskHandle_t task1_handle, task2_handle, task3_handle, task4_handle;
SemaphoreHandle_t counting_sem;

void task_1(void *data)
{
    printf("Task 1: Started\n");
    printf("Task 1: Requesting for Semaphore\n");
    xSemaphoreTake(counting_sem, pdMS_TO_TICKS(20000));
    printf("Task 1: Got the Semaphore\n");
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    xSemaphoreGive(counting_sem);
    printf("Task 1: Released the Semaphore\n");
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    printf("Task 2: Started\n");
    printf("Task 2: Requesting for Semaphore\n");
    xSemaphoreTake(counting_sem, pdMS_TO_TICKS(20000));
    printf("Task 2: Got the Semaphore\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    xSemaphoreGive(counting_sem);
    printf("Task 2: Released the Semaphore\n");
    vTaskDelete(NULL);
}

void task_3(void *data)
{
    printf("Task 3: Started\n");
    printf("Task 3: Requesting for Semaphore\n");
    xSemaphoreTake(counting_sem, pdMS_TO_TICKS(20000));
    printf("Task 3: Got the Semaphore\n");
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    xSemaphoreGive(counting_sem);
    printf("Task 3: Released the Semaphore\n");
    vTaskDelete(NULL);
}

void task_4(void *data)
{
    printf("Task 4: Started\n");
    printf("Task 4: Requesting for Semaphore\n");
    xSemaphoreTake(counting_sem, pdMS_TO_TICKS(20000));
    printf("Task 4: Got the Semaphore\n");
    vTaskDelay(8000 / portTICK_PERIOD_MS);
    xSemaphoreGive(counting_sem);
    printf("Task 4: Released the Semaphore\n");
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("Main Task\n");
    counting_sem = xSemaphoreCreateCounting(4, 2);
    xTaskCreate(task_1, "first task", 2048, NULL, 3, &task1_handle);
    xTaskCreate(task_2, "second task", 2048, NULL, 3, &task2_handle);
    xTaskCreate(task_3, "third task", 2048, NULL, 3, &task3_handle);
    xTaskCreate(task_4, "fourth task", 2048, NULL, 3, &task4_handle);
}
