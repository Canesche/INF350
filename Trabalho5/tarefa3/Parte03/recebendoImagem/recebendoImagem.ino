#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (9, 10); 
byte addresses[][6] = {"0"}; 
int msg[1];
int leitura=0;
String conteudo = "";
int i=0;
char saida=0;

void setup() {
  Serial.begin(115200);
  myRadio.begin(); 
  myRadio.setChannel(66); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop(){
    if ( myRadio.available())   {
      while (myRadio.available()) {
        myRadio.read( &saida, sizeof(saida) );
      }
      Serial.print(saida);
    }
}
