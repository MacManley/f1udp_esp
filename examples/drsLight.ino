//File: drsLight.ino

//#include "Wifi.h" // ESP32 WiFi include
#include <ESP8266WiFi.h> // ESP8266 WiFi include
#include <WiFiUdp.h>
#include <F1_23_UDP.h>

const char *SSID = "Your SSID";
const char *Password = "Your WiFi Password";

void startWiFi();
 
//The IP address that this ESP32 / ESP8266 has requested to be assigned to.
IPAddress ip();
WiFiUDP Udp;

unsigned int localPort = 20777; // Port that is used in game, default is 20777

F1_23_Parser* parser;

void setup() 
{ 
  parser = new F1_23_Parser();
  Serial.begin(115200);
  startWiFi();
  Udp.begin(localPort);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  int packetSize = Udp.parsePacket(); 
  
    if(packetSize) 
    {
       char packetBuffer[packetSize];
       while(Udp.available())
       {
        Udp.read(packetBuffer, packetSize);
       }
       parser->push(packetBuffer);

      unsigned int playerCar = parser->packetCarTelemetryData()->m_playerCarIndex(); // Get the index of the players car in the array.
      bool drs = parser->packetCarTelemetryData()->m_carTelemetryData(playerCar).m_drs; // DRS assigned as a bool, 0 - OFF, 1 - ON
      if (drs) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("DRS Enabled");
      } else {
        digitalWrite(LED_BUILTIN, LOW);
      }
      delay(250);
  }
}
void startWiFi()
{
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, Password);
  Serial.print("Attempting to connect to "); 
  Serial.println(SSID);
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(250);
 
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }
 
  Serial.print(F("Connection Successful | IP Address: "));
  Serial.println(WiFi.localIP());
}