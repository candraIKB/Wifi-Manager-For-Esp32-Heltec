/*
  Project: Wifi Manager Lesson
  Programmer: Shahrulnizam Mat Rejab
  Board: Hibiscus Sense ESP32
  Last Modified: 17 March 2021
  Website: http://shahrulnizam.com
*/

#include <WiFiManager.h>

#define LED       2
#define INTERVAL  1000

char data;
unsigned long int timer;

WiFiManager wifiManager;

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setTimeout(60);
  if (!wifiManager.autoConnect("ESP32"))
  {
    Serial.println("failed to connect and hit timeout");
  }
  else
  {
    Serial.println("Successfully connected");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (millis() - timer >= INTERVAL)
  {
    timer = millis();
    digitalWrite(LED, !digitalRead(LED));
    if (digitalRead(LED) == LOW) Serial.println("LED OFF");
    else Serial.println("LED ON");
  }

  if (Serial.available())
  {
    data = Serial.read();
    if (data == '1')
    {
      WiFi.disconnect(false, true);
      delay(3000);
      Serial.println("Reset wifi setting and restart");
      wifiManager.resetSettings();
      ESP.restart();
    }
  }
}

void configModeCallback (WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}
