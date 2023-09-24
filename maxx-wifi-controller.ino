#ifdef ESP32
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <mDNS.h> 
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <ESP8266mDNS.h> 
#endif

#include <EEPROM.h>

// Feste Werte
int IRledPin = 5; //D1 Port

const char* WiFi_Hostname = "maxxwifi";
const char* AP_WiFi_SSID = "Maxx-Wifi-Controller";
const char* AP_WiFi_Password = "12345678";

bool Load_WiFi_SSID_From_Eeprom(void);
bool Load_WiFi_Password_From_Eeprom(void);

boolean WiFi_Status_Up = false;
boolean requestReboot = false;
String WiFi_Stored_SSID;
String WiFi_Stored_Password = "";
String WiFi_List[50];
String WiFi_Ip_Adresse;

AsyncWebServer server(80);

void setup()
{
  pinMode(IRledPin, OUTPUT);  
  Serial.begin(9600);
  EEPROM.begin(512);
  delay(100);

  Serial.println("-= Maxx-WiFi-Controller =-");  
  
  setup_wifi();
  setup_webserver();

  Serial.printf("Open http://%s or http://%s.local\n", WiFi_Ip_Adresse.c_str(), WiFi_Hostname);
}


void loop()
{
  if (requestReboot) {
    Serial.println("Rebooting in 2 seconds...");
    delay(1000);
    server.reset();
    ESP.restart();
  }
  MDNS.update(); 
}