#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"


const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

AsyncWebServer server(80);


const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value to output to a PWM pin


String readOutputValue(){
  sensorValue = analogRead(analogInPin);
  
  // map it to the range of the PWM out
  outputValue = map(sensorValue, 0, 1023, 0, 100);
  
  return String(outputValue);
}
  
void setup() {
  // initialize serial communication at 115200
  Serial.begin(9600);

  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);// starts the WiFi server

  server.on("/outputValue", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send_P(200, "text/plain", readOutputValue().c_str());
  });
  
  // Start server
  server.begin();
}

void loop(){
  
}
