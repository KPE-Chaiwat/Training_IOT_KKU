#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define SERVER_IP "192.168.10.208"
#define SERVER_PORT "1880"

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

int mockDataTemp= 10;
int mockDataHumi = 5;
void loop() {

if(mockDataTemp == 100){
   mockDataTemp =10;
  mockDataHumi= 5;
}else{

   mockDataTemp =mockDataTemp+10;
  mockDataHumi= mockDataHumi+5;
}
  //----data

 // Create JSON object
  DynamicJsonDocument jsonDoc(256);
  jsonDoc["temp"] =mockDataTemp; //42;
  jsonDoc["humi"] =mockDataHumi; //30;
  jsonDoc["email"] = "Xiatong@kkumail.com";


  // Serialize JSON to string
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  // Serialize JSON to string




  //--------
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
   // http.begin(client, "http://" SERVER_IP "":""SERVER_PORT"/http");  // HTTP   http://192.168.10.208:1880/http

  //http.begin(client, "http://192.168.10.208:1880/http");  TO COM  
  //
    http.begin(client, "http://192.168.10.183:1880/http");// to pi
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    //int httpCode = http.POST("{\"hello\":\"world\"}");
     int httpCode = http.POST(jsonString);
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
