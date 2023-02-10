/**
 * @file    <msps.c>
 * @brief   **CasioCAN clock frequencies configuration**
 *
 * This is where the CPU clock frequency is set at 64MHz, this making use from the internal oscillator
 * HSI 16 MHz, also the AHB and APB busses are set to 64MHz and an extern oscillator LSE is set to feed
 * the RTC. A MCO output is set to be measure with a 24MHz logic analyzer.
 *
 */
#include "bsp.h"

/**
 * @brief   **HAL library call-back function**
 *
 * This is a call-back function called by the stm32g0xx HAL library that runs when the HAL_Init function is
 * also called, this is where the application should set the CPU frequency using the predefined HAL functions.
 * This is where the CPU clock frequency is set at 64 MHz using the internal HSI 16 MHz RC Oscillator.
 * Also the AHB and APB busses are set to work at 64MHz.
 * LSE is set to feed the RTC with an external 32.768 KHz cristal on a different clock domain.
 * MCO output is set to be suitable to be measure by a 24 MHz logic analizer.
 */

void HAL_MspInit( void );

void HAL_MspInit( void )
{
    
}