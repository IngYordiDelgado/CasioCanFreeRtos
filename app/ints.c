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
#include "stm32g0xx.h"
#include <stdint.h>

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
 * The program will jump here every millisecond and only will increment a global variable acting as 
 * system tick, which helps the program to keep tracking of every millisencond passed
 *
 */
/* cppcheck-suppress misra-c2012-8.4 ; there is no need for external linkage */
void SysTick_Handler( void )
{
    HAL_IncTick( );
}
