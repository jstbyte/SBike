#include <Arduino.h>
#include <ESP8266WiFi.h>

// For OTA UPDATE;
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#define KEY_PIN 5

#define AP_NAME "A29"
#define AP_PASS "A29Password"
char known_mac[] = "A8:7D:12:36:50:12";

AsyncWebServer server(80);

void setup()
{
  // Kill Switch Pin Setup;
  pinMode(KEY_PIN, OUTPUT);
  digitalWrite(KEY_PIN, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_NAME, AP_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
  }

  // Compare connetced AP MAC with predefined MAC;
  if (WiFi.BSSIDstr() != known_mac)
  {
    delay(1000);
    ESP.restart();
  }

  digitalWrite(KEY_PIN, HIGH);
  // ESP.deepSleep(ESP.deepSleepMax());

  // Start ElegantOTA;
  AsyncElegantOTA.begin(&server);
  server.begin();
}

// the loop function runs over and over again forever;
void loop()
{
  // Total 5 Minute Delay;
  for (int i = 0; i < 5; i++)
  {
    AsyncElegantOTA.loop();
    delay(60000);
  }

  // Check Wifi Connection;
  if (!WiFi.isConnected() || WiFi.BSSIDstr() != known_mac)
  {
    ESP.restart();
  }
}