#include "app.h"

uint16 TimeLine;
uint8 RTC_Time[7];

void TIMER1_Init()
{
    cli();                        // disable all interrupts
    TCCR1A = 0x00;                // WGM11 = 0; WGM10 = 0;
    TCCR1B = 0x00;                // WGM12 = 0; WGM13 = 0;
    TCNT1 = 3035;                 // preload timer 65536-16MHz/256/1Hz <=> (65535 - 1s.16Mhz/256)
    TCCR1B |= (1 << CS12);        // 256 prescaler
    TIMER1MSK_ON();               // enable timer overflow interrupt
    sei();                        // enable all interrupts
}

void TIMER2_Init()  // 1ms to interupt
{
    TCCR2A = 0;     //Reset Timer2
    TCCR2B = 0;      
    TIMSK2 = 0;
    //Setup Timer2
    TCCR2B |= (1 << CS22) ;   //Chọn prescaler 1024 CS22=1,CS21=1, CS20=1 xem bảng phía trên
    TCNT2 = 230;              //Giá trị tính toán phía trên
    TIMSK2 |= (1 << TOIE2);   //Overflow interrupt enable
    sei();                    //Cho phép ngắt toàn cục
}

void DataLoger2SDCard(uint8 WhData)
{
    String  TimeSave  = RTC_DS3231_ReadTime_String(RTC_Time);
    String  DirFolder = "DATALOG/YEAR" + (String)RTC_Time[year] + "/MONTH_" + (String)RTC_Time[month];
    String  SaveFile  = DirFolder + "/DATE_" + (String)RTC_Time[date] + ".txt";
    String  Title     = "Temperature,Salinity,PH,NH4,DO\r\n";
    String  comma     = ",";
    String  DataSave  = Value_Sensor[TEMP] + comma + 
                        Value_Sensor[SAL]  + comma + 
                        Value_Sensor[PH]   + comma + 
                        Value_Sensor[NH4]  + comma + 
                        Value_Sensor[DO]   + comma + 
                        TimeSave + DOWLN;
    DB_LOG(MODULE_APP, "DATALOGER SAVE AT: " + SaveFile);

    String DataSave2SD = "";
    if (WhData == NEWDAY)
        DataSave2SD = Title;
    if (WhData == NORMALDAY)
        DataSave2SD = DataSave;
    if (!SD.exists(DirFolder))
        SDCARD_CreateFolder_bool(DirFolder);
    SDCARD_WriteFile_String(SaveFile, DataSave2SD);
}

void Json_Parse_void(char DataParse[], uint8 FlagReset)
{
    String output;
    StaticJsonDocument <256> doc;
    deserializeJson(doc, DataParse);

    uint8 JsonTask = doc["task"];
    uint8 JsonStationID = doc["ClientID"];

    if(JsonStationID == StationIOT)
    {
        if(JsonTask == JSON_NUMERIC_ByServer)                   // reuest read config available in local
        {
            uint8_t numeric = doc["numeric"];
            SHOWLN("Numeric configuration is: " + (String)numeric);
            if( (1 <= numeric) && (numeric <= 5))
            {
                String DataRead = SDCARD_ReadFileCfg_String(numeric);
                DB_LOG(MODULE_APP,  "Data response>>> " + DataRead + DOWLN);
                ESPD1MINI.print(DataRead);
            }
            else
            {
                String Data_Calib_Now = Json_CreateCalib_String(Calibration);
                ESPD1_SEND(Data_Calib_Now);
            }
        }
        else if(JsonTask == JSON_CALIB_ByServer)                // request apply new calibration + reset board
        {
            uint8 NumCfg               = doc["config"];
            Calibration[SAL_Intercept] = doc["SAL"][0];
            Calibration[SAL_Slope]     = doc["SAL"][1];
            Calibration[PH_Intercept]  = doc["PH"][0];
            Calibration[PH_Slope]      = doc["PH"][1];
            Calibration[NH4_Eo]        = doc["NH4"][0];
            Calibration[NH4_m]         = doc["NH4"][1];
            Calibration[DO_Intercept]  = doc["OXI"][0];
            Calibration[DO_Slope]      = doc["OXI"][1];

            if( (FlagReset == RESETBOARD) || (NumCfg == NONE) )
            {
                TIMER1MSK_OFF();
                serializeJson(doc, output);
                EEPROM_Write_void(EEPROM_ADDRESS, NumCfg);
                SDCARD_SaveConfigFile_uint8(NumCfg, output);
                DB_LOG(MODULE_APP,  "output:  " + output + DOWLN);
                Serial.println(F("Reset to apply new Calibration...."));
                delay(10000);
            }
        }
        else if(JsonTask == JSON_TASK_ARDUINORESET)             // request reset board by user
        {
            Serial.println(F("Arduino will reset NOW \n\n"));
            TIMER1MSK_OFF();
            delay(10000);
        }
    } //end JsonStationID
    else
    {
        DB_LOG(MODULE_APP, "StationID no Suitable \r\n");
        DB_LOG(MODULE_APP, "StationID now is (" + (String)StationIOT + ") but StationID request is (" + (String)JsonStationID + ") \r\n");
    }

}

