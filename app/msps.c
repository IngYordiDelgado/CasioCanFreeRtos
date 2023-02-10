/**
 * @file    msps.c
 * @brief   **CasioCAN clock frequencies configuration**
 *
 * This is where the pheriperals port configuration is set, every peripheral in use calls a function
 * callback on each HAL_xxx_Init function, also Vector enable interrupts are located here as part
 * of the init fucntionality, main clock configuration shall be added
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
 * Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInitTypeDef structure
 * The frequency set is 64MHz with the internal 16MHz HSI oscilator. According to the formulas:
 * fVCO = fPLLIN x ( N / M ) = 16MHz x (8 / 1) = 128MHz
 * fPLLP = fVCO / P = 128MHz / 2 = 64MHz
 * fPLLQ = fVCO / Q = 128MHz / 2 = 64MHz
 * fPLLR = fVCO / R = 128MHz / 2 = 64MHz
 * MCO output PIN configuration function. Logic analizer: 24 MHz. SysClk / 4 = 64 MHz / 4 = 16 MHz.
 * LSE external cristal is set as source clock after turning off the internal oscillator.
 */

/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at HAL library */
void HAL_MspInit( void )
{
}