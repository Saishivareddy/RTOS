#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t serial_task_handle;

void serial_task(void *data)
{
    printf("In the Created Task\n");
    vTaskDelete(NULL);
}

void app_main()
{
    BaseType_t res;
    res = xTaskCreate(serial_task, "SERIALTASK", 2048, NULL, 5, &serial_task_handle);
    if(res == pdPASS)
    {
        printf("Task Created Successfully\n");
    }
}