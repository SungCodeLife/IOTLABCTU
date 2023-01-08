/* ---------------------------------------------------------------------------------------------- */
/*  File name:    eeprom_user.h                                                                   */
/*  Description:  functions                                                               */
/*  Version:      1.0.0                                                                           */
/*  Date:         24/02/2022                                                                      */
/* ---------------------------------------------------------------------------------------------- */
#ifndef __EEP_H_
#define __EEP_H_

/* ---------------------------------------------------------------------------------------------- */
/*                                         include library                                        */
/* ---------------------------------------------------------------------------------------------- */
#include "user_cfg.h"

/* ---------------------------------------------------------------------------------------------- */
/*                                       prototype function                                       */
/* ---------------------------------------------------------------------------------------------- */
uint8 EEPROM_Read_uint8(uint16 address);
void EEPROM_Write_void(uint16 address, uint8 SaveValue);
uint8 EEPROM_ReadCfg_uint8();


#endif

/*
* capacity EEPROM: 4KB
* Address save in EEPROM
* Address 0: Save number of config calibration
* Address 1: Save lenght of string json backup
* Address 2:
* Address 3: 
*/