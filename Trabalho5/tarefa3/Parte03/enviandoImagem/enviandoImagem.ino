#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (9, 10);
byte addresses[][6] = {"0"};
char entrada=0;


void setup(){
  Serial.begin(115200);
  //delay(1000);
  myRadio.begin();  
  myRadio.setChannel(66); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  //delay(1000);
}
void loop(){
  if (Serial.available() > 0) {
    //myRadio.write(&data, sizeof(data)); 
    entrada = Serial.read();
    myRadio.write(&entrada, sizeof(entrada)); 
    //data.imput = Serial.readString();  
    //data.imput = Serial.read();
    //Serial.print(data.imput);
    Serial.println(entrada);
    Serial.println("Texto Enviado....");
  } //Serial.println("Esperando....");
  delay (10);
}

