void Write_Eeprom_WiFi_Data(String qsid, String qpass)
{

  if (qsid.length() > 0 && qpass.length() > 0) {
    Serial.println("clearing eeprom");
    for (int i = 0; i < 96; ++i) {
      EEPROM.write(i, 0);
    }

    Serial.println("writing eeprom ssid:");
    for (int i = 0; i < qsid.length(); ++i)
    {
      EEPROM.write(i, qsid[i]);
      Serial.print("Wrote: ");
      Serial.print(qsid[i]);
    }
    
    Serial.println("writing eeprom pass:");
    for (int i = 0; i < qpass.length(); ++i)
    {
      EEPROM.write(32 + i, qpass[i]);
      Serial.print("Wrote: ");
      Serial.print(qpass[i]);
    }
    EEPROM.commit();
  }
}

void Clear_Eeprom_Data()
{ 
  Serial.println("clear eeprom");
  Write_Eeprom_WiFi_Data("0", "0");
}

bool Load_WiFi_SSID_From_Eeprom(){
  String Read_SSID;
  for (int i = 0; i < 32; ++i)
  {
    Read_SSID += char(EEPROM.read(i));
  }
  WiFi_Stored_SSID = Read_SSID.c_str();
  return true;
}

bool Load_WiFi_Password_From_Eeprom(){
  String Read_Password;
  for (int i = 32; i < 96; ++i)
  {
    Read_Password += char(EEPROM.read(i));
  }
  WiFi_Stored_Password = Read_Password.c_str();
  return true;
}