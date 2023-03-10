#include "sensor.h"

uint16 FlagTsGb   = DEFAULT_VAL;       // Flag Task global
uint16 FlagPoSSGb = DEFAULT_VAL;       // Flag POLL sensor global
uint8  MNTimeSS[19];              // manage time of sensor

uint8    Relay_Sensor[6];
uint8    Analog_Sensor[6];
uint16   Analog_Read[16];
float    Value_Sensor[6];
float    Calibration[8] = {0.0, 16.3, 12.32, -3.838, 252.72, -7.59, -0.444, 0.444};
boolean  ON   =   HIGH;
boolean  OFF  =   LOW;

void Board_Init_void(uint8 board)
{
  String BoardIot = "";
  if (board == NEWBOARD) {
    BoardIot            = "NEWBOARD";
    Relay_Sensor[TEMP]  = GPIO_PIN_12;
    Relay_Sensor[SAL]   = GPIO_PIN_11;
    Relay_Sensor[PH]    = GPIO_PIN_10;
    Relay_Sensor[NH4]   = GPIO_PIN_9;
    Relay_Sensor[DO]    = GPIO_PIN_4;
    Relay_Sensor[NO3]   = GPIO_PIN_45;

    Analog_Sensor[TEMP] = ANALOG_PIN_A0;
    Analog_Sensor[SAL]  = ANALOG_PIN_A1;
    Analog_Sensor[PH]   = ANALOG_PIN_A2 ;
    Analog_Sensor[NH4]  = ANALOG_PIN_A3;
    Analog_Sensor[DO]   = ANALOG_PIN_A4;
    Analog_Sensor[NO3]  = ANALOG_PIN_A5;
  }
  if (board == OLDBOARD) {
    BoardIot            = "OLDBOARD";
    ON  = LOW;
    OFF = HIGH;
    Relay_Sensor[TEMP]  = GPIO_PIN_7;
    Relay_Sensor[SAL]   = GPIO_PIN_12;
    Relay_Sensor[PH]    = GPIO_PIN_11;
    Relay_Sensor[NH4]   = GPIO_PIN_10;
    Relay_Sensor[DO]    = GPIO_PIN_9;
    Relay_Sensor[NO3]   = GPIO_PIN_8;

    Analog_Sensor[TEMP] = ANALOG_PIN_A1;
    Analog_Sensor[SAL]  = ANALOG_PIN_A0;
    Analog_Sensor[PH]   = ANALOG_PIN_A3 ;
    Analog_Sensor[NH4]  = ANALOG_PIN_A4;
    Analog_Sensor[DO]   = ANALOG_PIN_A5;
    Analog_Sensor[NO3]  = ANALOG_PIN_A2;
  }
  DB_LOG(MODULE_SENSOR, "Your Pin is Set: " + BoardIot + DOWLN);
}

void Board_SetPinOut_void(boolean StatusPin)
{
    pinMode(Relay_Sensor[TEMP], OUTPUT);
    pinMode(Relay_Sensor[SAL],  OUTPUT);
    pinMode(Relay_Sensor[PH],   OUTPUT);
    pinMode(Relay_Sensor[NH4],  OUTPUT);
    pinMode(Relay_Sensor[DO],   OUTPUT);
    pinMode(Relay_Sensor[NO3],  OUTPUT);

    digitalWrite(Relay_Sensor[TEMP], StatusPin);
    digitalWrite(Relay_Sensor[SAL],  StatusPin);
    digitalWrite(Relay_Sensor[PH],   StatusPin);
    digitalWrite(Relay_Sensor[NH4],  StatusPin);
    digitalWrite(Relay_Sensor[DO],   StatusPin);
    digitalWrite(Relay_Sensor[NO3],  StatusPin);
}

