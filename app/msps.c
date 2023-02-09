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

FDCAN_HandleTypeDef CANHandler;
SPI_HandleTypeDef SpiHandle; /*estructura para manejar el spi*/

void HAL_MspInit( void )
{
    HAL_Init( ); /* Inicializamos libreria HAL */

    /* Declaramos las opciones para configurar el modulo FDCAN1 para transmitir al bus CAN a 100Kbps
     y sample point de 75%, la frecuencia con la que el modulo de CAN se alimenta es
     fCAN = fHSI / CANHandler.Init.ClockDivider / CANHandler.Init.NominalPrescaler
     fCAN = 16MHz / 1 / 10 = 1.6Mhz
     El numero de time qantas requerido es
     Ntq = fCAN / CANbaudrate
     Ntq = 1.6Mhz / 100Kbps = 16
     EL porcentaje de sample point es
     Sp = ( CANHandler.Init.NominalTimeSeg1 +  1 / Ntq ) * 100
     Sp = ( ( 11 + 1 ) / 16 ) * 100 = 75%*/
    CANHandler.Instance                  = FDCAN1;
    CANHandler.Init.Mode                 = FDCAN_MODE_NORMAL;
    CANHandler.Init.FrameFormat          = FDCAN_FRAME_CLASSIC;
    CANHandler.Init.ClockDivider         = FDCAN_CLOCK_DIV1;
    CANHandler.Init.TxFifoQueueMode      = FDCAN_TX_FIFO_OPERATION;
    CANHandler.Init.AutoRetransmission   = DISABLE;
    CANHandler.Init.TransmitPause        = DISABLE;
    CANHandler.Init.ProtocolException    = DISABLE;
    CANHandler.Init.ExtFiltersNbr        = 0;
    CANHandler.Init.StdFiltersNbr        = 0;
    CANHandler.Init.NominalPrescaler     = 10;
    CANHandler.Init.NominalSyncJumpWidth = 1;
    CANHandler.Init.NominalTimeSeg1      = 11;
    CANHandler.Init.NominalTimeSeg2      = 4;
    HAL_FDCAN_Init( &CANHandler );
    /* Change FDCAN instance from initialization mode to normal mode */
    HAL_FDCAN_Start( &CANHandler );

    /*Configuramos al spi en modo maestro, comunicacion full-duplex, polaridad del reloj en alto y fase en flanco de bajada */
    SpiHandle.Instance            = SPI2;
    SpiHandle.Init.Mode           = SPI_MODE_MASTER;
    SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;    //16MHz / 16 = 1MHz
    SpiHandle.Init.Direction      = SPI_DIRECTION_2LINES;
    SpiHandle.Init.CLKPhase       = SPI_PHASE_2EDGE;
    SpiHandle.Init.CLKPolarity    = SPI_POLARITY_HIGH;
    SpiHandle.Init.DataSize       = SPI_DATASIZE_8BIT;
    SpiHandle.Init.FirstBit       = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.NSS            = SPI_NSS_SOFT;
    SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    SpiHandle.Init.TIMode         = SPI_TIMODE_DISABLED;
    /* aplicamos la configuracion al spi 1 pero antes nos aseguramos que el esclavo este deshabilitado pin C8 en alto*/
    HAL_SPI_Init( &SpiHandle );
}
