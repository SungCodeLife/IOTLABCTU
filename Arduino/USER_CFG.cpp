#include "USER_CFG.h"

uint16 SaveEnArduino = DEFAULT;
uint16 ErrorArduino  = DEFAULT;
uint16 DebugArduino  = DEFAULT;
uint8  StationIOT    = NONE;

void DB_LOG(uint8 module, String str)
{
    if (CHECK_BIT_DebugArduino(DEBUG_LOG_ALL, SHIFT_DEBUG_LOG_ALL))
    {
        if( CHECK_BIT_DebugArduino(DEBUG_LOG_MQTT, SHIFT_DEBUG_LOG_MQTT) )
        {
            Serial.println("Debug By MQTT");
            ESPD1_SEND(str);
            // delay(500);
        }

        if(CHECK_BIT_DebugArduino(DEBUG_LOG_OPT, SHIFT_DEBUG_LOG_OPT))
        {
            if( (module == MODULE_APP) && (CHECK_BIT_DebugArduino(DEBUG_LOG_APP, SHIFT_DEBUG_LOG_APP) ))
            {
                Serial.print(F("APP: "));
                Serial.print(str);
            }
            else if( (module == MODULE_SD) && (CHECK_BIT_DebugArduino(DEBUG_LOG_SD, SHIFT_DEBUG_LOG_SD) ))
            {
                Serial.print(F("SD: "));
                Serial.print(str);
            }
            else if( (module == MODULE_SENSOR) && (CHECK_BIT_DebugArduino(DEBUG_LOG_SS, SHIFT_DEBUG_LOG_SS) ))
            {
                Serial.print(F("SS: "));
                Serial.print(str);
            }
            else if( (module == MODULE_EEP) && (CHECK_BIT_DebugArduino(DEBUG_LOG_EEP, SHIFT_DEBUG_LOG_EEP) ))
            {
                Serial.print(F("EEP: "));
                Serial.print(str);
            }
            else if( (module == MODULE_JSON) && (CHECK_BIT_DebugArduino(DEBUG_LOG_JSON, SHIFT_DEBUG_LOG_JSON) ))
            {
                Serial.print(F("JSON: "));
                Serial.print(str);
            }
            else if( (module == MODULE_RTC) && (CHECK_BIT_DebugArduino(DEBUG_LOG_RTC, SHIFT_DEBUG_LOG_RTC) ))
            {
                Serial.print(F("RTC: "));
                Serial.print(str);
            }
        }
    } // end if
    
}

void IOT_ENV_Init()
{
    StationIOT = IOT_STATION_TEST;
    CLEAR_ALLBIT_DebugArduino();
    ENABLE_BIT_DebugArduino(DEBUG_LOG_ALL);
    ENABLE_BIT_DebugArduino(DEBUG_LOG_OPT);
    ENABLE_BIT_DebugArduino(DEBUG_LOG_APP);
    ENABLE_BIT_DebugArduino(DEBUG_LOG_SS);
    ENABLE_BIT_DebugArduino(DEBUG_LOG_SD);
    ENABLE_BIT_DebugArduino(DEBUG_LOG_JSON);
    ENABLE_BIT_DebugArduino(DEBUG_LOG_EEP);
    // ENABLE_BIT_DebugArduino(DEBUG_LOG_MQTT);
    // ENABLE_ALLBIT_DebugArduino();
    // CLEAR_BIT_DebugArduino(DEBUG_LOG_RTC);
    // CLEAR_BIT_DebugArduino(DEBUG_LOG_APP);
    Serial.print(F("DEUG LOG BIN: "));     Serial.println(DebugArduino, BIN);
}
