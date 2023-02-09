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
    #include "queue.h"

    /** 
      * @defgroup RTOS-redefinitions the remaining of the functions is to complain with the project 
      *           coding standard
      @{ */
    #define Task_SysTickHandler             xPortSysTickHandler     /*!< Tick function */
    #define Task_GetSchedulerState          xTaskGetSchedulerState  /*!< Scheduler state */
    #define Task_CreateStatic               xTaskCreateStatic       /*!< Create task */
    #define Task_StartScheduler             vTaskStartScheduler     /*!< Run scheduler */
    #define Task_GetTickCount               xTaskGetTickCount       /*!< Get current ticks */
    #define Task_DelayUntil                 xTaskDelayUntil         /*!< Block task */

    #define Queue_CreateStatic              xQueueCreateStatic      /*!< Create queue */
    /**
      @} */

    /**
     * @brief   time and date structure
     */
    typedef struct _ApplicationTm_t 
    {
        uint32_t tm_sec;         /*!< seconds,  range 0 to 59          */
        uint32_t tm_min;         /*!< minutes, range 0 to 59           */
        uint32_t tm_hour;        /*!< hours, range 0 to 23             */
        uint32_t tm_mday;        /*!< day of the month, range 1 to 31  */
        uint32_t tm_mon;         /*!< month, range 1 to 12             */
        uint32_t tm_year;        /*!< The year from 1900 to 2099       */
        uint32_t tm_wday;        /*!< day of the week, range 0 to 6    */
        uint32_t tm_yday;        /*!< day in the year, range 0 to 365  */
        uint32_t tm_isdst;       /*!< daylight saving time             */
    } ApplicationTm_t;

    /**
     * @brief   Application message structure
     */
    typedef struct _ApplicationMsg_t
    {
        uint8_t msg;            /*!< Store the message type to send */
        ApplicationTm_t tm;     /*!< time and date in stdlib tm format */
    }ApplicationMsg_t;

    /**
     * @brief  Queue to communicate messages between serial and clock task
     */
    extern QueueHandle_t ClockQueue;

    /**
     * @brief  Queue to communicate messages between clock and display task
     */
    extern QueueHandle_t DisplayQueue;

    /**
     * @brief  Queue to communicate messages between serial and heartbeat task
     */
    extern QueueHandle_t HeartbeatQueue;


#endif

