#include "ESP8266OTAUpdate.hpp"


ESP8266WiFiMulti* OTAUpdate::myWiFiMulti;
int OTAUpdate::interval = 0;

void OTAUpdate::setWiFi(ESP8266WiFiMulti& aWiFiMulti)
{
  myWiFiMulti = &aWiFiMulti;
}

void OTAUpdate::setInterval(int interval)
{
  OTAUpdate::interval = interval;
}

void OTAUpdate::handlePeriodicUpdates(void)
{
  if (OTAUpdate::interval == 0) return;

  static unsigned long timestamp = 0;
  if (millis() - timestamp > interval)
  {
    timestamp = millis();
    OTAUpdate::update();
  }
}

void OTAUpdate::update(void)
{
    // wait for WiFi connection
    if ((myWiFiMulti->run() == WL_CONNECTED)) {

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

void OTAUpdate::printConfig(void)
{
  Serial.print("Update URL: ");
  Serial.println(__CODEBENDER_UPDATE_URL__);
  Serial.print("Current Version: ");
  Serial.println(__CODEBENDER_AUTO_VERSION__);
}

