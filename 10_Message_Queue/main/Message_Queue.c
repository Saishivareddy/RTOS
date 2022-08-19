#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#define MQ_SIZE 4
#define MSG_SIZE 64
TaskHandle_t task1_handle, task2_handle, task3_handle, task4_handle;
QueueHandle_t msg_queue;
void task_1(void *data)
{
    int task1_data = 100;
    printf("Task 1\n");
    while (1)
    {
        task1_data++;
        xQueueSend(msg_queue, &task1_data, pdMS_TO_TICKS(5000));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    int task2_data = 200;
    printf("Task 2\n");
    while (1)
    {
        task2_data++;
        xQueueSend(msg_queue, &task2_data, pdMS_TO_TICKS(5000));
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task_3(void *data)
{
    int buffer = 0;
    printf("Task 3\n");
    while (1)
    {
        xQueueReceive(msg_queue, &buffer, portMAX_DELAY);
        printf("Task 3: Received Data : %d\n", buffer);
    }
    vTaskDelete(NULL);
}

void task_4(void *data)
{
    int buffer = 0;
    int count = 0;
    printf("Task 4\n");
    while (1)
    {
        xQueueReceive(msg_queue, &buffer, pdMS_TO_TICKS(1000));
        printf("Task 4: Received Data : %d\n", buffer);
        count++;
        if (count > 50)
        {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("Main Task\n");
    msg_queue = xQueueCreate(MQ_SIZE, MSG_SIZE);
    xTaskCreate(task_1, "First Task", 2048, NULL, 3, &task1_handle);
    xTaskCreate(task_2, "Second Task", 2048, NULL, 5, &task2_handle);
    xTaskCreate(task_3, "Third Task", 2048, NULL, 8, &task3_handle);
    xTaskCreate(task_4, "Fourth Task", 2048, NULL, 12, &task4_handle);
}
