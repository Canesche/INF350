#include "UbidotsMicroESP8266.h"

#define TOKEN  "bc6ae9c4c5be9b9afc5089765641920c6abe1c49"  // Put here your Ubidots TOKEN
#define ID_1  "595f6a5f76254204c3befb63"  // Put here your Ubidots variable ID
//#define ID_2 "Your_variable_ID_here" // Put your variable ID here
#define WIFISSID "DPI-2" // Put here your Wi-Fi SSID
#define PASSWORD "CmI2bc4r44" // Put here your Wi-Fi password

Ubidots client(TOKEN);

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){
    float value1 = analogRead(0);
    //float value2 = analogRead(2)
    client.add(ID_1, value1);
    //client.add(ID_2, value2);
    client.sendAll(false);
    delay(5000);
}
