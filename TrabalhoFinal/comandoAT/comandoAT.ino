//HC-12 AT Commander
//Autor Tom Heylen tomtomheylen.com
//The HC-12 commander mode runs at baud rate 9600

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

String r;

void setup() {
  Serial.begin(9600);
  /*Serial.println("---Baud Rate---");
  Serial.println("Type \"AT+Bxxxx\"");
  Serial.println("xxxx => 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200");
  Serial.println("---Canal de comunicacao---");
  Serial.println("AT+Czzz");
  Serial.println("zzz => 001 a 127");*/
  Serial.println("---Modulo Mode---");
  Serial.println("Type \"AT+yyy\"");
  Serial.print("yyy => FU1, FU2, FU3, FU4");
  Serial.println("\nEnter AT commands:");
  mySerial.begin(9600);
}

void loop(){
  
  if (Serial.available() > 0){
    mySerial.write(mySerial.read());
  }
  
  if (mySerial.available() > 0){
    r = Serial.readString();
    if(r == "1"){
      digitalWrite(13,HIGH);
      delay(1000); 
      digitalWrite(13,LOW);
      delay(1000);
    } else {
      Serial.print(r);
    }
  }
}
