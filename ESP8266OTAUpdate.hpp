#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>


#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>


#define __CODEBENDER_UPDATE_URL__ "http://esp.codebender.cc/api/update/CODEBENDER_API_KEY"
#define __CODEBENDER_AUTO_VERSION__ "0000000000"


class OTAUpdate
{
  public:  
  OTAUpdate(void);
  static void setWiFi(ESP8266WiFiMulti& aWiFiMulti);
  static void printConfig(void);

  static void update(void);
  static void setInterval(int interval);
  static void handlePeriodicUpdates(void);

  private:
  static int interval;
  static ESP8266WiFiMulti* myWiFiMulti;
};

