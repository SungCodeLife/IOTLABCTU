/* ---------------------------------------------------------------------------------------------- */
/*  File name:    rtc_ds3231.h                                                                    */
/*  Description:  Declare functions                                                               */
/*  Version:      1.0.0                                                                           */
/*  Date:         24/02/2022                                                                      */
/* ---------------------------------------------------------------------------------------------- */
#ifndef __RTC_DS3231_H_
#define __RTC_DS3231_H_

/* ---------------------------------------------------------------------------------------------- */
/*                                         include Library                                        */
/* ---------------------------------------------------------------------------------------------- */
#include "user_cfg.h"

/* ---------------------------------------------------------------------------------------------- */
/*                                       prototype function                                       */
/* ---------------------------------------------------------------------------------------------- */
String RTC_DS3231_DayOfWeedF_String(uint8 num);
String RTC_DS3231_ReadTime_String(uint8 *RTC);
void RTC_DS3231_SetTime_void(uint8 hourW, uint8 minuteW, uint8 secondW, uint8 dayofweekW, uint8 dateW, uint8 monthW, uint8 yearW);
uint8 D2B(uint8 num);
uint8 B2D(uint8 num);
void RTC_Init();


#endif
