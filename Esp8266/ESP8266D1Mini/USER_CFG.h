/*
 * pubsubclient version 2.8.0 by Nic O'leary 
 * when can not connect to server led on board will turn on
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/*buffer data pubish*/
#define Buffer      240
#define ON          LOW
#define OFF         HIGH
#define LED(x)      digitalWrite(BUILTIN_LED, x)
#define READLED     digitalRead(BUILTIN_LED)
#define UARTSEND    Serial.print

#define endln       Serial.println();
#define show        Serial.print
#define showln      Serial.println

#define BAUDRATE1   9600
#define BAUDRATE2   115200

#define DEBUG_LOG   false

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;

char SSID_WiFi[]   = "CTU_IOTLAB";                    //CTU_IOTLAB      //Khoa peB        //Nha Tro Di 3 2.4G
char PASS_WiFi[]   = "02710271";                      //02710271      //0936696867          //12356789
char MQTT_Server[] = "192.168.137.232";               //192.168.137.1     //192.168.0.102   //192.168.1.15

WiFiClient espClient;
PubSubClient client(espClient);
