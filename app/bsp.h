/**
 * @file    bsp.h
 * @brief   **CasioCAN Global definitions and symbols**
 *
 * This is where cross file symbols are place, if more than one file needs any of the symbols
 * shall be defined here, also control or pin definitions shall be allocated in the file 
 */
#ifndef BSP_H_
#define BSP_H_

    #include "stm32g0xx.h"
    #include <stdint.h>
    #include "FreeRTOS.h"
    #include "task.h"

    /** 
      * @defgroup RTOS-redefinitions the remaining of the functions is to complain with the project 
      *           coding standar
      @{ */
    #define Task_SysTickHandler             xPortSysTickHandler     /*!< Tick function */
    #define Task_GetSchedulerState          xTaskGetSchedulerState  /*!< Scheduler state */
    #define Task_CreateStatic               xTaskCreateStatic       /*!< Create task */
    #define Task_StartScheduler             vTaskStartScheduler     /*!< Run scheduler */
    #define Task_GetTickCount               xTaskGetTickCount       /*!< Get current ticks */
    #define Task_DelayUntil                 xTaskDelayUntil         /*!< Block task */
    /**
      @} */

#endif

