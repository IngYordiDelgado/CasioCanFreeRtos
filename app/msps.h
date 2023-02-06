/**
 * @file    msps.h
 * @brief   **CasioCAN peripheral pin configuration**
 *
 * This is where the pheriperals port configuration is set, every peripheral in use calls a function 
 * callback on each HAL_xxx_Init function, also Vector enable interrupts are located here as part 
 * of the init fucntionality, main clock configuration shall be added
 */
#ifndef MSPS_H_
#define MSPS_H_

/*these functions are only to reference their implementation in the corresponding .rst file, should 
not be included anywhere in the project*/
void HAL_MspInit( void );

#endif
