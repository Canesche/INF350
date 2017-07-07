#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (9, 10);
byte addresses[][6] = {"0"};

struct package{
  int id = 1;
  float temperature = 0.0;
  int led = 0;
};

typedef struct package Package;
Package data;

void setup(){
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(98); // configura o canal
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate(RF24_250KBPS); 
  myRadio.openWritingPipe(addresses[0]);
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
   
  delay(1000);
}

void loop(){

  // enviando
  data.id = data.id + 1;
  data.temperature = data.temperature+0.1;
  myRadio.write(&data, sizeof(data));
  

  // recebendo
  myRadio.startListening();
  delay(1000);
  if (myRadio.available()){
    while (myRadio.available()){
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("Recebi: ");
    
    
  }
  myRadio.stopListening();
  
  delay(1000);
}
