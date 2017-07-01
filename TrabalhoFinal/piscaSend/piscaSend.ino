/**
 * Exemplo básico para HC-12
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

String r;
int pacote, pacoteAntes, dif, qtd;

void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  pacote = 0;
  qtd = 0;
}

void loop() {

  if(mySerial.available() > 0){    
    pacoteAntes = mySerial.readString().toInt();
    dif = pacote - pacoteAntes - 1;
    if(dif < 20){
      qtd += dif;
      digitalWrite(13,HIGH);
      delay(100); 
      digitalWrite(13,LOW);
      delay(100);
      pacote = pacoteAntes;
    }
    Serial.println(qtd);
  }
  
  
}
