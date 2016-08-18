
#include "SPIFFSWiFiCredentials.hpp"
#include <FS.h>

String SPIFFSWiFiCredentials::credentialsString;

void SPIFFSWiFiCredentials::begin(void)
{
  SPIFFS.begin();
}

void SPIFFSWiFiCredentials::addSSID(String ssid, String password)
{
  Serial.println("Adding SSID:     " + ssid);
  Serial.println("       Password: " + (password == ""? "***NO PASSWORD***": password));

  credentialsString += ssid + "\n" + password + "\n";
//  Serial.print("Credentials String:\n" + SPIFFSWiFiCredentials::credentialsString);
}

void SPIFFSWiFiCredentials::save(void)
{
  SPIFFSWiFiCredentials::saveDataToFile("credentials", credentialsString);
}

void SPIFFSWiFiCredentials::load(ESP8266WiFiMulti &WiFiMulti)
{
  String credentials = SPIFFSWiFiCredentials::loadDataFromFile("credentials");  

//  Serial.println("creds loaded: ");
//  Serial.println(credentials);

  int done = false;
  int indexOfNewline;
  while(!done)
  {
    indexOfNewline = credentials.indexOf('\n');
    if(indexOfNewline == -1)
    {
      done = true;
      continue;
    }
    String ssid = credentials.substring(0, indexOfNewline);

    credentials = credentials.substring(indexOfNewline+1);

    indexOfNewline = credentials.indexOf('\n');
    if(indexOfNewline == -1)
    {
      done = true;
      continue;
    }
    String password = credentials.substring(0, indexOfNewline);
    
    credentials = credentials.substring(indexOfNewline+1);

    Serial.println("Setting up WiFi SSID");
    Serial.println("SSID:     " + ssid);
    Serial.println("Password: " + (password == ""? "***NO PASSWORD***": password));

    char bufferArray[2][20];
    ssid.toCharArray(bufferArray[0], 20);
    password.toCharArray(bufferArray[1], 20);

    WiFiMulti.addAP(bufferArray[0], bufferArray[1]);

//    Serial.println("credentials are now:\n" + credentials);
//    done = true;
  }
}

void SPIFFSWiFiCredentials::saveDataToFile(String fileNameForSave, String DataToSave)
{
  String filePath = String("/data/" + fileNameForSave+ ".dat");
  Serial.println("Saving File:  " + filePath);

  //SPIFFS.begin();
  File f = SPIFFS.open(filePath, "w");
  if (!f)
  {
    Serial.println(F("file open failed"));
  }
  else
  {
    f.println(String(DataToSave + String('\r')));
    f.close();
  }
  return;
}

String SPIFFSWiFiCredentials::loadDataFromFile(String fileNameForOpen)
{
  String filePath = String("/data/" + fileNameForOpen+ ".dat");
  Serial.println("Loading File: " + filePath);

  int fileOpenFail;
  String WhatIwillReturn;
  //SPIFFS.begin();
  File f = SPIFFS.open(filePath, "r");
  if (!f)
  {
    fileOpenFail = 1;
    //Serial.print("file open failed  :");
    //Serial.println(fileNameForOpen);
  }
  else
  {
    fileOpenFail = 0;
    WhatIwillReturn =  f.readStringUntil('\r');
//    WhatIwillReturn.replace("\n", "");
    f.close();
    return WhatIwillReturn;
  }
}
