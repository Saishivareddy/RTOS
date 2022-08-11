#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t task_handle;
TimerHandle_t timer_handle;
void callback_timer(TimerHandle_t xtimer)
{
    printf("Timer Fired\n");
}

void task_timer(void *data)
{
    printf("This is Task Created\n");
    timer_handle = xTimerCreate("one_shot_timer", 1000 / portTICK_PERIOD_MS, pdFALSE, 0, callback_timer);
    xTimerStart(timer_handle, 0);
    vTaskDelete(task_handle);
}

void app_main()
{
    BaseType_t res;
    printf("This is the Main task\n");
    res = xTaskCreate(task_timer, "Timer_task", 2048, NULL, 3, &task_handle);
    if (res != pdPASS)
    {
        perror("Error in Creating task :");
    }
}