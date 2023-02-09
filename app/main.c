/**
 * @file    main.c
 * @brief   **CasioCAN++ Application entry point**
 *
 * The main file is the entry point of the application and only has the RTOs mechanism required
 * to admnistrate the application tasks to run, the actual portion of the application is aplitted
 * into five main tasks
 *
 * - **Clock**.- In charge of controlling the internal time and date
 * - **Serial**.- In change of receive and transmit the CAN messages
 * - **Display**.- Only manage to display the information required to the user like time and date
 * - **Heartbeat**.- Signaling lights to feedback the user the application is running healthy
 * - **Watchdog**.- Trigger a software reset in case of a freeze event
 *
 * All of these tasks are grouped into three major operative systems task configured with hard
 * deadlines of 10, 50 and 100ms
 */
#include "bsp.h"

static void Task_10ms( void *Parameters );
static void Task_50ms( void *Parameters );
static void Task_100ms( void *Parameters );

/**
 * @brief   **Application entry point**
 *
 * The function will mainly initialize the two third party stacks in use, the **STM32CubeG0** HAL library
 * and the **FreeRTOS** operative system, also it is the place to register the tasks to run in the
 * operative system with they required parameter:
 *
 *  - 10ms task   512 bytes of stack  Highest priority
 *  - 50ms task   512 bytes of stack  Medium priority
 *  - 100ms task  512 bytes of stack  Lowest priority
 *
 * The Queue to comunicate between more than one task shall also be created here, such as:
 *
 *  - Clock Queue Comunicates Serial to Clock task
 *  - Clock Queue Comunicates Clock to Display task
 *  - Clock Queue Comunicates Serial to Heartbeat task
 *
 * @note    The main function will never return, if that happens needs to be consider a potential error
 *          on the RTOS and their object configuration
 *
 * @retval Always 0u
 */
int main( void )
{
    /*Dummy calls to allow compilation*/
    Task_10ms( NULL );
    Task_50ms( NULL );
    Task_100ms( NULL );

    return 0u;
}

/**
 * @brief   **10 millisecond task**
 *
 * Ten milliseconds periodic task with no return option, application should place here all tasks
 * required to run every 10ms at the highest priority keeping in mind their execution shall be as
 * short as possible. The task is called by the operative system once its kernel is running
 *
 * task to run:
 *  - Serial task
 *
 * @param[in] Parameters pointer to optional paramaters used to pass the task period time in ms
 */
static void Task_10ms( void *Parameters )
{
    (void)Parameters;

    /*Place here any task intilization*/

    for( ;; )
    {
        /*Place here any task periodic rutine*/
    }
}

/**
 * @brief   **50 millisecond task**
 *
 * Fifthy milliseconds periodic task with no return option, application should place here all tasks
 * required to run every 50ms at medium priority keeping in mind their execution shall be as
 * short as possible. The task is called by the operative system once its kernel is running
 *
 * task to run:
 *  - Clock task
 *  - Watchdog task
 *  - Heartbeat task
 *
 * @param[in] Parameters pointer to optional paramaters used to pass the task period time in ms
 */
static void Task_50ms( void *Parameters )
{
    (void)Parameters;

    /*Place here any task intilization*/

    for( ;; )
    {
        /*Place here any task periodic rutine*/
    }
}

/**
 * @brief   **100 millisecond task**
 *
 * Hundred milliseconds periodic task with no return option, application should place here all tasks
 * required to run every 100ms at the lowest priority keeping in mind their execution can long but no
 * more then its periodicity. The task is called by the operative system once its kernel is running
 *
 * task to run:
 *  - Display task
 *
 * @param[in] Parameters pointer to optional paramaters used to pass the task period time in ms
 */
static void Task_100ms( void *Parameters )
{
    (void)Parameters;

    /*Place here any task intilization*/

    for( ;; )
    {
        /*Place here any task periodic rutine*/
    }
}

/**
 * @brief   **Background task**
 *
 * This function is called continuously by the background task when no other task is running
 * a future algorithm to meassure CPU and stack utilization can be implemented.
 *
 * @note any code place here shall be at the lowest priority since always will be preempted by the tasks
 */
/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at RTOSs library */
void vApplicationIdleHook( void )
{
}

/**
 * @brief   **10 milliseoncd task**
 *
 * configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an implementation
 * of vApplicationGetIdleTaskMemory() to provide the memory that is used by the Idle task. This is
 * going to be achieved declaring a static StaticTask_t TCB and its corresponding static array
 *
 * @param[out] ppxIdleTaskTCBBuffer pointer to the StaticTask_t structure in which the Idle task's
 *                                  state will be stored
 * @param[out] ppxIdleTaskStackBuffer array that will be used as the Idle task's stack.
 * @param[out] pulIdleTaskStackSize array size that will be used as the Idle task's stack.
 */
/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at RTOS library */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
    (void)ppxIdleTaskTCBBuffer;
    (void)ppxIdleTaskStackBuffer;
    (void)pulIdleTaskStackSize;
}

/**
 * @brief   **10 milliseoncd task**
 *
 * configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the application must
 * provide an implementation of vApplicationGetTimerTaskMemory() to provide the memory that is used
 * by the Timer service task. This is going to be achieved declaring a static StaticTask_t TCB and
 * its corresponding static array
 *
 * @param[out] ppxTimerTaskTCBBuffer pointer to the StaticTask_t structure in which the Timer task's
 *                                  state will be stored
 * @param[out] ppxTimerTaskStackBuffer array that will be used as the Timer task's stack.
 * @param[out] pulTimerTaskStackSize array size that will be used as the Timer task's stack.
 */
/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at RTOS library */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
    (void)ppxTimerTaskTCBBuffer;
    (void)ppxTimerTaskStackBuffer;
    (void)pulTimerTaskStackSize;
}
