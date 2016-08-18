#include <Arduino.h>

//#include <String.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

class SPIFFSWiFiCredentials
{
  public:  
  SPIFFSWiFiCredentials(void);
  static void begin(void);
  static void addSSID(String ssid, String password);
  static void save(void);
  static void load(ESP8266WiFiMulti &WiFiMulti);

  private:
  static void saveDataToFile(String fileNameForSave, String DataToSave);
  static String loadDataFromFile(String fileNameForOpen);

  static String credentialsString;
};
