#include "user_cfg.h"

uint32 seconds = 0;
uint8 FlagMQTT_Pub = false;
char Data[200];

// prototype function
void MQTT_Reconnect();
void WIFI_SETUP();
uint8 MQTT_Publish(char topic[], char DataUser[]);
inline void DebugLog_Show(String content);

void setup()
{
    pinMode(BUILTIN_LED, OUTPUT);
    LED(OFF);
    Serial.begin(BAUDRATE2);
    WIFI_SETUP();
    /* setup Server */
    client.setServer(MQTT_Server, 1883);
    client.setCallback(callback);
    // ESP.wdtEnable(WDTO_8S);
}

void loop()
{
    // ESP.wdtFeed();

    if (!client.connected())
        MQTT_Reconnect();
    client.loop();
    
    if(millis() - seconds >= 1000)
    {
      char StatusESP[10];
      memset(StatusESP, 0, sizeof(StatusESP));
      strcpy(StatusESP, String(seconds/1000).c_str());
      MQTT_Publish("MQTT_esp8266_status", StatusESP);
      seconds = millis();
    }
    ESP_Sleep(MODEM_SLEEP_T);
}

void serialEvent()
{
    uint8 index;
    char DataBuffer[Buffer];
    memset(DataBuffer, 0, sizeof(DataBuffer));
    
    while(Serial.available())
    {
        DataBuffer[index++] = (char)Serial.read();
        if(!Serial.available())
            delayMicroseconds(100);

        if(  (DataBuffer != "") && (Serial.available() == 0)  ) 
        {
            DebugLog_Show(DataBuffer);
            MQTT_Publish("MQTT_DEBUG", DataBuffer);
            MQTT_Publish("MQTT_Data_Pub", DataBuffer);
        }
    }
}

/* -----------------------Program Function-----------------------*/
void WIFI_SETUP()
{
    LED(OFF);
    delay(10);
    DebugLog_Show("\nConnecting to WiFi: " + String(SSID_WiFi) + "...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_WiFi, PASS_WiFi);
    while (WiFi.status() != WL_CONNECTED)
    {
        LED(!READLED);
        delay(250);
    }
    DebugLog_Show("\nWIFI CONNECTED");
}

/* ---------------------------MQTT function ---------------------------*/
void callback(char* topic, byte* payload, unsigned int length)
{
    String mess_payload = "";
    char msg_process[length+1];

    DebugLog_Show("\r\nMessage [" + (String)topic + "]");
    for (int i = 0; i < length; i++)
    {
        mess_payload += (char)payload[i];
        Data[i] = (char)payload[i];
        delayMicroseconds(100);
    }

    DebugLog_Show(mess_payload);
    UARTSEND(mess_payload);

} /* end callback */

uint8 MQTT_Publish(char topic[], char DataUser[])
{
    if(FlagMQTT_Pub)
    {
        boolean boolPub = client.publish(topic, DataUser);
        if(boolPub)
        {
//            DebugLog_Show("SUCCESS send data to server.");
            FlagMQTT_Pub = true;
            return 1;
        }
        else
        {
            DebugLog_Show("FAILED send data to server.");
            FlagMQTT_Pub = false;
            return 0;
        }
    }
    else
    {
      delay(50);
      FlagMQTT_Pub = true;
    }

    return 1;
}//end sub

void ESP_Sleep(sleep_type_t Mode)
{
    yield();
    delay(100);
    wifi_set_sleep_type(Mode);  //MODEM_SLEEP_T
    yield();
}

void MQTT_Reconnect()
{
  while (!client.connected())
  {
    DebugLog_Show("Connecting to MQTT Server..." + (String)MQTT_Server);
    if(WiFi.status() != WL_CONNECTED)
        WIFI_SETUP();
    if(client.connect("ESP"))
    {
        LED(OFF);
        DebugLog_Show("CONNECTED MQTT");
        client.subscribe("MQTT_Data_Sub");
    }
    else{
        DebugLog_Show("failed, rc = " + String(client.state()) + " try again in 5 seconds");
        LED(ON);
        delay(5000);
    }
  } /* end while */
} /* end reconnect MQTT*/ 

/*---------------------------Debug function----------------------------------------*/
inline void DebugLog_Show(String content)
{
    #if DEBUG_LOG
        showln(content);
    #endif
}
