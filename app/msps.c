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
 * This is a call-back function called by the stm32g0xx HAL library that runs when the HAL_Init
 * function is also called.This is where the CPU clock frequency is set at 64MHz using the internal
 * HSI 16MHz RC Oscillator and the PLL. The AHB bus will also set to 64MHz, but the APB buss is
 * set to work at 32MHz, while the Systick timer will run to 64MHz / 8 = 8MHz.
 *
 * The following formula calculates the Frequencies
 *
 * @code
 * fVCO = fPLLIN x ( N / M ) = 16MHz x (8 / 1) = 128MHz
 * fPLLP = fVCO / P = 128MHz / 2 = 64MHz
 * fPLLQ = fVCO / Q = 128MHz / 2 = 64MHz
 * fPLLR = fVCO / R = 128MHz / 2 = 64MHz
 *
 * fAHB = fPLLP / DIV_1 = 64MHz
 * fAPB = fAHB / DIV_2 = 32MHz
 * @endcode
 *
 * The LSE is set to feed the RTC with an external 32.768 KHz cristal on a different clock domain.
 *
 * The pin A08 will be configured to act as the MCO to output the sysclck signal which esentially
 * feeds the main microcontroller BUS (AHB). The frequency is prescaled to 1MHz using a 64 preescaler
 */
/* cppcheck-suppress misra-c2012-8.4 ; its external linkage is declared at HAL library */
void HAL_MspInit( void )
{
    /* Init structures */
    RccOscInit_t OscInitStruct             = { 0 };
    RccClkInit_t ClkInitStruct             = { 0 };
    RccPeriphClkInit_t PeriphClkInitStruct = { 0 };
    GpioHandle_t McoInitStruct             = { 0 };

    /* System clock enable */
    __HAL_RCC_SYSCFG_CLK_ENABLE( );
    __HAL_RCC_PWR_CLK_ENABLE( );

    /* Initializes the RCC Oscillators */
    OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    OscInitStruct.HSIState            = RCC_HSI_ON;
    OscInitStruct.HSIDiv              = RCC_HSI_DIV1;
    OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
    OscInitStruct.PLL.PLLM            = RCC_PLLM_DIV1;
    OscInitStruct.PLL.PLLN            = 8;
    OscInitStruct.PLL.PLLP            = RCC_PLLP_DIV2;
    OscInitStruct.PLL.PLLQ            = RCC_PLLQ_DIV2;
    OscInitStruct.PLL.PLLR            = RCC_PLLR_DIV2;
    Rcc_OscConfig( &OscInitStruct );

    /** Initializes the CPU, AHB and APB buses clocks */
    ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    Rcc_ClockConfig( &ClkInitStruct, FLASH_LATENCY_2 );

    /* Enable backup domain */
    Pwr_ControlVoltageScaling( PWR_REGULATOR_VOLTAGE_SCALE1 );
    Pwr_EnableBkUpAccess( );
    __HAL_RCC_LSEDRIVE_CONFIG( RCC_LSEDRIVE_LOW );

    /* Reset previous RTC source clock */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection    = RCC_RTCCLKSOURCE_NONE;
    Rcc_PeriphClkConfig( &PeriphClkInitStruct );

    /* Configure LSE as RTC clock source */
    OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
    OscInitStruct.PLL.PLLState   = RCC_PLL_NONE;
    OscInitStruct.LSEState       = RCC_LSE_ON;  /* ON external oscillator LSE 32.768 KHz*/
    OscInitStruct.LSIState       = RCC_LSI_OFF; /* OFF internal oscillator LSI 32 KHz */
    Rcc_OscConfig( &OscInitStruct );

    /*Set LSE as source clock */
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    Rcc_PeriphClkConfig( &PeriphClkInitStruct );

    /* MCO output PIN configuration function. Logic analizer: 24 MHz */
    McoInitStruct.Pin       = MCO_PIN;
    McoInitStruct.Mode      = GPIO_MODE_AF_PP;
    McoInitStruct.Pull      = GPIO_PULLUP;
    McoInitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    McoInitStruct.Alternate = GPIO_AF0_MCO;
    Gpio_Init( MCO_PORT, &McoInitStruct );
    /* SysClk / 2 = 64 MHz / 64 = 1 MHz */
    Rcc_McoConfig( RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_64 );
}