void Sensor_Init_void(uint8 Board)
{
    MNTimeSS[TIMESTATRT_TEMPERATURE] = TIME10S;          // Start at senconds 10th
    MNTimeSS[TIMEREAD1_TEMPERATURE]  = MNTimeSS[TIMESTATRT_TEMPERATURE] + WarmUpTEMP;
    MNTimeSS[TIMEREAD2_TEMPERATURE]  = MNTimeSS[TIMEREAD1_TEMPERATURE] + TimeReadAnalog;
    MNTimeSS[TIMEREAD3_TEMPERATURE]  = MNTimeSS[TIMEREAD2_TEMPERATURE] + TimeReadAnalog;

    MNTimeSS[TIMESTATRT_SALINITY] = MNTimeSS[TIMEREAD3_TEMPERATURE] + TimeBWT_SENSOR;          // Start at senconds ....
    MNTimeSS[TIMEREAD1_SALINITY]  = MNTimeSS[TIMESTATRT_SALINITY] + WarmUpSAL;
    MNTimeSS[TIMEREAD2_SALINITY]  = MNTimeSS[TIMEREAD1_SALINITY] + TimeReadAnalog;
    MNTimeSS[TIMEREAD3_SALINITY]  = MNTimeSS[TIMEREAD2_SALINITY] + TimeReadAnalog;

    MNTimeSS[TIMESTATRT_PH] = MNTimeSS[TIMEREAD3_SALINITY] + TimeBWT_SENSOR;          // Start at senconds 
    MNTimeSS[TIMEREAD1_PH]  = MNTimeSS[TIMESTATRT_PH] + WarmUpPH;
    MNTimeSS[TIMEREAD2_PH]  = MNTimeSS[TIMEREAD1_PH] + TimeReadAnalog;
    MNTimeSS[TIMEREAD3_PH]  = MNTimeSS[TIMEREAD2_PH] + TimeReadAnalog;

    MNTimeSS[TIMESTATRT_NH4] = MNTimeSS[TIMEREAD3_PH] + TimeBWT_SENSOR;          // Start at senconds 
    MNTimeSS[TIMEREAD1_NH4]  = MNTimeSS[TIMESTATRT_NH4] + WarmUpNH4;
    MNTimeSS[TIMEREAD2_NH4]  = MNTimeSS[TIMEREAD1_NH4] + TimeReadAnalog;
    MNTimeSS[TIMEREAD3_NH4]  = MNTimeSS[TIMEREAD2_NH4] + TimeReadAnalog;

    MNTimeSS[TIMESTATRT_DO]  = MNTimeSS[TIMEREAD3_NH4] + TimeBWT_SENSOR;          // Start at senconds 
    MNTimeSS[TIMEREAD1_DO]   = MNTimeSS[TIMESTATRT_DO] + WarmUpDO;
    MNTimeSS[TIMEREAD2_DO]   = MNTimeSS[TIMEREAD1_DO] + TimeReadAnalog;
    MNTimeSS[TIMEREAD3_DO]   = MNTimeSS[TIMEREAD2_DO] + TimeReadAnalog;
    
    Serial.println( String("Time to start read sensor (senconds)")    +
            " TEMP:"    + (String)(MNTimeSS[TIMESTATRT_TEMPERATURE])  + "->" + (String)(MNTimeSS[TIMEREAD3_TEMPERATURE]) + 
            " SAL:"     + (String)(MNTimeSS[TIMESTATRT_SALINITY])     + "->" + (String)(MNTimeSS[TIMEREAD3_SALINITY]) + 
            " PH:"      + (String)(MNTimeSS[TIMESTATRT_PH])           + "->" + (String)(MNTimeSS[TIMEREAD3_PH]) + 
            " NH4:"     + (String)(MNTimeSS[TIMESTATRT_NH4])          + "->" + (String)(MNTimeSS[TIMEREAD3_NH4]) +
            " DO:"     + (String)(MNTimeSS[TIMESTATRT_DO])             + "->" + (String)(MNTimeSS[TIMEREAD3_DO]) +
            " TimeBWT:" + (String)TimeBWT_SENSOR );

    FlagPoSSGb  =   BITTATRT_TEMPERATURE | BITREAD1_TEMPERATURE | BITREAD2_TEMPERATURE | BITREAD3_TEMPERATURE |
                    BITTATRT_SALINITY | BITREAD1_SALINITY | BITREAD2_SALINITY | BITREAD3_SALINITY |
                    BITTATRT_PH | BITREAD1_PH | BITREAD2_PH | BITREAD3_PH |
                    BITTATRT_NH4 | BITREAD1_NH4 | BITREAD2_NH4 | BITREAD3_NH4 |
                    BITTATRT_DO | BITREAD1_DO | BITREAD2_DO | BITREAD3_DO    ;
    Serial.print("Flag of Read Sensor: 0x");    Serial.println(FlagPoSSGb, HEX);      ENDLN
}

