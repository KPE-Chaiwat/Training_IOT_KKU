#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "KKU-EE-IoT"
#define STAPSK "ee@kku1234"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;


ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);


  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for Connect to WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print("#.");
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.println("Channel: ");
  Serial.println(WiFi.channel());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Subnet Masks: ");
  Serial.println(WiFi.subnetMask());
  Serial.println("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("DNS address: ");
  Serial.println(WiFi.dnsIP());

  delay(1000);
}


void loop() {
}
