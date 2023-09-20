#ifdef ESP32
#include <WiFi.h>
  #include <WiFiClient.h>
  #include <WebServer.h>
  WebServer server(80);
#else
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
  ESP8266WebServer server(80);
#endif
const char* ssid     = "dyrdom";
const char* password = "0990371234";

char htmlResponse[3000];
int ir = 13;
int led = 14;