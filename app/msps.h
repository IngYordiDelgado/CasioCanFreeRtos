/**
 * @file    msps.h
 * @brief   **CasioCAN peripheral pin configuration**
 *
 * This is where the pheriperals port configuration is set, every peripheral in use calls a function
 * callback on each HAL_xxx_Init function, also Vector enable interrupts are located here as part
 * of the init fucntionality, main clock configuration shall be added
 */
extern void HAL_MspInit( void );
