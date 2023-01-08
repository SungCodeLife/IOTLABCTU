
#ifndef _DECODE_H_
#define _DECODE_H_

#include <stdint.h>

/* ---------------------------------------------------------------------------------------------- */
/*                                        define a new type                                       */
/* ---------------------------------------------------------------------------------------------- */

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;

#define GPIO_PIN_4      4
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_45     45

#define ANALOG_PIN_A0   A0
#define ANALOG_PIN_A1   A1
#define ANALOG_PIN_A2   A2
#define ANALOG_PIN_A3   A3
#define ANALOG_PIN_A4   A4
#define ANALOG_PIN_A5   A5

#define BIT0     0x01
#define BIT1     0x02
#define BIT2     0x04
#define BIT3     0x08
#define BIT4     0x10
#define BIT5     0x20
#define BIT6     0x40
#define BIT7     0x80
#define BIT8     0x100
#define BIT9     0x200
#define BIT10    0x400
#define BIT11    0x800
#define BIT12    0x1000
#define BIT13    0x2000
#define BIT14    0x4000
#define BIT15    0x8000

#define SHIFTBIT0    0
#define SHIFTBIT1    1
#define SHIFTBIT2    2
#define SHIFTBIT3    3
#define SHIFTBIT4    4
#define SHIFTBIT5    5
#define SHIFTBIT6    6
#define SHIFTBIT7    7
#define SHIFTBIT8    8
#define SHIFTBIT9    9
#define SHIFTBIT10   10
#define SHIFTBIT11   11
#define SHIFTBIT12   12
#define SHIFTBIT13   13
#define SHIFTBIT14   14
#define SHIFTBIT15   15

#define FLAG_TIM1       BIT0
#define FLAG_ESPDTA1    BIT1
#define FLAG_ESPDTA2    BIT2
#define FLAG_ESPDTA3    BIT3
#define FLAG_DTALOG     BIT4
#define FLAG_JSVALUE    BIT5
#define FLAG_JSCALIB    BIT6
#define FLAG_JSANALOG   BIT7
#define FLAG_ENDREADSS  BIT8
#define FLAG_ENBTASK    BIT9

#define SHIFT_FLAG_TIM1       SHIFTBIT0
#define SHIFT_FLAG_ESPDTA1    SHIFTBIT1
#define SHIFT_FLAG_ESPDTA2    SHIFTBIT2
#define SHIFT_FLAG_ESPDTA3    SHIFTBIT3
#define SHIFT_FLAG_DTALOG     SHIFTBIT4
#define SHIFT_FLAG_JSVALUE    SHIFTBIT5
#define SHIFT_FLAG_JSCALIB    SHIFTBIT6
#define SHIFT_FLAG_JSANALOG   SHIFTBIT7
#define SHIFT_FLAG_ENDREADSS  SHIFTBIT8
#define SHIFT_FLAG_ENBTASK    SHIFTBIT9

#define DEBUG_LOG_APP   BIT15
#define DEBUG_LOG_SD    BIT14
#define DEBUG_LOG_SS    BIT13
#define DEBUG_LOG_EEP   BIT12
#define DEBUG_LOG_JSON  BIT11
#define DEBUG_LOG_RTC   BIT10

#define DEBUG_LOG_MQTT  BIT2
#define DEBUG_LOG_OPT   BIT1
#define DEBUG_LOG_ALL   BIT0

#define SHIFT_DEBUG_LOG_APP   SHIFTBIT15
#define SHIFT_DEBUG_LOG_SD    SHIFTBIT14
#define SHIFT_DEBUG_LOG_SS    SHIFTBIT13
#define SHIFT_DEBUG_LOG_EEP   SHIFTBIT12
#define SHIFT_DEBUG_LOG_JSON  SHIFTBIT11
#define SHIFT_DEBUG_LOG_RTC   SHIFTBIT10

#define SHIFT_DEBUG_LOG_MQTT  SHIFTBIT2
#define SHIFT_DEBUG_LOG_OPT   SHIFTBIT1
#define SHIFT_DEBUG_LOG_ALL   SHIFTBIT0

#define SAVE_EN_IDLE        BIT0
#define SAVE_EN_POWERSAVE   BIT1
#define SAVE_EN_POWERDOWN   BIT2
#define SAVE_EN_STANDBY     BIT3
#define SAVE_EN_EXSTANDBY   BIT4

#define SHIFT_SAVE_EN_IDLE        SHIFTBIT0
#define SHIFT_SAVE_EN_POWERSAVE   SHIFTBIT1
#define SHIFT_SAVE_EN_POWERDOWN   SHIFTBIT2
#define SHIFT_SAVE_EN_STANDBY     SHIFTBIT3
#define SHIFT_SAVE_EN_EXSTANDBY   SHIFTBIT4

