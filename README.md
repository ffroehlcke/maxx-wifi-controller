# Maxx-Wifi-Controller 👋

Mit diesem Projekt könnt Ihr euch eine IR-Steuerung für den beliebten Camper-Ventilator bauen. Der Code ist getestet auf einem [ESP8266](https://github.com/esp8266/Arduino)- und einem 
[ESP32](https://github.com/espressif/arduino-esp32)-Mikrocontroller. Ihr braucht nur den Chip und eine IR-LED. Der Kontroller kann entweder im WLAN-Access-Point Modus betrieben werden oder mit einem vorhandnen WLAN verbunden werden.  

![IMG_3854](https://github.com/ffroehlcke/maxx-wifi-controller/assets/4354298/adae7102-da4f-48e2-af4c-0dd7b278ad98)

### Aufbau

Verbindet die LED mit GND und D1. Übertragt den Code auf den Mikrocontroller.

![image](https://github.com/ffroehlcke/maxx-wifi-controller/assets/4354298/e1fc1cb2-8f2c-41b3-bb18-89d5cf6f2095)


### Regex Unterstützung aktivieren

Damit euer Compiler Regex unterstützt, müsst ihr ein Flag setzen:

Arduino IDE: create/update platform.local.txt
Windows: C:\Users\(username)\AppData\Local\Arduino15\packages\espxxxx\hardware\espxxxx\{version}\platform.local.txt
Linux: ~/.arduino15/packages/espxxxx/hardware/espxxxx/{version}/platform.local.txt

compiler.cpp.extra_flags=-DASYNCWEBSERVER_REGEX=1

platformio: platformio.ini:
 build_flags = 
      -DASYNCWEBSERVER_REGEX


### WLAN

Nach dem Einschalten startet der Kontroller einen Access-Point mit der SSID *Maxx-Wifi-Controller* und den Passwort *12345678*. Diese Werte können om Code geändert werden: 
```
const char* WiFi_Hostname = "maxxwifi";
const char* WiFi_AP_SSID = "Maxx-Wifi-Controller";
const char* WiFi_AP_Password = "12345678";
```
Verbindet euch mit diesem WLAN und ruft das Web-Interface über 
* http://maxxwifi.local oder
* http://192.167.4.1 auf. 

Auf dieser Seite könnt ihr nun euren Ventilator steuern oder den Kontroller mit einem vorhandenen WLAN verbinden. Wählt dazu das gewünschte Netzwerk aus und gebt den Schlüssel ein. Die Zugangsdaten werden auf dem Chip gespeichert. 

### API

Auch wenn das den Begriff API eigentlich nicht verdient, könnt ihr mit einem HTTP-POST auf die folgende Endpoints den Kontroller z.B. in NodeRed, [VanPi](https://pekaway.de/), etc. einbinden.

* http://maxxwifi.local/fan/power/on
* http://maxxwifi.local/fan/power/off
* http://maxxwifi.local/fan/windows/open
* http://maxxwifi.local/fan/windows/close
* http://maxxwifi.local/fan/air/in
* http://maxxwifi.local/fan/air/out
* http://maxxwifi.local/fan/speed/10
* http://maxxwifi.local/fan/speed/20
* usw.

### Disclaimer

Das WLAN-Kennwort ist unsicher, die Verbindung läuft nicht über SSL, die API hat keinen Token... Lange Rede, der Kontroller sollte nur in zusätzlich gesicherten WLAN-Netzwerken und im Hobby-Bereich betrieben werden! 

Ihr habt Anpassungen? Dann freue ich mich über Unterstützung.
