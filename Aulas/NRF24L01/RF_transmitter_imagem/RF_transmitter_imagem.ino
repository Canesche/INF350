#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (9, 10);  // <===== CHANGE 9,10
byte addresses[][6] = {"0"};

struct package{
  //int id=1;
  char txt = '1';
};

typedef struct package Package;
Package data;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(98); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
  char t;
  if(Serial.available()){
    t = Serial.read();
    data.txt = t;
    myRadio.write(&data, sizeof(data)); 
  }
  delay(1000);
}
  
