void setup_wifi()
{
  Serial.println("Reading EEPROM");
  Load_WiFi_SSID_From_Eeprom();
  Load_WiFi_Password_From_Eeprom();

  if(WiFi_Stored_SSID != "0")
  {
    Serial.printf("Trying to connect to %s \n", WiFi_Stored_SSID);
    Serial.printf("Password %s \n", WiFi_Stored_Password);

    WiFi.mode(WIFI_STA);
    WiFi.hostname(WiFi_Hostename);
    WiFi.begin(WiFi_Stored_SSID, WiFi_Stored_Password);

    int i = 0;
    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
      ++i;
      if(i >= 100){
        break;
      }
    }
  }
  

  if(WiFi.status() == WL_CONNECTED){
    WiFi_Status_Up = true;

    Serial.print("\nConnected to WiFi-Network: ");
    Serial.println(WiFi_Stored_SSID);
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    WiFi_Ip_Adresse = WiFi.localIP().toString();
  
  } else {
    
    WiFi.disconnect();
    Serial.print("\nWiFi-Fallback - Switch to AP Mode"); 

    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i) {
      WiFi_List[i] = WiFi.SSID(i);
    }

    WiFi.mode(WIFI_AP); 
    WiFi.hostname(WiFi_Hostename);
    WiFi.softAP(AP_WiFi_SSID, AP_WiFi_Password);
    Serial.printf("\nOnline - SSID %s AP with IP address %s\r\n", AP_WiFi_SSID, WiFi.softAPIP().toString().c_str());
    WiFi_Ip_Adresse = WiFi.softAPIP().toString();
    
  }
}
