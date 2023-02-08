/**
 * @file    main.h
 * @brief   **CasioCAN++ Application entry point**
 *
 * The main file is the entry point of the application and only has the RTOs mechanism required
 * to admnistrate the application tasks to run, the actual portion of the application is aplitted
 * into five main tasks
 *
 * - **CLock**.- In charge of controlling the internal time and date
 * - **Serial**.- In charge of receive and transmit the CAN messages
 * - **Display**.- Only manage to display the information required for the user like time and date
 * - **Heartbeat**.- Signaling lights to feedback the user that the application is running healthy
 * - **Watchdog**.- Trigger a software reset in case of a freeze event
 *
 * All of these tasks are grouped into three major operative systems task configured with hard
 * deadlines of 10, 50 and 100ms
 */
#ifndef MAIN_H_
#define MAIN_H_

int main( void );

#endif
