/**
 * @file    app_msps.c
 * @brief   **CasioCAN peripheral pin configuration**
 *
 * This is where the pheriperals port configuration is set, every peripheral in use calls a function
 * callback on each HAL_xxx_Init function, also Vector enable interrupts are located here as part
 * of the init fucntionality, main clock configuration shall be added
 */
#include "stm32g0xx.h"
#include <stdint.h>

/**
 * @brief   **Extra gobal HAL library initilization**
 *
 * Function has nothing at the moment
 *
 */
void HAL_MspInit( void )
{
    
}
