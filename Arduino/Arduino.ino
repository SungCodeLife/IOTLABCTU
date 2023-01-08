#include "app.h"
#undef F_CPU
#define F_CPU 8000000

// variable declare
char  Data1[200];
char  Data2[200];
char  Data3[200];

extern boolean  ON;
extern boolean  OFF;

/* ------------------------------------------------ main function ---------------------------------------------- */
void setup()
{
    Serial.begin(BUADRATE2);
    ESPD1MINI.begin(BUADRATE2);
    Serial.println("clock:" + (String)F_CPU + "Hz");
    IOT_ENV_Init();
    Board_Init_void(OLDBOARD);
    Board_SetPinOut_void(OFF);
    RTC_Init();
//     RTC_DS3231_SetTime_void(20, 33, 30, WEDNESDAY, 31, 8, 22);            //14h9p30s - tuesday - 17/05/2022
    SDCARD_init_void();
    Calibration_Init_void();

    wdt_enable(WDTO_4S);
    TIMER1_Init();
    Sensor_Init_void(OLDBOARD);
}

void loop()
{
    wdt_reset();            // reset WDT
    FlagManageTask();

    /*  */
}

/* ------------------------------------------------ FlagTask function ---------------------------------------------- */
void WDT_ON()
{
    cli();
    wdt_reset();                                      // reset wdt to set prescaler
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    WDTCSR  = (1<<WDIE) | (1 << WDP3) | (1 << WDP0); // presceler 1024k 8s vcc=5.0
    sei();
}

ISR(WDT_vect)
{
  Serial.println("Watch Dog Timer interrupt");
}

void FlagManageTask()
{
    if(FlagTsGb > 0)
    {
        if( CHECK_BIT_FLAGTsGb(FLAG_TIM1, SHIFT_FLAG_TIM1) )
        {
            RTC_DS3231_ReadTime_String(RTC_Time);
            if( RTC_Time[hour] == 0 && RTC_Time[minute] == 0 && RTC_Time[second] == 0 )
            {
                delay(999);
                DataLoger2SDCard(NEWDAY);
            }
            TIM1_POLL_void();
            CLEAR_BIT_FLAGTsGb(FLAG_TIM1);

        }
        // Flag ESPDATA
        if( CHECK_BIT_FLAGTsGb(FLAG_ESPDTA1, SHIFT_FLAG_ESPDTA1) )
        {
            Json_Parse_void(Data1, RESETBOARD);
            memset(Data1, 0, sizeof(Data1));
            CLEAR_BIT_FLAGTsGb(FLAG_ESPDTA1);
        }
        else if( CHECK_BIT_FLAGTsGb(FLAG_ESPDTA2, SHIFT_FLAG_ESPDTA2) )
        {
            Json_Parse_void(Data2, RESETBOARD);
            memset(Data2, 0, sizeof(Data2));
            CLEAR_BIT_FLAGTsGb(FLAG_ESPDTA2);
        }
        else if( CHECK_BIT_FLAGTsGb(FLAG_ESPDTA3, SHIFT_FLAG_ESPDTA3) )
        {
            Json_Parse_void(Data3, RESETBOARD);
            memset(Data3, 0, sizeof(Data3));
            CLEAR_BIT_FLAGTsGb(FLAG_ESPDTA3);
        }
        // Flag save dataloger
        if( CHECK_BIT_FLAGTsGb(FLAG_DTALOG, SHIFT_FLAG_DTALOG) )
        {
            DataLoger2SDCard(NORMALDAY);
            CLEAR_BIT_FLAGTsGb(FLAG_DTALOG);
        }
        // Flag save json
        if( CHECK_BIT_FLAGTsGb(FLAG_JSVALUE, SHIFT_FLAG_JSVALUE) )
        {
          Serial.println("FLAG_JSVALUE");
            String JsonValueString = Json_CreateValue_String(Value_Sensor);
            ESPD1_SEND(JsonValueString);
            CLEAR_BIT_FLAGTsGb(FLAG_JSVALUE);
        }
        if( CHECK_BIT_FLAGTsGb(FLAG_JSANALOG, SHIFT_FLAG_JSANALOG) )
        {
          Serial.println("FLAG_JSANALOG");
            String JsonAnalogString = Json_CreateAnalog_String(JSON_ANALOG_byClient, Analog_Read);
            ESPD1_SEND(JsonAnalogString);
            CLEAR_BIT_FLAGTsGb(FLAG_JSANALOG);
        }

        if( CHECK_BIT_SaveEnArduino(SAVE_EN_IDLE, SHIFT_SAVE_EN_IDLE) )
        {
          Serial.println("Go to saving energy mode IDLE.");
          CLEAR_BIT_SaveEnArduino(SAVE_EN_IDLE);
          Saving_Energy_IDLEmode(ADC_ON, TIMER2_OFF, TIMER1_ON, TIMER0_ON, SPI_ON, USART0_ON, TWI_ON);
        }
    }
}

