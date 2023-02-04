/**
 * @file    app_ints.h
 * @brief   **CasioCAN interrupt vectors**
 *
 * This where the application interrupt vector are defined. This shall be the only place to do this
 * since we are using the HAL library, The vectors will only contain **HAL_xxx_IRQHandler** functions
 * plus some minor extra code. 
 * 
 * Vector definitions as week functions can be found at file **startup_stm32g0b1xx.s**
 *
 */

extern void NMI_Handler( void );
extern void HardFault_Handler( void );
extern void SVC_Handler( void );
extern void PendSV_Handler( void );
extern void SysTick_Handler( void );
