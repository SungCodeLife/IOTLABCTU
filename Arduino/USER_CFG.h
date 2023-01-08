/* ---------------------------------------------------------------------------------------------- */
/*  File name:    def_cfg.h                                                                       */
/*  Description:  define macro                                                                    */
/*  Version:      1.0.0                                                                           */
/*  Date:         24/02/2022                                                                      */
/* ---------------------------------------------------------------------------------------------- */
#ifndef __USER_CFG_H_
#define __USER_CFG_H_

/* ---------------------------------------------------------------------------------------------- */
/*                                         include library                                        */
/* ---------------------------------------------------------------------------------------------- */
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SD.h>
#include <ArduinoJson.h>         /* JSON version 6.19.0 by Beniot Blanchon */
#include "DECODE.h"
//#include <LowPower.h>

/* ---------------------------------------------------------------------------------------------- */
/*                                     define position sensor                                     */
/* ---------------------------------------------------------------------------------------------- */

#define TEMP              0
#define SAL               1
#define PH                2
#define NH4               3
#define DO                4
#define NO3               5

/* ---------------------------------------------------------------------------------------------- */
/*                             define position parametter calibration                             */
/* ---------------------------------------------------------------------------------------------- */

#define SAL_Intercept     0
#define SAL_Slope         1
#define PH_Intercept      2
#define PH_Slope          3
#define NH4_Eo            4
#define NH4_m             5
#define DO_Intercept      6
#define DO_Slope          7

/* ---------------------------------------------------------------------------------------------- */
/*                               define position time in RTC Ds3231                               */
/* ---------------------------------------------------------------------------------------------- */

#define second            0
#define minute            1
#define hour              2
#define dayofweek         3
#define date              4
#define month             5
#define year              6

/* ---------------------------------------------------------------------------------------------- */
/*                               define position day of week                                      */
/* ---------------------------------------------------------------------------------------------- */

#define SUNDAY             1
#define MONDAY             2
#define TUESDAY            3
#define WEDNESDAY          4
#define THURSDAY           5
#define FRIDAY             6
#define SATURDAY           7

/* ---------------------------------------------------------------------------------------------- */
/*                               define Time read sensor                                          */
/* ---------------------------------------------------------------------------------------------- */

#define TIME10S            10     // time to start read sensor (seconds)
#define TimeBWT_SENSOR     1      // time between of the times read sensor (seconds)
#define TimeReadAnalog     1      // time read analog sensor
#define TIMES1READ_ANALOG  1      // times 1 read analog
#define TIMES2READ_ANALOG  1      // times 2 read analog
#define TIMES3READ_ANALOG  1      // times 3 read analog

#define WarmUpTEMP         20
#define WarmUpSAL          20
#define WarmUpPH           20
#define WarmUpNH4          20
#define WarmUpDO           20

/* ---------------------------------------------------------------------------------------------- */
/*                                      define MODULE PROGRAM                                     */
/* ---------------------------------------------------------------------------------------------- */

#define MODULE_APP      1
#define MODULE_SD       2
#define MODULE_SENSOR   3
#define MODULE_EEP      4
#define MODULE_JSON     5
#define MODULE_RTC      6

/* ---------------------------------------------------------------------------------------------- */
/*                                      define STATION IOT AB                                     */
/* ---------------------------------------------------------------------------------------------- */

#define AB_TAYYENA          99      // ANH GIANG - KHU RAY MOI
#define AB_NAMTHAIA         88      // YBND - KENH CHONG MY
#define AB_NAMTHAI          77      // DANH NA
#define AB_NAMYEN           66      // KENH BA BIEN

#define IOT_STATION1        AB_TAYYENA
#define IOT_STATION2        AB_NAMTHAIA
#define IOT_STATION3        AB_NAMTHAI
#define IOT_STATION4        AB_NAMYEN
#define IOT_STATION_TEST    0

/* ---------------------------------------------------------------------------------------------- */
/*                                      define parametter ADC                                     */
/* ---------------------------------------------------------------------------------------------- */

#define VOLTAGE_REF                 (5.0)
#define NumberTimes_ReadAnalog      (3)

/* ---------------------------------------------------------------------------------------------- */
/*                                      define parametter sleep                                   */
/* ---------------------------------------------------------------------------------------------- */

#define SLEEP_15MS      WDTO_15MS
#define SLEEP_30MS      WDTO_30MS
#define SLEEP_60MS      WDTO_60MS
#define SLEEP_120MS     WDTO_120MS
#define SLEEP_250MS     WDTO_250MS
#define SLEEP_500MS     WDTO_500MS
#define SLEEP_1S        WDTO_1S
#define SLEEP_2S        WDTO_2S
#define SLEEP_4S        WDTO_4S
#define SLEEP_8S        WDTO_8S
#define SLEEP_FOREVER   99

#define MODE_POWER_IDLE          SLEEP_MODE_IDLE
#define MODE_POWER_SAVE          SLEEP_MODE_PWR_SAVE
#define MODE_POWER_DOWN          SLEEP_MODE_PWR_DOWN
#define MODE_POWER_STANDBY       SLEEP_MODE_STANDBY
#define MODE_POWER_EXSTANDBY     SLEEP_MODE_EXT_STANDBY

/* ---------------------------------------------------------------------------------------------- */
/*                                   define some information use                                  */
/* ---------------------------------------------------------------------------------------------- */

