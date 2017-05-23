#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (9, 10); 
struct package
{
  int id=0;
  char  text[1024] ="empty";
};

byte addresses[][6] = {"0"}; 

unsigned count = 0;

typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(98); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  delay(1000);

  if ( myRadio.available()) {
     //Serial.println("opa");
     while (myRadio.available())
    {
      //Serial.println("Ju desconfiada");
      myRadio.read( &data, sizeof(data) );
    }
    //Serial.print("Data: ");
    //Serial.println(data.id);
    count = data.id;  
  }
}


void loop()  
{

  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.temperature);
    Serial.println(data.text);
    int diff = data.id - count - 1;
    Serial.print("QTD Pacote perdido: ");
    Serial.println(diff);
    count = data.id; 
  }
}