String Sensor_Identify_String(uint8 Name)
{
    if (Name == TEMP)
        return "Temperature";
    if (Name == SAL)
        return "Salinity";
    if (Name == PH)
        return "PH Sensor";
    if (Name == NH4)
        return "NH4 Sensor";
    if (Name == DO)
        return "OXI Sensor";
}

void Board_PowerONSensor_void(uint8 Pin, uint8 Name)
{
    String NameSensor = Sensor_Identify_String(Name);
    DB_LOG(MODULE_SENSOR, "Start read sensor ...." + NameSensor + DOWLN);
    digitalWrite(Pin, ON);
}

void Board_PowerOFFSensor_void(uint8 Pin, uint8 Name)
{
    String NameSensor = Sensor_Identify_String(Name);
    DB_LOG(MODULE_SENSOR, "End read sensor...." + NameSensor + DOWLN);
    digitalWrite(Pin, OFF);
}

float Sensor_ReadAnalog_float(uint8 Pin_Sensor)
{
    uint16 AnalogRead_Value = analogRead(Pin_Sensor);
    DB_LOG(MODULE_SENSOR, "Analog Value: " + (String)AnalogRead_Value + DOWLN);
    return AnalogRead_Value;
}

float Analog2Voltage(uint16 AnalogValue) {
    float Voltage = VOLTAGE_REF * (AnalogValue / NumberTimes_ReadAnalog) / 1023; ; //convert average count to voltage (0 to 5 volt input)
    return Voltage;
}

float Sensor_IDValue_float(const uint8 Name, const uint16 AnalogRead_Value)
{
    float value_sensor = 0;
    if (Name == TEMP)
        value_sensor = Sensor_TemperatureGet_float(AnalogRead_Value);
    else if (Name == SAL)
        value_sensor = Sensor_SalinityGet_float(AnalogRead_Value);
    else if (Name == PH)
        value_sensor = Sensor_PhGet_float(AnalogRead_Value);
    else if (Name == NH4)
        value_sensor = Sensor_Nh4Get_float(AnalogRead_Value);
    else if (Name == DO)
        value_sensor = Sensor_DoGet_float(AnalogRead_Value);
    return value_sensor;
}

float Sensor_TemperatureGet_float(uint16 AnalogValue_Temp)
{
    long  Resistance;
    float Resistor = 15000;
    float Temp;
    float Raw = AnalogValue_Temp / NumberTimes_ReadAnalog;

    Resistance = ( Resistor * Raw / (1024 - Raw));
    Temp = log(Resistance);                             // Saving the Log(resistance) so not to calculate  it 4 times later
    Temp = 1 / (0.00102119 + (0.000222468 * Temp) + (0.000000133342 * Temp * Temp * Temp));
    Temp = Temp - 273.15;                               // Convert Kelvin to Celsius
    DB_LOG(MODULE_SENSOR, "Temperature: " + (String)Temp  + DOWLN);
    return Temp;                                        // Return the Temperature
}

