
#include "JSON.h"

/*******************************************************************************
* @FunctionName:    String Json_CreateCalib_String                                    
* @Description:     create json: calibration json
* @Param:           float *Caliration    
* @Return:          String                                                       
*******************************************************************************/
String Json_CreateCalib_String(float *Calib)
{
    String output;
    char jsondata[1];
    StaticJsonDocument <256> doc;
    deserializeJson(doc, jsondata);

    doc["config"]   = EEPROM.read(EEPROM_ADDRESS);
    doc["SAL"][0]   = Calib[SAL_Intercept];
    doc["SAL"][1]   = Calib[SAL_Slope];
    doc["PH"][0]    = Calib[PH_Intercept];
    doc["PH"][1]    = Calib[PH_Slope];
    doc["NH4"][0]   = Calib[NH4_Eo];
    doc["NH4"][1]   = Calib[NH4_m];
    doc["OXI"][0]   = Calib[DO_Intercept];
    doc["OXI"][1]   = Calib[DO_Slope];
    doc["clientID"]     = StationIOT;
    doc["task"]         = JSON_TASK_CALIB;
    serializeJson(doc, output);
    DB_LOG(MODULE_JSON, "JS created CALIB: " + output + DOWLN);
    
    return output;
}

/*******************************************************************************
* @FunctionName:    String Json_CreateValue_String                                    
* @Description:     create json: value json
* @Param:           float *Value_Sensor    
* @Return:          String                                                       
*******************************************************************************/
String Json_CreateValue_String(float *Value)
{
    String output;
    char jsondata[1];
    StaticJsonDocument <256> doc;
    deserializeJson(doc, jsondata);

    doc["TEMP_Value"]  = Value[TEMP];
    doc["SAL_Value"]   = Value[SAL];
    doc["PH_Value"]    = Value[PH];
    doc["NH4_Value"]   = Value[NH4];
    doc["DO_Value"]    = Value[DO];
    doc["clientID"]    = StationIOT;
    doc["task"]        = JSON_TASK_VALUE;
    serializeJson(doc, output);
    DB_LOG(MODULE_JSON, "JS created VALUE: " + output + DOWLN);

    return output;  
}

String Json_CreateAnalog_String(uint8_t request, uint16 *Analog)
{
    String output;
    char jsondata[1];
    StaticJsonDocument <256> doc;
    deserializeJson(doc, jsondata);

    if (request == JSON_ANALOG_byClient)
    {
        doc["TEMP_Analog"] = (Analog[TEMP*3+1] + Analog[TEMP*3+2] + Analog[TEMP*3+3]) / NumberTimes_ReadAnalog;
        doc["SAL_Analog"]  = (Analog[SAL*3+1]  + Analog[SAL*3+2]  + Analog[SAL*3+3])  / NumberTimes_ReadAnalog;
        doc["PH_Analog"]   = (Analog[PH*3+1]   + Analog[PH*3+2]   + Analog[PH*3+3])   / NumberTimes_ReadAnalog;
        doc["NH4_Analog"]  = (Analog[NH4*3+1]  + Analog[NH4*3+2]  + Analog[NH4*3+3])  / NumberTimes_ReadAnalog;
        doc["OXI_Analog"]  = (Analog[DO*3+1]   + Analog[DO*3+2]   + Analog[DO*3+3])   / NumberTimes_ReadAnalog;
        doc["clientID"]     = StationIOT;
        doc["task"]         = JSON_TASK_ANALOG_SINGLE;
        serializeJson(doc, output);
        DB_LOG(MODULE_JSON, "JS created ANALOG: " + output + DOWLN);
    }
    else if(request == JSON_ANAOG_DETAIL_byClient)
    {
        doc["TEMP"][0]  = Analog[1];
        doc["TEMP"][1]  = Analog[2];
        doc["TEMP"][2]  = Analog[3];
        doc["SAL"][0]   = Analog[4];
        doc["SAL"][1]   = Analog[5];
        doc["SAL"][2]   = Analog[6];
        doc["PH"][0]    = Analog[7];
        doc["PH"][1]    = Analog[8];
        doc["PH"][2]    = Analog[9];
        doc["NH4"][0]   = Analog[10];
        doc["NH4"][1]   = Analog[11];
        doc["NH4"][2]   = Analog[12];
        doc["OXI"][0]   = Analog[13];
        doc["OXI"][1]   = Analog[14];
        doc["OXI"][2]   = Analog[15];
        doc["clientID"] = StationIOT;
        doc["task"]     = JSON_TASK_ANALOG_DETAL;
        serializeJson(doc, output);
        DB_LOG(MODULE_JSON, "JS created ANALOG_DETAIL: " + output + DOWLN);
    }
    return output;
}

String Json_CreateRelayPIN_String(uint8 *pin)
{
    String output;
    char jsondata[1];
    StaticJsonDocument <256> doc;
    deserializeJson(doc, jsondata);

    doc["TEMP_Relay"] = pin[TEMP];
    doc["SAL_Relay"]  = pin[SAL];
    doc["PH_Relay"]   = pin[PH];
    doc["NH4_Relay"]  = pin[NH4];
    doc["DO_Relay"]   = pin[DO];
    doc["clientID"]   = StationIOT;
    doc["task"]       = JSON_TASK_RELAYPIN;
    serializeJson(doc, output);
    DB_LOG(MODULE_JSON, "JS created REALY PIN: " + output + DOWLN);
}

String Json_CreateAnalogPIN_String(uint8 *pin)
{
    String output;
    char jsondata[1];
    StaticJsonDocument <256> doc;
    deserializeJson(doc, jsondata);

    doc["TEMP_AnalogPIN"] = pin[TEMP];
    doc["SAL_AnalogPIN"]  = pin[SAL];
    doc["PH_AnalogPIN"]   = pin[PH];
    doc["NH4_AnalogPIN"]  = pin[NH4];
    doc["DO_AnalogPIN"]   = pin[DO];
    doc["clientID"]       = StationIOT;
    doc["task"]           = JSON_TASK_ANALOGPIN;
    serializeJson(doc, output);
    DB_LOG(MODULE_JSON, "JS created ANALOG PIN: " + output + DOWLN);
}
