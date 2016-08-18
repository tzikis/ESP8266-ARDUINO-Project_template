/**
   httpUpdate.ino

    Created on: 27.11.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "SPIFFSWiFiCredentials.hpp"
#include "ESP8266OTAUpdate.hpp"

ESP8266WiFiMulti WiFiMulti;

const int ledPin = LED_BUILTIN;

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
  
   SPIFFSWiFiCredentials::begin();
   SPIFFSWiFiCredentials::load(WiFiMulti);

   OTAUpdate::printConfig();
   OTAUpdate::setWiFi(WiFiMulti);

  // if there's an update, fetch it and update
  //OTAUpdate::update(); 
  // check every 30 seconds
  OTAUpdate::setInterval(30000); 

  pinMode(ledPin, OUTPUT);
}


void blinkLEDWithoutDelay(int pin);

void loop() {

  blinkLEDWithoutDelay(ledPin);

  // if the interval since the last update has passed, see if there's an update and if so fetch it & update
  OTAUpdate::handlePeriodicUpdates();
}


void blinkLEDWithoutDelay(int pin)
{
  static unsigned long blinkTimestamp = 0;
  static const int interval = 1000;
  if (millis() - blinkTimestamp > interval)
  {
    static bool status = 0;
    digitalWrite(ledPin, status);
    if (status == 0) status = 1;
    else status = 0;

    blinkTimestamp = millis();
  }

}
