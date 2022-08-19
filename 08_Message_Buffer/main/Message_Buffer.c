#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"

TaskHandle_t task1_handle, task2_handle;
MessageBufferHandle_t msg_buff;

void task_1(void *data)
{
    printf("Task 1: Started\n");
    xMessageBufferSend(msg_buff, "First Message", 15, pdMS_TO_TICKS(00));
    xMessageBufferSend(msg_buff, "Second Message", 15, pdMS_TO_TICKS(00));
    xMessageBufferSend(msg_buff, "Third Message", 15, pdMS_TO_TICKS(0));
    printf("Task 1: Send Data to Task 2\n");
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    unsigned char rec_buff[200];
    printf("Task 2: Started\n");
    while (1)
    {
        xMessageBufferReceive(msg_buff, &rec_buff, 200, pdMS_TO_TICKS(1000));
        printf("Task 2: Received Data is %s\n", rec_buff);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("Main Task\n");
    msg_buff = xMessageBufferCreate(200);
    xTaskCreate(task_1, "task1", 2048, NULL, 3, &task1_handle);
    xTaskCreate(task_2, "task2", 2048, NULL, 5, &task2_handle);
}
