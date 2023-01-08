#include "EEP.h"

uint8 EEPROM_Read_uint8(uint16 address)
{
    uint8 value = EEPROM.read(address);
    delay(10);
    DB_LOG(MODULE_EEP, "EEPROM _ value read: " + (String)value + DOWLN);
    return value;
}

void EEPROM_Write_void(uint16 address, uint8 SaveValue)
{
    /* An EEPROM write takes 3.3 ms to complete - The EEPROM memory has a specified life of 100,000 write/erase cycles */
    uint8 conditionLoop = 5; 
    EEPROM.write(address, SaveValue);
    delay(10);
    while(EEPROM.read(address) != SaveValue)
    {
        if(--conditionLoop)
          break;
        delay(10);
        EEPROM.write(address, SaveValue);
        delay(10);
    }
    DB_LOG(MODULE_EEP, "EEPROM SAVE VALUE : "+ String(SaveValue) + DOWLN);
    delay(5);
}

/* read config from eeprom 0 - 5 at address 4095 */
uint8 EEPROM_ReadCfg_uint8()
{
    delay(10);
    uint8 conf = EEPROM_Read_uint8(EEPROM_ADDRESS);
    if (conf >= 0 && conf < 6)
        DB_LOG(MODULE_EEP, "EEPROM _ Calibration config is: " + (String)conf + DOWLN);
    else
        DB_LOG(MODULE_EEP, "EEPROM _ value config read from EEPROM is not suitable");

    return conf;
}

