#include "SD_CARD.h"

/*******************************************************************************
* @FunctionName:    SDCARD_WriteFile_String                                            
* @Description:     write string to SD CARD      
* @Param:           String NameFile, String WriteContent    
* @Return:          boolean                                                       
*******************************************************************************/
boolean SDCARD_WriteFile_String( String NameFile, String WriteContent )
{
    File WriteFile;
    WriteFile = SD.open(NameFile, FILE_WRITE);
    if(WriteFile)
    {
        DB_LOG(MODULE_SD, "Write(file): " + WriteContent + DOWLN);
        uint32_t WriteData = WriteFile.print(WriteContent);
        if (WriteData > 0)
            DB_LOG(MODULE_SD, F("Write(file) SUCCESS. \r\n"));
        else
            DB_LOG(MODULE_SD, F("Write(file) FAIL. \r\n"));

        WriteFile.close();
        return true;
    }
    else
    {
        DB_LOG(MODULE_SD, F("write(file)ERROR."));           ENDLN
        return false;
    }
}

// /*******************************************************************************
// * @FunctionName:    SDCARD_RemoveFile_bool                                            
// * @Description:     delete file      
// * @Param:           String NameFile   
// * @Return:          boolean                                                       
// *******************************************************************************/
boolean SDCARD_RemoveFile_bool( String NameFile )
{
  int8_t boolRemove = -1;
  if (SD.exists(NameFile))
  {
    boolRemove = SD.remove(NameFile);
    if (boolRemove)
        DB_LOG(MODULE_SD, F("Remove file SUCCESS. \r\n"));
    else
        DB_LOG(MODULE_SD, F("Remove file FAIL. \r\n"));
  }
}

/*******************************************************************************
* @FunctionName:    SDCARD_CreateFolder_bool                                            
* @Description:     create folder direction      
* @Param:           String direct   
* @Return:          boolean                                                       
*******************************************************************************/
boolean SDCARD_CreateFolder_bool(String direct)
{
    boolean FlagSD = SD.mkdir(direct);
    if (FlagSD) {
        DB_LOG(MODULE_SD, "Create folder SUCCESS: " + (String)direct + DOWLN);
        return true;
    }
    else {
        DB_LOG(MODULE_SD, F("Create folder FAIL"));      ENDLN
        return false;
    }
}

/*******************************************************************************
* @FunctionName:    SDCARD_ReadFileCfg_String                                            
* @Description:     read of file configuration from SD CARD      
* @Param:           uint8 configsave    
* @Return:          String                                                       
*******************************************************************************/
String SDCARD_ReadFileCfg_String(uint8 CfgSave)
{
  String DataGet = "";
  switch (CfgSave)
  {
    case 1:
        DataGet = SDCARD_ReadFile_String("/config/config1.txt");
        break;
    case 2:
        DataGet = SDCARD_ReadFile_String("/config/config2.txt");
        break;
    case 3:
        DataGet = SDCARD_ReadFile_String("/config/config3.txt");
        break;
    case 4:
        DataGet = SDCARD_ReadFile_String("/config/config4.txt");
        break;
    case 5:
        DataGet = SDCARD_ReadFile_String("/config/config5.txt");
        break;
    default:
        DB_LOG(MODULE_SD, F("request read(file) not available"));    ENDLN
      break;
  }
  return DataGet;
}

/*******************************************************************************
* @FunctionName:    SDCARD_ReadFile_String                                            
* @Description:     read content of file      
* @Param:           String NameFile    
* @Return:          String                                                       
*******************************************************************************/
String SDCARD_ReadFile_String( String NameFile )
{
    String ContentFile = "";
    File ReadFile;

    ReadFile = SD.open(NameFile);
    if(ReadFile)
    {
        while (ReadFile.available())
        ContentFile += char(ReadFile.read());
        ReadFile.close();
        DB_LOG(MODULE_SD, "Read(file): " + ContentFile + DOWLN);
    }
    else
        DB_LOG(MODULE_SD, F("read(file)ERROR.!"));       ENDLN
    return ContentFile;
}

/*******************************************************************************
* @FunctionName:    SDCARD_SaveConfigFile_uint8                                            
* @Description:     save string to SD CARD with numeric of calibration   
* @Param:           uint8 NumCfg, String DataSave
* @Return:          uint8                                                       
*******************************************************************************/
uint8 SDCARD_SaveConfigFile_uint8(uint8 NumCfg, String DataSave)
{
  if (!SD.exists("config"))
    SDCARD_CreateFolder_bool("config");
  switch (NumCfg)
  {
    case 1:
        SDCARD_RemoveFile_bool("/config/config1.txt");
        SDCARD_WriteFile_String("/config/config1.txt", DataSave);
        break;
    case 2:
        SDCARD_RemoveFile_bool("/config/config2.txt");
        SDCARD_WriteFile_String("/config/config2.txt", DataSave);
        break;
    case 3:
        SDCARD_RemoveFile_bool("/config/config3.txt");
        SDCARD_WriteFile_String("/config/config3.txt", DataSave);
        break;
    case 4:
        SDCARD_RemoveFile_bool("/config/config4.txt");
        SDCARD_WriteFile_String("/config/config4.txt", DataSave);
        break;
    case 5:
        SDCARD_RemoveFile_bool("/config/config5.txt");
        SDCARD_WriteFile_String("/config/config5.txt", DataSave);
        break;
    default:
        DB_LOG(MODULE_SD, F("no task Json config is saved"));    ENDLN
        break;
  }
}

/*******************************************************************************
* @FunctionName:    SDCARD_SaveFile2Folder_void                                            
* @Description:     save string to folder and FolderDirect (FolderDirect can not available)   
* @Param:           String Folder, String FolderDirect, String Data
* @Return:          void                                                       
*******************************************************************************/
void SDCARD_SaveFile2Folder_void(String Folder, String FolderDirect, String Data)
{
    if (!SD.exists(Folder))
        SDCARD_CreateFolder_bool(Folder);
    SDCARD_RemoveFile_bool(FolderDirect);
    SDCARD_WriteFile_String(FolderDirect, Data);
}

/*******************************************************************************
* @FunctionName:    DataLoggerSD                                            
* @Description:     save history value of sensor to SD CARD    
* @Param:           uint8 WhData, float *Value_Sensor
* @Return:          void                                                       
*******************************************************************************/
void SDCARD_init_void(void)
{
    int reconnect = 0;
    do
    {
        if (SD.begin(PIN_SD_CARD))
        {
            DB_LOG(MODULE_SD, F("_________initialization SD CARD done___________"));   ENDLN
        }
        else
            DB_LOG(MODULE_SD, F("_________initialization SD CARD failed!_________"));  ENDLN
        reconnect++;
        if (reconnect >= 5)
        break;
        //resetFunc();
    } while (!SD.begin(PIN_SD_CARD));

    SDCARD_CreateFolder_bool(FOLDER_DATALOG);
    SDCARD_CreateFolder_bool(FOLDER_AN_CALI);
    SDCARD_CreateFolder_bool(FOLDER_CONFIG);
}
