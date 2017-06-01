/*
 * Trabalho 5 tarefa 4
 * Autores: Michael Canesche - 68064
 *          Juliana Moreno - 75763
 * Professor: Ricardo dos Santos Ferreira
 * Última atualização: 30/05/17
 * Esse trabalho pode ser encontrado em: https://github.com/Canesche/INF350/trabalho5
 */
const byte LED_PIN = 13;
// RF24l01
#include <SPI.h>  
#include "RF24.h" 
// TIME
#include <Time.h>

// variaveis
#define LED_PIN 13
String s = "";

RF24 myRadio (9, 10);  // <===== CHANGE 9,10
byte addresses[][6] = {"0"};

struct package{
  int id=1, a = 0, u = 0;
  float t = 0.0, h = 0.0;
  String sensor = "";
};

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(98); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  delay(1000);
}


void loop() {

  if ( myRadio.available()){
      while (myRadio.available()){
        myRadio.read( &data, sizeof(data) );
      }
      s = data.sensor;
      Serial.println(data.id);
      if(s == "1"){ // LDR
        Serial.print("Intensidade: "); Serial.println(data.a);
      } else if(s == "2"){ // DHT22
        Serial.print("Temperature: "); Serial.println(data.t);
        Serial.print("Umidade: "); Serial.println(data.h);
      } else if(s == "3"){
        Serial.print("distancia (cm): "); Serial.println(data.u);
      }
  }
  delay(1000);
}
