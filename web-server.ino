void setup_webserver()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML());
  });

  server.on("/change-wlan", HTTP_GET, [](AsyncWebServerRequest *request){
    String qsid = request->arg("ssid");
    String qpass = request->arg("password");
    Handle_Http_Save_WiFi(qsid, qpass);
    request->redirect("/");
  });

  server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("/");
    requestReboot = true;
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Reboot");
    Clear_Eeprom_Data();
    requestReboot = true;
  });

  //RegEx: https://github.com/me-no-dev/ESPAsyncWebServer/blob/master/examples/regex_patterns/regex_patterns.ino
  server.on("^\\/fan\\/([a-z0-9]+)\\/([a-z0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String action = request->pathArg(0);
      String value = request->pathArg(1);
      HttpFanHandler(action, value); 
      request->redirect("/");
  });

  server.on("^\\/fan\\/([a-z0-9]+)\\/([a-z0-9]+)$", HTTP_POST, [] (AsyncWebServerRequest *request) {
      String action = request->pathArg(0);
      String value = request->pathArg(1);
      HttpFanHandler(action, value); 
      request->send(200, "text/plain", "OK");
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/html", "Not found");
  }); 

  if (!MDNS.begin(WiFi_Hostname)) {
    Serial.println("Error setting up MDNS responder!");
  }

  server.begin();
  Serial.println("HTTP server started");

}

void Handle_Http_Save_WiFi(String qsid, String qpass) 
{
    if (qsid.length() > 0 && qpass.length() > 0) {
      Write_Eeprom_WiFi_Data(qsid, qpass);
      requestReboot = true;
    }
}

void HttpFanHandler(String action, String value) {

    if(action == "power" && value == "on")
    {
        IR_Send_Fan_On();    
    }
    else if(action == "power" && value == "off")
    {
        IR_Send_Fan_Off(); 
    }
    else if(action == "window" && value == "open")
    {
        IR_Send_Fan_Open();    
    }
    else if(action == "window" && value == "close")
    {
        IR_Send_Fan_Close(); 
    }
    else if(action == "air" && value == "in")
    {
        IR_Send_Fan_Air_OutIn(); 
    }
    else if(action == "air" && value == "out")
    {
        IR_Send_Fan_Air_InOut(); 
    }
    else if(action == "automode" && value == "on")
    {
        IR_Send_Fan_Automode_On(); 
    }
    else if(action == "automode" && value == "off")
    {
        IR_Send_Fan_Automode_Off(); 
    }
    else if(action == "speed" && value == "10")
    {
        IR_Send_Fan_Speed_10(); 
    }
    else if(action == "speed" && value == "20")
    {
        IR_Send_Fan_Speed_20(); 
    }
    else if(action == "speed" && value == "30")
    {
        IR_Send_Fan_Speed_30(); 
    }
    else if(action == "speed" && value == "40")
    {
        IR_Send_Fan_Speed_40(); 
    }
    else if(action == "speed" && value == "50")
    {
        IR_Send_Fan_Speed_50(); 
    }
    else if(action == "speed" && value == "60")
    {
        IR_Send_Fan_Speed_60(); 
    }
    else if(action == "speed" && value == "70")
    {
        IR_Send_Fan_Speed_70(); 
    }
    else if(action == "speed" && value == "80")
    {
        IR_Send_Fan_Speed_80(); 
    }
    else if(action == "speed" && value == "90")
    {
        IR_Send_Fan_Speed_90(); 
    }
    else if(action == "speed" && value == "100")
    {
        IR_Send_Fan_Speed_100(); 
    }
    else if(action == "window" && value == "50")
    {
        IR_Send_Fan_Open_50(); 
    }
    else if(action == "window" && value == "60")
    {
        IR_Send_Fan_Open_60(); 
    }
    else if(action == "window" && value == "70")
    {
        IR_Send_Fan_Open_70(); 
    }
    else if(action == "window" && value == "80")
    {
        IR_Send_Fan_Open_80(); 
    }
    else if(action == "window" && value == "90")
    {
        IR_Send_Fan_Open_90(); 
    }

    
}



String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>MaxxFan WiFi Controller</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 200px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +=".input {display: block;width:200px;color: #3498db;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;}\n";
  ptr +=".select {display: block;width:260px;color: #3498db;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>MaxxFan WiFi Controller</h1>\n";

  if(!WiFi_Status_Up){
    ptr +="<h3>Access Point(AP) Mode</h3>\n";
    ptr +="<form action=\"/change-wlan\">\n";
    ptr +="<p>WLAN-Netzwerk</p>\n";
    ptr +="<select name=\"ssid\" class=\"select\" >\n";
    for (byte i = 0; i < 49; i = i + 1) {
      if(WiFi_List[i].length() >= 3){
        ptr +="<option value=\"";
        ptr += WiFi_List[i];
        ptr +="\">";
        ptr += WiFi_List[i];
        ptr +="</option>\n";
      }
    }

    ptr +="</select>\n";
    ptr +="<p>Passwort</p>\n";
    ptr +="<input class=\"input\" type=\"text\" name=\"password\">\n";
    ptr +="<input class=\"button\" type=\"submit\" value=\"Speichern\">\n";
    ptr +="</form>\n";

  }else{
    ptr +="<h3>Connected to WLAN: ";
    ptr += WiFi_Stored_SSID;
    ptr +="</h3>\n";
    ptr +="<p>WLAN Einstellungen neu setzen</p><a class=\"button button-on\" href=\"/reset\">RESET</a>\n";
  }
 
  ptr +="<br><p>System neustarten</p><a class=\"button button-off\" href=\"/reboot\">REBOOT</a><br><br>\n";

  ptr +="<br><p><a href=\"/fan/power/on\">Einschalten</a>\n";
  ptr +="<br><p><a href=\"/fan/power/off\">Ausschalten</a>\n";
  ptr +="<br><p><a href=\"/fan/window/open\">Fenster öffnen</a>\n";
  ptr +="<br><p><a href=\"/fan/window/close\">Fenster schließen</a>\n";
  ptr +="<br><p><a href=\"/fan/air/in\">Luft rein</a>\n";
  ptr +="<br><p><a href=\"/fan/air/out\">Luft raus</a>\n";
  ptr +="<br><p><a href=\"/fan/automode/on\">Automode: on</a>\n";
  ptr +="<br><p><a href=\"/fan/automode/off\">Automode: off</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/10\">Speet: 10 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/20\">Speet: 20 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/30\">Speet: 30 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/40\">Speet: 40 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/50\">Speet: 50 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/60\">Speet: 60 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/70\">Speet: 70 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/80\">Speet: 80 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/90\">Speet: 90 %</a>\n";
  ptr +="<br><p><a href=\"/fan/speed/100\">Speet: 100 %</a>\n";
  ptr +="<br><p><a href=\"/fan/window/50\">Fenster öffnen (50)</a>\n";
  ptr +="<br><p><a href=\"/fan/window/60\">Fenster öffnen (60)</a>\n";
  ptr +="<br><p><a href=\"/fan/window/70\">Fenster öffnen (70)</a>\n";
  ptr +="<br><p><a href=\"/fan/window/80\">Fenster öffnen (80)</a>\n";
  ptr +="<br><p><a href=\"/fan/window/90\">Fenster öffnen (90)</a>\n";

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}