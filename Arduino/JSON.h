/* ---------------------------------------------------------------------------------------------- */
/*  File name:    json.h                                                                          */
/*  Description:  functions                                                                       */
/*  Version:      1.0.0                                                                           */
/*  Date:         24/02/2022                                                                      */
/* ---------------------------------------------------------------------------------------------- */
#ifndef __JSON_H_
#define __JSON_H_

/* ---------------------------------------------------------------------------------------------- */
/*                                         include Library                                        */
/* ---------------------------------------------------------------------------------------------- */

#include "user_cfg.h"
#include <ArduinoJson.h>  // JSON version 6.19.0 by Beniot Blanchon

/* ---------------------------------------------------------------------------------------------- */
/*                                       prototype function                                       */
/* ---------------------------------------------------------------------------------------------- */

String Json_CreateCalib_String( float *Calib );
String Json_CreateValue_String( float *ValueSS );
String Json_CreateAnalog_String(uint8_t request, uint16 *AnalogJS);
String Json_CreateRelayPIN_String(uint8 *pin);
String Json_CreateAnalogPIN_String(uint8 *pin);


#endif
