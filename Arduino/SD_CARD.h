
#ifndef __SD_CARD_H_
#define __SD_CARD_H_

#include "user_cfg.h"

/* ---------------------------------------------------------------------------------------------- */
/*                                       prototype function                                       */
/* ---------------------------------------------------------------------------------------------- */
boolean SDCARD_WriteFile_String(String NameFile, String WriteContent);
boolean SDCARD_RemoveFile_bool(String NameFile);
boolean SDCARD_CreateFolder_bool(String direct);
String SDCARD_ReadFileCfg_String(uint8 configsave);
String SDCARD_ReadFile_String( String NameFile );
uint8 SDCARD_SaveConfigFile_uint8(uint8 configsave, String datasave);
void SDCARD_SaveFile2Folder_void(String Folder, String FolderDirect, String Data);
void DataLoggerSD(uint8 WhData, float *Value_Sensor);
void SDCARD_init_void(void);


#endif
