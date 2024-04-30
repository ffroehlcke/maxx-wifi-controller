void setup_webserver()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendHTML());
  });

  server.on("/change-wlan", HTTP_POST, [](AsyncWebServerRequest *request){
    String qsid = request->arg("ssid");
    String qpass = request->arg("password");
    Handle_Http_Save_WiFi(qsid, qpass);
    String redirect = "http://" + String(WiFi_Hostname) + ".local";
    request->send(200, "text/html", SendRebootHTML(redirect));
  });

  server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendRebootHTML("/"));
    requestReboot = true;
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", SendRebootHTML("http://192.168.4.1"));
    Clear_Eeprom_Data();
    requestReboot = true;
  });

  //RegEx: https://github.com/me-no-dev/ESPAsyncWebServer/blob/master/examples/regex_patterns/regex_patterns.ino
  server.on("^\\/fan\\/([a-zA-Z0-9]+)\\/([a-z0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) {
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
    else if(action == "automode" && value == "on")
    {
        IR_Send_Fan_Automode_On(); 
    }
    else if(action == "automode" && value == "off")
    {
        IR_Send_Fan_Automode_Off(); 
    }
    else if(action == "speed" && value == "0")
    {
        IR_Send_Fan_Speed_0(); 
    }
    else if(action == "speedOut" && value == "10")
    {
        IR_Send_Fan_Speed_Out_10(); 
    }
    else if(action == "speedOut" && value == "20")
    {
        IR_Send_Fan_Speed_Out_20(); 
    }
    else if(action == "speedOut" && value == "30")
    {
        IR_Send_Fan_Speed_Out_30(); 
    }
    else if(action == "speedOut" && value == "40")
    {
        IR_Send_Fan_Speed_Out_40(); 
    }
    else if(action == "speedOut" && value == "50")
    {
        IR_Send_Fan_Speed_Out_50(); 
    }
    else if(action == "speedOut" && value == "60")
    {
        IR_Send_Fan_Speed_Out_60(); 
    }
    else if(action == "speedOut" && value == "70")
    {
        IR_Send_Fan_Speed_Out_70(); 
    }
    else if(action == "speedOut" && value == "80")
    {
        IR_Send_Fan_Speed_Out_80(); 
    }
    else if(action == "speedOut" && value == "90")
    {
        IR_Send_Fan_Speed_Out_90(); 
    }
    else if(action == "speedOut" && value == "100")
    {
        IR_Send_Fan_Speed_Out_100(); 
    }
    else if(action == "speedIn" && value == "10")
    {
        IR_Send_Fan_Speed_In_10(); 
    }
    else if(action == "speedIn" && value == "20")
    {
        IR_Send_Fan_Speed_In_20(); 
    }
    else if(action == "speedIn" && value == "30")
    {
        IR_Send_Fan_Speed_In_30(); 
    }
    else if(action == "speedIn" && value == "40")
    {
        IR_Send_Fan_Speed_In_40(); 
    }
    else if(action == "speedIn" && value == "50")
    {
        IR_Send_Fan_Speed_In_50(); 
    }
    else if(action == "speedIn" && value == "60")
    {
        IR_Send_Fan_Speed_In_60(); 
    }
    else if(action == "speedIn" && value == "70")
    {
        IR_Send_Fan_Speed_In_70(); 
    }
    else if(action == "speedIn" && value == "80")
    {
        IR_Send_Fan_Speed_In_80(); 
    }
    else if(action == "speedIn" && value == "90")
    {
        IR_Send_Fan_Speed_In_90(); 
    }
    else if(action == "speedIn" && value == "100")
    {
        IR_Send_Fan_Speed_In_100(); 
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
  String ptr = "<!DOCTYPE html>\n";
  ptr += "<html lang=\"de\">\n";
  ptr += "<head>\n";
  ptr += "<meta charset=\"UTF-8\">\n";
  ptr += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  ptr += "<title>MaxxWifi-Controller</title>\n";
  ptr += "<style>\n";
  
  ptr += "body {background: linear-gradient(-45deg, #ee7752, #e73c7e, #23d5ab, #23a6d5); background-size: 400% 400%; height: 100vh; text-align:center;color:#FFFFFF;font-family:'Roboto',sans-serif;}";
  ptr += "@keyframes gradient { 0% { background-position: 0% 50%; } 50% { background-position: 100% 50%; } 100% { background-position: 0% 50%; } }";

  ptr += "h1 {margin: 30px auto 30px; margin-right: 20px; margin-left: 20px;font-size:7vw;}\n";
  ptr += "p {font-weight:300;}\n";
  ptr += ".button{display:inline-block;padding:0.35em 1.2em;border:0.1em solid #FFFFFF;margin:0 0.3em 0.3em 0;border-radius:0.12em;box-sizing: border-box;text-decoration:none;font-weight:300;text-align:center;transition: all 0.2s;color:#FFFFFF;font-family:'Roboto',sans-serif; }\n";
  ptr += "button {background-color: transparent;background-repeat: no-repeat;}\n";
  ptr += ".button:hover{color:#000000; background-color:#FFFFFF;}\n";
  ptr += "@media all and (max-width:30em){.button { display: block; margin: 0.4em auto;}}\n";
  ptr += ".block {width: 150px}\n";
  ptr += ".speed {width: 100%;}\n";
  ptr += "hr {margin: 0 auto;margin-top: 20px;margin-bottom: 20px;width: 40%;border: 0;height: 1px;background-image: linear-gradient(to right, rgba(255, 255, 255, 0), rgba(255, 255, 255, 0.75), rgba(255, 255, 255, 0));}\n";
  ptr += ".form {display:inline-block;padding:0.35em 1.2em;border:0.1em solid #FFFFFF;margin:0 10px 10px 0;border-radius:0.12em;box-sizing: border-box;}\n";
  ptr += "table {margin: auto;width: 100%;}\n";
  ptr += ".td-50 {width: 50%;}\n";
  ptr += ".td-20 {width: 20%;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Maxx Wifi Controller</h1>\n";

  if(!WiFi_Status_Up){
    ptr += "<p><strong>Access Point(AP) Mode</strong></p>\n";  
  }else{
    ptr += "<p>Connected to WLAN: <strong>";
    ptr += WiFi_Stored_SSID;
    ptr += "</strong></p>\n";
  }

  ptr += "<hr>\n";
  ptr += "<table><tr>";
  ptr += "<td class=\"td-50\"><a href=\"/fan/power/on\" class=\"button block\">Start</a></td>";
  ptr += "<td class=\"td-50\"><a href=\"/fan/power/off\" class=\"button block\">Stop</a></td>";
  ptr += "</tr><tr>";
  ptr += "<td class=\"td-50\"><a href=\"/fan/window/open\" class=\"button block\">Open</a></td>";
  ptr += "<td class=\"td-50\"><a href=\"/fan/power/off\" class=\"button block\">Close</a></td>";
  ptr += "</tr><tr>";
  ptr += "<td class=\"td-50\"><a href=\"/fan/air/in\" class=\"button block\">In</a></td>";
  ptr += "<td class=\"td-50\"><a href=\"/fan/air/out\" class=\"button block\">Out</a></td>";
  ptr +="</tr></table>\n";
  ptr += "<p>Set Fan speed</p>\n";
  ptr += "<table><tr>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speed/0\" class=\"button speed\">0</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/10\" class=\"button speed\">in 10</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/20\" class=\"button speed\">in 20</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/30\" class=\"button speed\">in 30</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/40\" class=\"button speed\">in 40</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/50\" class=\"button speed\">in 50</a></td>";
  ptr += "</tr><tr>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/60\" class=\"button speed\">in 60</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/70\" class=\"button speed\">in 70</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/80\" class=\"button speed\">in 80</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/90\" class=\"button speed\">in 90</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedIn/100\" class=\"button speed\">in 100</a></td>";
  ptr += "</tr><tr>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/10\" class=\"button speed\">out 10</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/20\" class=\"button speed\">out 20</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/30\" class=\"button speed\">out 30</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/40\" class=\"button speed\">out 40</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/50\" class=\"button speed\">out 50</a></td>";
  ptr += "</tr><tr>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/60\" class=\"button speed\">out 60</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/70\" class=\"button speed\">out 70</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/80\" class=\"button speed\">out 80</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/90\" class=\"button speed\">out 90</a></td>";
  ptr += "<td class=\"td-20\"><a href=\"/fan/speedOut/100\" class=\"button speed\">out 100</a></td>";
  ptr += "</tr></table>\n";

  ptr += "<hr>\n";
  ptr += "<p><strong>Settings</strong>\n";

  if(!WiFi_Status_Up){
    ptr += "<form action=\"/change-wlan\" method=\"post\">\n";
    ptr += "<select class=\"form\" name=\"ssid\">\n";
    for (byte i = 0; i < 49; i = i + 1) {
      if(WiFi_List[i].length() >= 3){
        ptr +="<option value=\"";
        ptr += WiFi_List[i];
        ptr +="\">";
        ptr += WiFi_List[i];
        ptr +="</option>\n";
      }
    }
    ptr += "</select>\n";
    ptr += "<input class=\"form\" type=\"text\" name=\"password\" placeholder=\"Password\"><br>\n";
    ptr += "\n";

    ptr += "<table><tr>\n";
    ptr += "<td class=\"td-50\"><button class=\"button\" type=\"submit\">Speichern</button></button>\n";
    ptr += "<td class=\"td-50\"><a href=\"/reboot\" class=\"button\">Reboot Controller</a></td>\n";
    ptr += "</tr></table>\n";

    ptr += "</form>\n";
  
  } else {
    ptr += "<table><tr>\n";
    ptr += "<td class=\"td-50\"><a href=\"/reset\" class=\"button\">Reset WIFI</a></td>\n";
    ptr += "<td class=\"td-50\"><a href=\"/reboot\" class=\"button\">Reboot Controller</a></td>\n";
    ptr += "</tr></table>\n";
  }


  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}


String SendRebootHTML(String nextPage){
  String ptr = "<!DOCTYPE html>\n";
  ptr += "<html lang=\"de\">\n";
  ptr += "<head>\n";
  ptr += "<meta charset=\"UTF-8\">\n";
  ptr += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  ptr += "<title>MaxxWifi-Controller</title>\n";
  ptr += "<style>\n";
  //ptr += "body {background-image: linear-gradient(to right, #0f0c29, #302b63, #24243e); text-align:center;color:#FFFFFF;font-family:'Roboto',sans-serif;}\n";
  
  ptr += "body {background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab); background-size: 400% 400%; animation: gradient 15s ease infinite; height: 100vh; text-align:center;color:#FFFFFF;font-family:'Roboto',sans-serif;}";
  ptr += "@keyframes gradient { 0% { background-position: 0% 50%; } 50% { background-position: 100% 50%; } 100% { background-position: 0% 50%; } }";
  
  ptr += "h1 {margin: 30px auto 30px; margin-right: 20px; margin-left: 20px;font-size:7vw;}\n";
  ptr += "p {font-weight:300;}\n";
  ptr += ".lds-ellipsis {display: inline-block;position: relative;width: 80px;height: 80px;}\n";
  ptr += ".lds-ellipsis div {position: absolute;top: 33px;width: 13px;height: 13px;border-radius: 50%;background: #fff;animation-timing-function: cubic-bezier(0, 1, 1, 0);}\n";
  ptr += ".lds-ellipsis div:nth-child(1) {left: 8px;animation: lds-ellipsis1 0.6s infinite;}\n";
  ptr += ".lds-ellipsis div:nth-child(2) {left: 8px;animation: lds-ellipsis2 0.6s infinite;}\n";
  ptr += ".lds-ellipsis div:nth-child(3) {left: 32px;animation: lds-ellipsis2 0.6s infinite;}\n";
  ptr += ".lds-ellipsis div:nth-child(4) {left: 56px;animation: lds-ellipsis3 0.6s infinite;} \n";
  ptr += "@keyframes lds-ellipsis1 {0% {  transform: scale(0);}100% {  transform: scale(1);}}\n";
  ptr += "@keyframes lds-ellipsis3 {0% {  transform: scale(1);}100% {  transform: scale(0);}}\n";
  ptr += "@keyframes lds-ellipsis2 {0% {  transform: translate(0, 0);}100% {  transform: translate(24px, 0);}}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Maxx Wifi Controller</h1>\n";
  ptr += "<p>Rebooting - Give me 5 seconds...</p>\n";
  ptr += "<div class=\"lds-ellipsis\"><div></div><div></div><div></div><div></div></div>\n";
  ptr += "<script> window.setTimeout(\"location.href='";
  ptr += nextPage;
  ptr += "';\", 6000); </script>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