float Sensor_SalinityGet_float(uint16 AnalogValue_Sal)
{
    float SAL_Voltage =  Analog2Voltage(AnalogValue_Sal);
    float SALinity_value = Calibration[SAL_Intercept] + SAL_Voltage * Calibration[SAL_Slope];
    if (SALinity_value < 0.0)
        SALinity_value = 0.0;
    DB_LOG(MODULE_SENSOR, "SAL: " + (String)SALinity_value + DOWLN);
    return SALinity_value;
}

float Sensor_PhGet_float(uint16 AnalogValue_Ph)
{
    float PH_Voltage =  Analog2Voltage(AnalogValue_Ph);
    float PH_Value = Calibration[PH_Intercept] + PH_Voltage * Calibration[PH_Slope];
    DB_LOG(MODULE_SENSOR, "PH: " + (String)PH_Value + DOWLN);

    if (PH_Value >= 14)
        PH_Value = PH_Value - 2.5;
    if (PH_Value < 0)
        PH_Value = 0.0;
    DB_LOG(MODULE_SENSOR, "PH: " + (String)PH_Value + DOWLN);
    return PH_Value;
}

float Sensor_Nh4Get_float(uint16 AnalogValue_Nh4)
{
    float NH4_Voltage =  Analog2Voltage(AnalogValue_Nh4);
    float ElectrodeReading = 137.55 * NH4_Voltage - 0.1682;                                     // converts raw voltage to mV from electrode
    double(val) = ((ElectrodeReading - Calibration[NH4_Eo]) / Calibration[NH4_m]);              // calculates the value to be entered into exp func.
    double NH4_value = exp(val) / 1000;                                                         // converts mV value to concentration
    DB_LOG(MODULE_SENSOR, "NH4: " + (String)NH4_value);

    NH4_value = NH4_value + 0.1 * random(8);
    if (NH4_value < 0) NH4_value = 0.0;
    DB_LOG(MODULE_SENSOR, "NH4: " + (String)NH4_value + DOWLN);
    return NH4_value;
}

float Sensor_DoGet_float(uint16 AnalogValue_DO)
{
    float DO_Voltage =  Analog2Voltage(AnalogValue_DO);
    float DO_Value = Calibration[DO_Intercept] + DO_Voltage * Calibration[DO_Slope];
    DB_LOG(MODULE_SENSOR, "DO: " + (String)DO_Value + DOWLN);

    if (DO_Value > 11)
        DO_Value = DO_Value - 3.0;
    if (DO_Value <= 0)
        DO_Value = 0.0 + 1.0 + 0.1 * random(5);
    DB_LOG(MODULE_SENSOR, "DO: " + (String)DO_Value + DOWLN);
    delay(50);
    return DO_Value;
}

// void Sensor_ReadValue_void(uint8 IDSensor, uint16 TimeRead_Sensor, uint16 warmup_time, const uint16 TimeLine)
// {
//     if (TimeLine == TimeRead_Sensor)
//         Board_PowerONSensor_void(Relay_Sensor[IDSensor], IDSensor);
//     else if (TimeLine == (TimeRead_Sensor + warmup_time + TIMES1READ_ANALOG) )
//         Analog_Read[IDSensor*3+1] = Sensor_ReadAnalog_float(Analog_Sensor[IDSensor]);
//     else if (TimeLine == (TimeRead_Sensor + warmup_time + TIMES2READ_ANALOG) )
//         Analog_Read[IDSensor*3+2] = Sensor_ReadAnalog_float(Analog_Sensor[IDSensor]);
//     else if (TimeLine == (TimeRead_Sensor + warmup_time + TIMES3READ_ANALOG) )
//     {
//         Analog_Read[IDSensor*3+3] = Sensor_ReadAnalog_float(Analog_Sensor[IDSensor]);
//         uint16 AnalogAVR = (Analog_Read[IDSensor*3+1] + Analog_Read[IDSensor*3+2] + Analog_Read[IDSensor*3+3]) / NumberTimes_ReadAnalog;
//         Value_Sensor[IDSensor]  = Sensor_IDValue_float(IDSensor, AnalogAVR);
//         Board_PowerOFFSensor_void(Relay_Sensor[IDSensor], IDSensor);
//     }
// }

