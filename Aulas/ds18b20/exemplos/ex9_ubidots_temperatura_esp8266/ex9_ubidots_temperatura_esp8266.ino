/*
 * Material adaptado por Michael Canesche
 * Tutorial Original: Página do Ubidots
 * Objetivo: Enviar o dado de temperatura para o site do Ubidots usando o esp8266
 */

#include <UbidotsESP8266.h>
#include <SoftwareSerial.h> 

#define SSID "Office"  // por exemplo dti2
#define PASS "pass123" // senha do dti2

// token (api key)
#define TOKEN "WzcXyqYlv9uKgwqhvyI6K0WfpFBkuI"

Ubidots client(TOKEN);

void setup() {
    Serial.begin(9600);
    client.wifiConnection(SSID, PASS);
}

void loop() {
    float temperature = analogRead(A0);
    // numero da chave obtido ao criar a variavel
    client.add("56cc97c9762542282c26c7e0", temperature);
    client.sendAll();
}