#define PIN_SD_CARD       (24)                                         // PIN CS of SD Card SPI
#define DS3231_ADDRESS    (0x68)                                       // Address i2c of slave RTC DS3231
#define EEPROM_ADDRESS    4095                                         // calib config number save in eeprom
#define UARTJSON_ANALOG   255                                          // analog
#define UARTJSON_CALIB    254                                          // calibration
#define NEWDAY            253                                          // Dataloger at NewDay
#define NORMALDAY         252                                          // Dataloger at normal day
#define NEWBOARD          251                                          // 99 is new board ---------------------------------
#define OLDBOARD          250                                          // 11 is old board ---------------------------------
#define RESETBOARD        230
#define NONE              0

#define JSON_ANAOG_DETAIL_byClient  244                                          // json client
#define JSON_CALIB_byClient         240                                          // json client
#define JSON_ANALOG_byClient        248                                          // json client
#define JSON_VALUE_SENSOR_byClient  247                                          // json client

#define JSON_TASK_ByServer          246                                          // json server
#define JSON_NUMERIC_ByServer       245                                          // json server
#define JSON_CALIB_ByServer         249                                          // json server
#define JSON_CALIB_Get              243                                          // json server

#define JSON_TASK_CALIB             249
#define JSON_TASK_VALUE             247
#define JSON_TASK_ANALOG_SINGLE     248
#define JSON_TASK_ANALOG_DETAL      0
#define JSON_TASK_ARDUINORESET      235
#define JSON_TASK_RELAYPIN          234
#define JSON_TASK_ANALOGPIN         233

#define SHOW              Serial.print
#define SHOWLN            Serial.println
#define ENDLN             Serial.println();
#define DOWLN             "\r\n"

#define FOLDER_CONFIG     "Config"
#define FOLDER_DATALOG    "DataLog"
#define FOLDER_AN_CALI    "An_Cali"
#define DIRECT_ANALOG     ""
#define DIRECT_CONFIGS    ""
#define DIRECT_DATALOG    ""

/* ---------------------------------------------------------------------------------------------- */
/*                                           define UART                                          */
/* ---------------------------------------------------------------------------------------------- */

#define BUADRATE1         9600
#define BUADRATE2         115200
#define ESP8266V1         Serial1
#define ESPD1MINI         Serial2
#define ESPD1_SEND        ESPD1MINI.print

#define TIMER1MSK_OFF()      TIMSK1 &= ~(1 << TOIE1)
#define TIMER1MSK_ON()       TIMSK1 |= (1 << TOIE1)

/* ---------------------------------------------------------------------------------------------- */
/*                                define information Wifi + Server                                */
/* ---------------------------------------------------------------------------------------------- */

#define _ssid             "CTU_IOTLAB"            //
#define _pass             "02710271"              // An Bien - Kien Giang
#define _ipserver         "IoTlab.net.vn"         // station test   - TayYenA       - NamThaiA      - DanhNa        - BaBien
#define _StationCode      "iepF8KwIKv"            // iepF8KwIKv       9ZI1L084I7      9eqA2hcmpZ      K6hgva7zJd      dkWSDD8pQ4
#define _StationSecret    "G0JmNawogG"            // G0JmNawogG       2cPnm9RWtQ      3iJQtNz1zB      qjKPbhgcMs      zHtrLheTmE
#define _ServerPort       "3000"

#define SLEEP_ARDUINO(mode)   \
do{                           \
    set_sleep_mode(mode);     \
    cli();                    \
      sleep_enable();         \
      sei();                  \
      sleep_cpu();            \
      sleep_disable();        \
    sei();                    \
}while(0)

#define SLEEP_ENABLE(mode, Time)  \
do{                               \
  ADCSRA &= ~(1 << ADEN);         \
  wdt_enable(Time);               \
  WDTCSR |= (1 << WDIE);          \
  SLEEP_ARDUINO(mode);            \
  ADCSRA |= (1 << ADEN);          \
}while(0)

enum adc_t
{
	ADC_OFF,
	ADC_ON
};

enum timer5_t
{
	TIMER5_OFF,
	TIMER5_ON
};

enum timer4_t
{
	TIMER4_OFF,
	TIMER4_ON
};

enum timer3_t
{
	TIMER3_OFF,
	TIMER3_ON
};

enum timer2_t
{
	TIMER2_OFF,
	TIMER2_ON
};

enum timer1_t
{
	TIMER1_OFF,
	TIMER1_ON
};

enum timer0_t
{
	TIMER0_OFF,
	TIMER0_ON
};

enum spi_t
{
	SPI_OFF,
	SPI_ON
};

enum usart0_t
{
	USART0_OFF,
	USART0_ON
};

enum usart1_t
{
	USART1_OFF,
	USART1_ON
};

enum usart2_t
{
	USART2_OFF,
	USART2_ON
};

enum usart3_t
{
	USART3_OFF,
	USART3_ON
};

enum twi_t
{
	TWI_OFF,
	TWI_ON
};

extern uint16  DebugArduino;
extern uint8   StationIOT;
extern uint16  ErrorArduino;
extern uint16  SaveEnArduino;

void DB_LOG(uint8 module, String str);
void IOT_ENV_Init();

#endif

/* 
*   - các công việc còn dang dở
    + kiểm tra dùng cấu hình hiện tại trên server - da thuc hien
    + bổ sung truyền tham số task_poll_tim1 bằng mảng -> da thay the bang macro
    + kiểm tra nhiểu relay với led
    + cần tối ưu hóa tính toán thời gian cảm biến trong task_poll_tim1
    + cần code linh động đọc nhiều cảm biến
    + xem thêm sleep arduino và đánh thức arduino
*
* API
* void wdt_disable (void)
* wdt_enable(WDTO_8S) WDTO_15MS/WDTO_30MS/WDTO_60MS/WDTO_120MS/WDTO_250MS/WDTO_500MS/WDTO_1S/WDTO_2S/WDTO_4S/WDTO_8S
* 
*/
