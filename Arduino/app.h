#ifndef __APP_H_
#define __APP_H_

#include "RTC_DS3231.h"             /* lib user */
#include "JSON.h"                   /* lib user */
#include "EEP.h"                    /* lib user */
#include "SENSOR.h"                 /* lib user */
#include "SD_CARD.h"                /* lib user */
#include "user_cfg.h"

extern uint16 TimeLine;
extern uint8 RTC_Time[7];

// /*--------------------------------------------- prototype function -----------------------------------------*/
void TIMER1_Init();
void Calibration_Init_void();
void DataLoger2SDCard(uint8);
void Json_Parse_void(char DataParse[], uint8 FlagReset);
void TIM1_POLL_void();

#endif
