// NRF024
#include <SPI.h>  
#include "RF24.h"

// 18b20
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

// ledRGB
int R = 3; // Pin 3
int G = 4; // Pin 4
int B = 5; // Pin 5

RF24 myRadio (9, 10);
byte addresses[][6] = {"0"};

struct package{
  int id = 1;
  float temperature = 18.3;
  int red = 0;
  int green = 0;
  int blue = 0; 
};

typedef struct package Package;
Package data;

void setup(){
  analogWrite(R, 0);
  analogWrite(G, 0);
  analogWrite(B, 0);
  
  Serial.begin(115200);//115200
  sensors.begin();
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(98); // configura o canal
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS) ; 
  myRadio.openWritingPipe(addresses[0]);
  myRadio.openReadingPipe(1,addresses[0]);

  myRadio.startListening();
   
  //myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop(){

  sensors.requestTemperatures();
  
  // enviando
  data.id = data.id + 1;
  data.temperature = sensors.getTempC(sensor1);

  Serial.println(data.temperature);
  myRadio.write(&data, sizeof(data));
  delay(500);
  myRadio.startListening();
  delay(500);
  
  // recebendo
  if (myRadio.available()){
    while (myRadio.available()){
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("Recebi: ");
    analogWrite(R, data.red);
    analogWrite(G, data.green);
    analogWrite(B, data.blue); 
  }
  myRadio.stopListening();
  
  delay(500);
}