void Calibration_Init_void()
{
    char   CData[256];
    uint8  conf = EEPROM_Read_uint8(EEPROM_ADDRESS);
    String Data = SDCARD_ReadFileCfg_String(conf);
    if(Data)
        ESPD1_SEND(Data);

    if (0 < conf && conf <= 5)
    {
        strcpy(CData, Data.c_str());
        Json_Parse_void(CData, NONE);
        DB_LOG(MODULE_APP, (String)"Calibration now "
        + "SAL_Intercept: " + (String)Calibration[SAL_Intercept]  + " SAL_Slope:" + (String)Calibration[SAL_Slope] 
        + " PH_Intercept:"  + (String)Calibration[PH_Intercept]   + " PH_Slope:"  + (String)Calibration[PH_Slope] 
        + " Eo:"            + (String)Calibration[NH4_Eo]         + " m:"         + (String)Calibration[NH4_m] 
        + " DO_Intercept:"  + (String)Calibration[DO_Intercept]   + " DO_Slope:"  + (String)Calibration[DO_Slope]);
    }
    else
    {
        DB_LOG(MODULE_APP, (String)"Use calib default "
        + "SAL_Intercept: " + (String)Calibration[SAL_Intercept]  + " SAL_Slope:" + (String)Calibration[SAL_Slope] 
        + " PH_Intercept:"  + (String)Calibration[PH_Intercept]   + " PH_Slope:"  + (String)Calibration[PH_Slope] 
        + " Eo:"            + (String)Calibration[NH4_Eo]         + " m:"         + (String)Calibration[NH4_m] 
        + " DO_Intercept:"  + (String)Calibration[DO_Intercept]   + " DO_Slope:"  + (String)Calibration[DO_Slope]);
    }
}

void TIM1_POLL_void()
{
    static uint16 TimeWait;
    if( CHECK_BIT_FLAGTsGb(FLAG_ENDREADSS, SHIFT_FLAG_ENDREADSS) )
    {
        TimeWait = TimeLine;
        CLEAR_BIT_FLAGTsGb(FLAG_ENDREADSS);
        ENABLE_BIT_FLAGTsGb(FLAG_ENBTASK);
    }

    Sensor_AnalogRead_void(TEMP, TimeLine);
    Sensor_AnalogRead_void(SAL, TimeLine);
    Sensor_AnalogRead_void(PH, TimeLine);
    Sensor_AnalogRead_void(NH4, TimeLine);
    Sensor_AnalogRead_void(DO, TimeLine);

    if( CHECK_BIT_FLAGTsGb(FLAG_ENBTASK, SHIFT_FLAG_ENBTASK) )
    {
        if( (TimeLine - TimeWait) == 50 )
        {
            TimeLine = 0;
            CLEAR_BIT_FLAGTsGb(FLAG_ENBTASK);
        }

        else if( (TimeLine - TimeWait) == 5)
            ENABLE_BIT_FLAGTsGb(FLAG_DTALOG);
        else if( (TimeLine - TimeWait) == 10)
            ENABLE_BIT_FLAGTsGb(FLAG_JSANALOG);
        else if( (TimeLine - TimeWait) == 15)
            ENABLE_BIT_FLAGTsGb(FLAG_JSVALUE);
        else if( (TimeLine - TimeWait) == 16)
            ENABLE_BIT_SaveEnArduino(SAVE_EN_IDLE);
        

    } // End FLAG_ENTASK
} // End TIM1_POLL_void
