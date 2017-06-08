/*
 * Material adaptado por Michael Canesche
 * Tutorial Original: Página do Ubidots
 * Objetivo: Enviar o dado de temperatura para o site do Ubidots
 */

#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>
#define TOKEN  "WzcXyqYlv9uKgwqhvyI6K0WfpFBkuI"  

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 177);
Ubidots client(TOKEN);

void setup() {
    Serial.begin(9600);
    if (Ethernet.begin(mac) == 0) {
          Ethernet.begin(mac, ip);
    }
    delay(1000);
}
void loop() {
    float temperature = analogRead(A0);
    client.add("56cc97c9762542282c26c7e0", temperature);
    client.sendAll();
    delay(5000);
}
