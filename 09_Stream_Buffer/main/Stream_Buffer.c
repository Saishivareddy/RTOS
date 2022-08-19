#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/stream_buffer.h"

TaskHandle_t task1_handle, task2_handle;
StreamBufferHandle_t stream_buff;
unsigned char rec_buff[200];
void task_1(void *data)
{
    printf("Task 1: Started\n");
    xStreamBufferSend(stream_buff, "First Message\n", 14, pdMS_TO_TICKS(10000));
    xStreamBufferSend(stream_buff, "Second Message\n", 15, pdMS_TO_TICKS(10000));
    xStreamBufferSend(stream_buff, "Third Message\n", 14, pdMS_TO_TICKS(10000));
    printf("Task 1: Send Data to Task 2\n");
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    printf("Task 2: Started\n");
    size_t rsize = xStreamBufferReceive(stream_buff, &rec_buff, 200, pdMS_TO_TICKS(10000));
    printf("Task 2: Received Data: %d :: %s \n", rsize, rec_buff);
    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("Main Task\n");
    stream_buff = xStreamBufferCreate(200, 14);
    xTaskCreate(task_1, "task1", 2048, NULL, 3, &task1_handle);
    xTaskCreate(task_2, "task2", 2048, NULL, 5, &task2_handle);
}
