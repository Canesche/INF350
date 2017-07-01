/**
 * Exemplo básico para HC-12
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

String r;

void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  
  mySerial.print("1");

  if(mySerial.available() > 0){    
    digitalWrite(13,HIGH);
    delay(1000); 
    digitalWrite(13,LOW);
    delay(1000);
  }
}
