/**
 * @file    ints.c
 * @brief   **CasioCAN interrupt vectors**
 *
 * This where the application interrupt vector are defined. This shall be the only place to do this
 * since we are using the HAL library, The vectors will only contain **HAL_xxx_IRQHandler** functions
 * plus some minor extra code.
 *
 * Vector definitions as week functions can be found at file **startup_stm32g0b1xx.s**
 */
#include "bsp.h"

/**
 * @brief   **Non Maskable Interrupt vector**
 *
 * @todo Define when the program will jump here and whay shall be do, in case necesary
 *
 */
/* cppcheck-suppress misra-c2012-8.4 ; there is no need for external linkage */
void NMI_Handler( void )
{
}

/**
 * @brief   **Hard Fault Vector**
 *
 * For the moment this vector will allocate the macro assert_param that eventually will need to be
 * implemented
 *
 * @todo Define when the program will jump here and whay shall be do, in case necesary
 *
 */
/* cppcheck-suppress misra-c2012-8.4 ; there is no need for external linkage */
void HardFault_Handler( void )
{
    assert_param( 0u );
}

/**
 * @brief   **System Tick timer Vector**
 *
 * The program will jump here every millisecond and increments a global variable used internally by
 * as system tick by the HAL library, which helps the program to keep tracking of every millisencond
 * passed. also the RTOS will use this same interrupt in its own way to keep tracking of the ticks
 * for their internal mechanism, to switch task and count milliseconds
 */
/* cppcheck-suppress misra-c2012-8.4 ; there is no need for external linkage */
void SysTick_Handler( void )
{
    /*Run the RTOS tick rutine only if the scheduler is running */
    if( Task_GetSchedulerState( ) != taskSCHEDULER_NOT_STARTED )
    {
        Task_SysTickHandler( );
    }
    /*Increment the STM32CubeG0 library tick*/
    HAL_IncTick( );
}
