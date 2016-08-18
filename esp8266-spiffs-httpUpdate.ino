/**
   httpUpdate.ino

    Created on: 27.11.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#include "SPIFFSWiFiCredentials.hpp"

ESP8266WiFiMulti WiFiMulti;

const int ledPin = 5;

void setup() {

  Serial.begin(115200);
   Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  Serial.print("Update URL: ");
  Serial.println(__CODEBENDER_UPDATE_URL__);
  Serial.print("Current Version: ");
  Serial.println(__CODEBENDER_AUTO_VERSION__);
  
   SPIFFSWiFiCredentials::begin();
   SPIFFSWiFiCredentials::load(WiFiMulti);


  pinMode(ledPin, OUTPUT);
}

void tryToUpdate(void);

void loop() {

  static unsigned long blinkTimestamp = 0;
  static const int interval = 1000;
  if (millis() - blinkTimestamp > interval)
  {
    static bool status = 0;
    digitalWrite(ledPin, status);
    if (status == 0) status = 1;
    else status = ledPin;

    blinkTimestamp = millis();
  }
  tryToUpdate();
}

void tryToUpdate(void)
{
  static unsigned long timestamp = 0;
  static const int interval = 10000;
  if (millis() > 30000 && millis() - timestamp > interval)
  {
    timestamp = millis();
    
    // wait for WiFi connection
    if ((WiFiMulti.run() == WL_CONNECTED)) {

      Serial.println("Trying to fetch new binary");

      t_httpUpdate_return ret = ESPhttpUpdate.update(__CODEBENDER_UPDATE_URL__, __CODEBENDER_AUTO_VERSION__);
      switch (ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          break;

        case HTTP_UPDATE_OK:
          Serial.println("HTTP_UPDATE_OK");
          break;
      }
    }
  }
}

