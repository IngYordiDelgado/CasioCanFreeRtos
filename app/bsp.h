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
      * @defgroup RTC-redefinitions the remaining of the functions is to complain with the project 
      *           coding standard
      @{ */
    typedef RCC_OscInitTypeDef              RccOscInit_t;                   /*!< Oscillator config structure */
    typedef RCC_ClkInitTypeDef              RccClkInit_t;                   /*!< Clock config structure */
    typedef RCC_PeriphCLKInitTypeDef        RccPeriphClkInit_t;             /*!< Peripheral clk config structure */

    #define Rcc_OscConfig                   HAL_RCC_OscConfig               /*!< Oscillator configuration */
    #define Rcc_ClockConfig                 HAL_RCC_ClockConfig             /*!< Clock configuration */
    #define Rcc_McoConfig                   HAL_RCC_MCOConfig               /*!< Mco pin configuration */
    #define Rcc_PeriphClkConfig             HAL_RCCEx_PeriphCLKConfig       /*!< Peripheral clocks */

    #define Pwr_EnableBkUpAccess            HAL_PWR_EnableBkUpAccess        /*!< Enable backup  */
    #define Pwr_ControlVoltageScaling       HAL_PWREx_ControlVoltageScaling /*!< Voltage scaling */

    typedef GPIO_InitTypeDef                GpioHandle_t;                   /*!< Gpio config handler */

    #define Gpio_Init                       HAL_GPIO_Init                   /*!< Init GPIOs */
    /**
      @} */

    /** 
      * @defgroup Application-Pins pins that will be used by the appllication to interface the
      *             external peripherals
      @{ */
    #define MCO_PIN                         GPIO_PIN_8  /*!< Output for the sysclock */
    #define MCO_PORT                        GPIOA       /*!< Port where the MCO pin is located */
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
    
    /* Definitions for custom micro delay */
    extern TIM_HandleTypeDef TIM6_Handler;    
    void Delay_us_Init(void);
    void Delay_us(uint16_t delay);


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