/* ------------------------------------------------ interrupt function ---------------------------------------------- */
ISR(TIMER1_OVF_vect)
{
    TCNT1 = 3035;
    ENABLE_BIT_FLAGTsGb(FLAG_TIM1);
    ++TimeLine;
}

void serialEvent2()
{
    String DataRev  = "";
    delayMicroseconds(50);
    while (ESPD1MINI.available() > 0)
    {
        DataRev += (char)ESPD1MINI.read();
        if(!ESPD1MINI.available())
            delayMicroseconds(100);
    }

    SHOW(F("NEW Data receive from ESP8266D1 mini: "));  SHOW((String)DataRev + DOWLN);

    if( !(CHECK_BIT_FLAGTsGb(FLAG_ESPDTA1, SHIFT_FLAG_ESPDTA1)) )
    {
        strcpy(Data1, DataRev.c_str());
        ENABLE_BIT_FLAGTsGb(FLAG_ESPDTA1);
        SHOWLN(F("Save massage from ESP to DATA1"));
    }
    else if( !(CHECK_BIT_FLAGTsGb(FLAG_ESPDTA2, SHIFT_FLAG_ESPDTA2)) )
    {
        strcpy(Data2, DataRev.c_str());
        ENABLE_BIT_FLAGTsGb(FLAG_ESPDTA2);
        SHOWLN(F("Save massage from ESP to DATA2"));
    }
    else if( !(CHECK_BIT_FLAGTsGb(FLAG_ESPDTA3, SHIFT_FLAG_ESPDTA3)) )
    {
        strcpy(Data3, DataRev.c_str());
        ENABLE_BIT_FLAGTsGb(FLAG_ESPDTA3);
        SHOWLN(F("Save massage from ESP to DATA3"));
    }
}

//void serialEvent()
//{
//    char   DataRev[50];
//    uint8  Cnt = 0;
//    while (Serial.available())
//    {
//        DataRev[Cnt++] = Serial.read();
//        if( (DataRev[Cnt] == '\r') || (DataRev[Cnt] == '\n') )
//        {
//            Serial.print(F("nhan duoc reuest: "));     
//            Serial.println(DataRev);
//        }
//        Serial.println(DataRev);
//    }
//    memset(DataRev, 0, sizeof(DataRev));
//    
//}

void	Saving_Energy_IDLEmode(adc_t adc, timer2_t timer2,timer1_t timer1, timer0_t timer0, spi_t spi, usart0_t usart0,	twi_t twi)
{
    // Temporary clock source variable
    unsigned char clockSource = 0;

    if (timer2 == TIMER2_OFF)
    {
      // Store current setting
      clockSource = TCCR2B;

      // Remove the clock source to shutdown Timer2
      TCCR2B &= ~(1 << CS22);
      TCCR2B &= ~(1 << CS21);
      TCCR2B &= ~(1 << CS20);

      power_timer2_disable();
    }

    if (adc == ADC_OFF)
    {
      ADCSRA &= ~(1 << ADEN);
      power_adc_disable();
    }

    if (timer1 == TIMER1_OFF)	power_timer1_disable();
    if (timer0 == TIMER0_OFF)	power_timer0_disable();
    if (spi == SPI_OFF)			  power_spi_disable();
    if (usart0 == USART0_OFF)	power_usart0_disable();
    if (twi == TWI_OFF)			  power_twi_disable();

    SLEEP_ARDUINO(MODE_POWER_IDLE);

    if (adc == ADC_OFF)
    {
      power_adc_enable();
      ADCSRA |= (1 << ADEN);
    }

    if (timer2 == TIMER2_OFF)
    {
      // Restore previous setting
      TCCR2B = clockSource;
      power_timer2_enable();
    }

    if (timer1 == TIMER1_OFF)	power_timer1_enable();
    if (timer0 == TIMER0_OFF)	power_timer0_enable();
    if (spi == SPI_OFF)			  power_spi_enable();
    if (usart0 == USART0_OFF)	power_usart0_enable();
    if (twi == TWI_OFF)			  power_twi_enable();
}
