#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (9, 10);
byte addresses[][6] = {"123"};
char data;
/*
struct package
{
  int id=1;
  float temperature = 18.3;
  char  text[100] = "Lord Voldemort vive!!";
};


typedef struct package Package;
Package data;
*/

void setup()
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
  //String data;
  if(Serial.available()){
    data = Serial.read();
    myRadio.write(&data, sizeof(data)); 
      
    
/*
  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.temperature);
  Serial.println(data.text);
  data.id = data.id + 1;
  data.temperature = data.temperature+0.1;
 */
  //Serial.print("Enviado...");
  //Serial.println(data);
  delay(100);

  }
  
}
