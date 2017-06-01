/*
 * Trabalho 5 - tarefa 4
 * Autores: Michael Canesche - 68064
 *          Juliana Moreno - 75763
 * Professor: Ricardo dos Santos Ferreira
 * Última atualização: 25/04/17
 * Esse trabalho pode ser encontrado em: https://github.com/Canesche/INF350/Trabalho5
 */
const byte LED_PIN = 13;
// RF24l01
#include <SPI.h>  
#include "RF24.h" 
// TIME
#include <Time.h>
// DHT
#include "DHT.h"
// obs.: para a versão da bbt do dht mais recente, precisa dessa bbt
// link: https://github.com/adafruit/Adafruit_Sensor ultima visualizacao: 06/04/17
#include <Adafruit_Sensor.h> 
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
// Ultrassonic
#include <Ultrasonic.h>
#define TRIGGER_PIN 12
#define ECHO_PIN 11
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
// LDR
#define LDR_PIN A0

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


void setup(){
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);

  pinMode(LED_PIN, OUTPUT); // led 13 fica como saida
  while(!Serial){;}
  Tela_inicial();
  do {
     if(s != "1" && s != "2" && s != "3" && s != ""){
        Serial.println("Sensor " + s + " não disponivel!");
        Tela_inicial();
        s = "";
     }
     s = Serial.readString();  
  } while(s != "1" && s != "2" && s != "3");
  if(s == "1") Serial.println(" --- Sendor LDR escolhido! ---");
  else if(s == "2") Serial.println(" --- Sendor DHT22 escolhido! ---");
  else if(s == "3") Serial.println(" --- Sendor Ultrassonico escolhido! ---");
}

void loop(){
  myRadio.write(&data, sizeof(data)); 

  Serial.print("\nPackage:");
  Serial.println(data.id);
  
  data.id = data.id + 1;
  if(s == "1"){ // LDR
    data.a = analogRead(LDR_PIN);
    Serial.print("Intensidade: "); Serial.println(data.a);
    data.sensor = "1";
  } else if(s == "2"){ // DHT22
    data.t = dht.readTemperature();
    data.h = dht.readHumidity();
    Serial.print("Temperature: "); Serial.println(data.t);
    Serial.print("Umidade: "); Serial.println(data.h);
    data.sensor = "2"; 
  } else if(s == "3"){
    data.u = ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
    Serial.print("distancia (cm): "); Serial.println(data.u);
    data.sensor = "3";
  }
  
  delay(1000);
}

/* FUNCOES CRIADAS */
void Tela_inicial(){
  Serial.println("Digite outro numero do sensor interessado:");
  Serial.println("[1] LDR");
  Serial.println("[2] DHT22");
  Serial.println("[3] Ultrassonico");  
}
