//HC-12 AT Commander
//Autor Tom Heylen tomtomheylen.com
//The HC-12 commander mode runs at baud rate 9600

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

String r;
int pacote;
bool passou;

void setup() {
  Serial.begin(9600);
  Serial.println("---Modulo Mode---");
  Serial.println("\"AT+yyy\"");
  Serial.print("yyy => FU1, FU2, FU3, FU4");
  Serial.println("\nEnter AT commands:");
  mySerial.begin(9600);
  pacote = 0;
  passou = false;
  while(!Serial.available()){;}
  mySerial.write(Serial.read());
  
}

void loop(){
  
  mySerial.print(pacote);
  pacote++;
  Serial.println(pacote);

  if(mySerial.available()){
    Serial.println("opa");  
  }
  
  delay(200);
}