#define TIMESTATRT_TEMPERATURE  0
#define TIMEREAD1_TEMPERATURE   1
#define TIMEREAD2_TEMPERATURE   2
#define TIMEREAD3_TEMPERATURE   3

#define TIMESTATRT_SALINITY     4
#define TIMEREAD1_SALINITY      5
#define TIMEREAD2_SALINITY      6
#define TIMEREAD3_SALINITY      7

#define TIMESTATRT_PH           8
#define TIMEREAD1_PH            9
#define TIMEREAD2_PH            10
#define TIMEREAD3_PH            11

#define TIMESTATRT_NH4           12
#define TIMEREAD1_NH4            13
#define TIMEREAD2_NH4            14
#define TIMEREAD3_NH4            15

#define TIMESTATRT_DO            16
#define TIMEREAD1_DO             17
#define TIMEREAD2_DO             18
#define TIMEREAD3_DO             19

#define BITTATRT_TEMPERATURE   BIT0
#define BITREAD1_TEMPERATURE   BIT1
#define BITREAD2_TEMPERATURE   BIT2
#define BITREAD3_TEMPERATURE   BIT3

#define BITTATRT_SALINITY      BIT4
#define BITREAD1_SALINITY      BIT5
#define BITREAD2_SALINITY      BIT6
#define BITREAD3_SALINITY      BIT7

#define BITTATRT_PH            BIT8
#define BITREAD1_PH            BIT9
#define BITREAD2_PH            BIT10
#define BITREAD3_PH            BIT11

#define BITTATRT_NH4           BIT12
#define BITREAD1_NH4           BIT13
#define BITREAD2_NH4           BIT14
#define BITREAD3_NH4           BIT15

#define BITTATRT_DO            (BIT0 | BIT1)      // 3
#define BITREAD1_DO            (BIT0 | BIT2)      // 5
#define BITREAD2_DO            (BIT0 | BIT3)      // 9
#define BITREAD3_DO            (BIT0 | BIT4)      // 11

#define DEFAULT_VAL         0x00

#define ENABLE_BIT_FLAGTsGb(x)      FlagTsGb |= x
#define CLEAR_BIT_FLAGTsGb(x)       FlagTsGb &= ~x
#define CHECK_BIT_FLAGTsGb(x, y)    ((FlagTsGb & x) >> y)
#define CLEAR_ALLBIT_FLAGTsGb()     FlagTsGb = DEFAULT_VAL
#define ENABLE_ALLBIT_FLAGTsGb()    FlagTsGb = 0xFFFF

#define ENABLE_BIT_FLAGPoSSGb(x)      FlagPoSSGb |= x
#define CLEAR_BIT_FLAGPoSSGb(x)       FlagPoSSGb &= ~x
#define CHECK_BIT_FLAGPoSSGb(x)       FlagPoSSGb & x
#define CLEAR_ALLBIT_FLAGPoSSGb()     FlagPoSSGb = DEFAULT_VAL
#define ENABLE_ALLBIT_FLAGPoSSGb()    FlagPoSSGb = 0xFFFF

#define ENABLE_BIT_DebugArduino(x)      DebugArduino |= x
#define CLEAR_BIT_DebugArduino(x)       DebugArduino &= ~x
#define CHECK_BIT_DebugArduino(x, y)    ((DebugArduino & x) >> y)
#define CLEAR_ALLBIT_DebugArduino()     DebugArduino = DEFAULT_VAL
#define ENABLE_ALLBIT_DebugArduino()    DebugArduino = 0xFFFF

#define ENABLE_BIT_ErrorArduino(x)      ErrorArduino |= x
#define CLEAR_BIT_ErrorArduino(x)       ErrorArduino &= ~x
#define CHECK_BIT_ErrorArduino(x, y)    ((ErrorArduino & x) >> y)
#define CLEAR_ALLBIT_ErrorArduino()     ErrorArduino = DEFAULT_VAL
#define ENABLE_ALLBIT_ErrorArduino()    ErrorArduino = 0xFFFF

#define ENABLE_BIT_SaveEnArduino(x)      SaveEnArduino |= x
#define CLEAR_BIT_SaveEnArduino(x)       SaveEnArduino &= ~x
#define CHECK_BIT_SaveEnArduino(x, y)    ((SaveEnArduino & x) >> y)
#define CLEAR_ALLBIT_SaveEnArduino()     SaveEnArduino = DEFAULT_VAL
#define ENABLE_ALLBIT_SaveEnArduino()    SaveEnArduino = 0xFFFF

/* xem them cac bien:
- gia tri analog
- gia tri on/off
- 
 */

/* ton tai nguyen:
+ 106 byte cho sd card
+ 212 byte json khoi tao 
+ 
 */

// mang chua thoi gian thuc hien
// flag de quan li chu trinh thuc hien polling
// flag canh bao neu can


#endif
