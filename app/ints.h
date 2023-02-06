/**
 * @file    ints.h
 * @brief   **CasioCAN interrupt vectors**
 *
 * This where the application interrupt vector are defined. This shall be the only place to do this 
 * since we are using the HAL library, The vectors will only contain **HAL_xxx_IRQHandler** functions 
 * plus some minor extra code.
 *
 * Vector definitions as week functions can be found at file **startup_stm32g0b1xx.s**
 */
#ifndef INTS_H_
#define INTS_H_

/*these functions are only to reference their implementation in the corresponding .rst file, should 
not be included anywhere in the project*/
void NMI_Handler( void );
void HardFault_Handler( void );
void SysTick_Handler( void );

#endif
