
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#define WCET_T1 200
#define WCET_T2 100
#define WCET_T3 100
#define WCET_T4 200

#define DEADLINE_T1 600
#define DEADLINE_T2 300
#define DEADLINE_T3 700
#define DEADLINE_T4 900

TaskHandle_t T1Handle, T2Handle, T3Handle, T4Handle;

void Task1(void *pvParameters) {
    while (1) {
        printf("Running T1\n");
        vTaskDelay(pdMS_TO_TICKS(WCET_T1));
    }
}
void Task2(void *pvParameters) {
    while (1) {
        printf("Running T2\n");
        vTaskDelay(pdMS_TO_TICKS(WCET_T2));
    }
}
void Task3(void *pvParameters) {
    while (1) {
        printf("Running T3\n");
        vTaskDelay(pdMS_TO_TICKS(WCET_T3));
    }
}
void Task4(void *pvParameters) {
    while (1) {
        printf("Running T4\n");
        vTaskDelay(pdMS_TO_TICKS(WCET_T4));
    }
}

void EDFScheduler(void *pvParameters) {
    const TickType_t delay = pdMS_TO_TICKS(500);
    while (1) {
        int deadlines[] = {DEADLINE_T1, DEADLINE_T2, DEADLINE_T3, DEADLINE_T4};
        TaskHandle_t handles[] = {T1Handle, T2Handle, T3Handle, T4Handle};

        int min = 0;
        for (int i = 1; i < 4; i++) {
            if (deadlines[i] < deadlines[min]) {
                min = i;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (i == min) {
                vTaskPrioritySet(handles[i], 3);
            } else {
                vTaskPrioritySet(handles[i], 1);
            }
        }

        vTaskDelay(delay);
    }
}

int main(void) {
    xTaskCreate(Task1, "T1", 1000, NULL, 1, &T1Handle);
    xTaskCreate(Task2, "T2", 1000, NULL, 1, &T2Handle);
    xTaskCreate(Task3, "T3", 1000, NULL, 1, &T3Handle);
    xTaskCreate(Task4, "T4", 1000, NULL, 1, &T4Handle);
    xTaskCreate(EDFScheduler, "EDF", 1000, NULL, 2, NULL);

    vTaskStartScheduler();
    return 0;
}
