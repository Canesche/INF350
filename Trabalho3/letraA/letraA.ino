/* LDR */
int ldrPin = A0; // pino do ldr (analogico)
/* ULTRASSONICO */
#include <Ultrasonic.h>
#define TRIGGER_PIN  11
#define ECHO_PIN     12
/* DHT */
#include "DHT.h"
#define DHTPIN 2   
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

String s = "";

void setup() {
    Serial.begin(9600);
    dht.begin();
    Serial.print("Digite qual sensor você quer: ");
    while(s == "" && Serial.available()){
      s = Serial.readString();
    }
    Serial.print("Sensor escolhido: ");
    Serial.println(s);
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  

  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.println(t);

  delay(2000);
  if(Serial.available()){  
    String s = Serial.readString();
    //Serial.println("Digitou: "+s);
  } 

}
