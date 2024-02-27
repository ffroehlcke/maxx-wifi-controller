void setup_wifi()
{
  Serial.println("Reading EEPROM");
  Load_WiFi_SSID_From_Eeprom();
  Load_WiFi_Password_From_Eeprom();

  if(WiFi_Stored_SSID != "0")
  {
    Serial.printf("Trying to connect to %s \n", WiFi_Stored_SSID.c_str());

    WiFi.mode(WIFI_STA);
    WiFi.setHostname(WiFi_Hostname);
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
  

  if(WiFi.status() == WL_CONNECTED)
  {
    WiFi_Status_Up = true;

    Serial.print("\nConnected to WiFi-Network: ");
    Serial.println(WiFi_Stored_SSID.c_str());
    Serial.print("Local ESP IP: ");
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
    WiFi.setHostname(WiFi_Hostname);
    WiFi.softAP(WiFi_AP_SSID, WiFi_AP_Password);
    Serial.printf("\nOnline - SSID %s AP with IP address %s\r\n", WiFi_AP_SSID, WiFi.softAPIP().toString().c_str());
    WiFi_Ip_Adresse = WiFi.softAPIP().toString();
  }  
}
