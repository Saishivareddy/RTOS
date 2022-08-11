#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle;

void task_1(void *data)
{
    int count = 0;
    while (1)
    {
        count += 1;
        if (count > 5)
        {
            vTaskResume(task2_handle);
            count = 0;
        }
        UBaseType_t prio;
        prio = uxTaskPriorityGet(task1_handle);
        printf("Task 1 and Priority is %d\n", prio);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(task1_handle);
}

void task_2(void *data)
{
    while (1)
    {
        vTaskSuspend(task2_handle);
        UBaseType_t prio;
        prio = uxTaskPriorityGet(task2_handle);
        printf("Task 2 and Priority is %d\n", prio);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(task2_handle);
}
void app_main()
{
    BaseType_t res1, res2;
    res1 = xTaskCreate(task_1, "FIRST TASK", 2048, NULL, 5, &task1_handle);
    res2 = xTaskCreate(task_2, "Second Task", 2048, NULL, 6, &task2_handle);
    if (res1 && res2 != pdPASS)
    {
        perror("Error in Creating Tasks\n");
    }
}