/**
* @file app_clock.h
* @brief this header file will contain all required
* definitions for clock functionality implementation.
*
* @author Yordi Edgardo Delgado Ortiz
*
* @date 01/04/2023
*/

#ifndef CLOCK_H__
#define CLOCK_H__

  #include "bsp.h"
  #include "timers.h"
  #include "serial.h"

  #define   FALSE 0
  #define   TRUE  1
  #define ONESECOND   60u
  #define DISPLAY_TIMER_PERIOD ( ( pdMS_TO_TICKS( 1000u ) ) )
  #define ALARM_TIMER_PERIOD ( ( pdMS_TO_TICKS( 1000u ) ) )
  #define BUZZER      GPIO_PIN_14

  //extern uint8_t AlarmSet;
 /*  extern uint8_t AlarmActive;
  extern uint8_t BtnPush;
  extern uint8_t DisplayAlarm_Run;
   */
  

  typedef struct _APP_Display_MsgTypeDef
  {
    uint8_t           msg;          /*!< Store the message type to send */
    APP_TmTypeDef     tm;     /*!< time and date in stdlib tm format */
    RTC_AlarmTypeDef  sAlarm;
    uint8_t           Alarm_set; 
  }APP_Display_MsgTypeDef;

  extern RTC_HandleTypeDef        hrtc;
  extern uint32_t TimerId;
  extern TaskHandle_t DisplayTaskHandler;

  extern void Clock_Init( void );
  extern void Clock_Task( void );
  extern void HAL_GPIO_EXTI_Falling_Callback( uint16_t GPIO_Pin );
  extern void HAL_GPIO_EXTI_Rising_Callback( uint16_t GPIO_Pin );
  extern void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *rtc);
  extern void Display_TimerCallback(TimerHandle_t xTimer);
  extern uint8_t  leap(uint32_t year);
  typedef enum DisplayEvents{
    DISPLAY_NO_MSG  = 0u,
    DISPLAY_ALARM_ACTIVE,
    DISPLAY_ALARM_SET,
    DISPLAY_ALARM_NOSET,
    DISPLAY_TIMESTR_PROCESSING,
    DISPLAY_DATESTR_PROCESSING,
    DISPLAY_LCD_WRITE,
    DISPLAY_LAST  
  }App_Display_Events;
  
 
  typedef enum Clock_Events{
      CLOCK_MSG_NONE = 0u,
      CLOCK_TIME,
      CLOCK_DATE,
      CLOCK_ALARM,
      CLOCK_DISPLAY,
      CLOCK_ALARM_ACTIVATE,
      CLOCK_ALARM_DEACTIVATE,
      CLOCK_ALARM_DISPLAY,
      CLOCK_LAST
    }Clock_Events_TypeDef;
  
  typedef struct Clock_EventMachine
  {
    Clock_Events_TypeDef event;
    void(*const func)(APP_Display_MsgTypeDef *msg_struct);
  }Clock_EventMachine_Typedef;
  extern const Clock_EventMachine_Typedef Clock_EventsMachine;
#endif