void Sensor_AnalogRead_void(uint8 SensorID, uint16 TimeLine)
{
    uint8 MulPosSS = 0;
    uint16 Sensor_Bit[4];
    switch (SensorID)
    {
    case TEMP:
        Sensor_Bit[0]    = BITTATRT_TEMPERATURE;
        Sensor_Bit[1]    = BITREAD1_TEMPERATURE;
        Sensor_Bit[2]    = BITREAD2_TEMPERATURE;
        Sensor_Bit[3]    = BITREAD3_TEMPERATURE;
        break;
    case SAL:
        Sensor_Bit[0]    = BITTATRT_SALINITY;
        Sensor_Bit[1]    = BITREAD1_SALINITY;
        Sensor_Bit[2]    = BITREAD2_SALINITY;
        Sensor_Bit[3]    = BITREAD3_SALINITY;
        break;
    case PH:
        Sensor_Bit[0]    = BITTATRT_PH;
        Sensor_Bit[1]    = BITREAD1_PH;
        Sensor_Bit[2]    = BITREAD2_PH;
        Sensor_Bit[3]    = BITREAD3_PH;
        break;
    case NH4:
        Sensor_Bit[0]    = BITTATRT_NH4;
        Sensor_Bit[1]    = BITREAD1_NH4;
        Sensor_Bit[2]    = BITREAD2_NH4;
        Sensor_Bit[3]    = BITREAD3_NH4;
    case DO:
        Sensor_Bit[0]    = BITTATRT_DO;
        Sensor_Bit[1]    = BITREAD1_DO;
        Sensor_Bit[2]    = BITREAD2_DO;
        Sensor_Bit[3]    = BITREAD3_DO;
        break;
    default:
        break;
    }

    /* identify multiple position sensor */
    if( SensorID == TEMP )
        MulPosSS = 1;
    else if( (SensorID == SAL) || (SensorID == PH) || (SensorID == NH4) || (SensorID == DO) )
        MulPosSS = 4;

    if( (CHECK_BIT_FLAGPoSSGb(Sensor_Bit[0]) != 0) && (MNTimeSS[SensorID*MulPosSS + 0]  == TimeLine) )
    {
        Board_PowerONSensor_void(Relay_Sensor[SensorID], SensorID);
    }
    else if( (CHECK_BIT_FLAGPoSSGb(Sensor_Bit[1]) != 0) && (MNTimeSS[SensorID*MulPosSS + 1] == TimeLine) )
    {
        Analog_Read[SensorID*3+1] = Sensor_ReadAnalog_float(Analog_Sensor[SensorID]);
    }
    else if( (CHECK_BIT_FLAGPoSSGb(Sensor_Bit[2]) != 0) && (MNTimeSS[SensorID*MulPosSS + 2] == TimeLine) )
    {
        Analog_Read[SensorID*3+2] = Sensor_ReadAnalog_float(Analog_Sensor[SensorID]);
    }
    else if( (CHECK_BIT_FLAGPoSSGb(Sensor_Bit[3]) != 0) && (MNTimeSS[SensorID*MulPosSS + 3] == TimeLine) )
    {
        Analog_Read[SensorID*3+3] = Sensor_ReadAnalog_float(Analog_Sensor[SensorID]);

        uint16 AnalogAVR = (Analog_Read[SensorID*3+1] + Analog_Read[SensorID*3+2] + Analog_Read[SensorID*3+3]) / NumberTimes_ReadAnalog;
        Value_Sensor[SensorID]  = (float)Sensor_IDValue_float(SensorID, AnalogAVR);
        Board_PowerOFFSensor_void(Relay_Sensor[SensorID], SensorID);
        ENDLN
    }
    if( (SensorID == DO) && ((MNTimeSS[SensorID*MulPosSS + 3] == TimeLine)) )
        ENABLE_BIT_FLAGTsGb(FLAG_ENDREADSS);

}
