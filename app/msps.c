/**
 * @file    msps.c
 * @brief   **CasioCAN peripheral pin configuration**
 *
 * This is where the pheriperals port configuration is set, every peripheral in use calls a function
 * callback on each HAL_xxx_Init function, also Vector enable interrupts are located here as part
 * of the init fucntionality, main clock configuration shall be added
 */
#include "bsp.h"

/**
 * @brief   **Extra gobal HAL library initilization**
 *
 * Function has nothing at the moment
 *
 */
/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at HAL library */

void HAL_MspInit( void )
{
    RCC_OscInitTypeDef RCC_OscInitStruct         = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct         = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

    __HAL_RCC_SYSCFG_CLK_ENABLE( );
    __HAL_RCC_PWR_CLK_ENABLE( );

    /** Configure the main internal regulator output voltage*/
    HAL_PWREx_ControlVoltageScaling( PWR_REGULATOR_VOLTAGE_SCALE1 );

    /* Initializes the RCC Oscillators according to the specified parameters in the RCC_OscInitTypeDef structure
    The frequency set is 64MHz with the internal 16MHz HSI oscilator. According to the formulas:
    fVCO = fPLLIN x ( N / M ) = 16MHz x (8 / 1) = 128MHz
    fPLLP = fVCO / P = 128MHz / 2 = 64MHz
    fPLLQ = fVCO / Q = 128MHz / 2 = 64MHz
    fPLLR = fVCO / R = 128MHz / 2 = 64MHz
    */
    RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
    RCC_OscInitStruct.HSIDiv              = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM            = RCC_PLLM_DIV1;  //fVCO = fPLLIN x ( N / M ) = 16MHz x (N / 1)
    RCC_OscInitStruct.PLL.PLLN            = 8;  //16MHz x (8 / 1) = 128MHz
    RCC_OscInitStruct.PLL.PLLP            = RCC_PLLP_DIV2;  //fPLLP = fVCO / P = 128MHz / 2 = 64MHz
    RCC_OscInitStruct.PLL.PLLQ            = RCC_PLLQ_DIV2;  //fPLLQ = fVCO / Q = 128MHz / 2 = 64MHz
    RCC_OscInitStruct.PLL.PLLR            = RCC_PLLR_DIV2;  //fPLLR = fVCO / R = 128MHz / 2 = 64MHz
    HAL_RCC_OscConfig( &RCC_OscInitStruct );

    /** Initializes the CPU, AHB and APB buses clocks*/
    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1; // 64MHz/1 = 64MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;   // 64MHz/1 = 64MHz
    HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_2 );

    // ENABLE LSE CLOCK
    /*Enable backup domain*/
    HAL_PWREx_ControlVoltageScaling( PWR_REGULATOR_VOLTAGE_SCALE1 );
    HAL_PWR_EnableBkUpAccess( );
    __HAL_RCC_LSEDRIVE_CONFIG( RCC_LSEDRIVE_LOW );

    /*reset previous RTC source clock*/
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection    = RCC_RTCCLKSOURCE_NONE;
    HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct );

    /* Configure LSE/LSI as RTC clock source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState       = RCC_LSE_ON;  // ON external oscillator LSE 32.768 KHz
    RCC_OscInitStruct.LSIState       = RCC_LSI_OFF; // OFF internal oscillator LSI 32 KHz
    HAL_RCC_OscConfig( &RCC_OscInitStruct );

    /*Set LSE as source clock*/
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct );

    /* Peripheral clock enable */
    __HAL_RCC_RTC_ENABLE( );
    __HAL_RCC_RTCAPB_CLK_ENABLE( );

    HAL_RCC_MCOConfig( RCC_MCO1, RCC_MCO1SOURCE_LSE, RCC_MCODIV_1 ); // MCO output PIN conf. Logic analizer: 24 MHz
                                                                     // fLSE / 2 = 32.768 MHz / 2 = 16.384 MHz
}