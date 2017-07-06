#include <Ultrasonic.h>
#include "HC12Remote.h"
#include <SoftwareSerial.h>

Ultrasonic ultra(10,11);
SoftwareSerial hc(2,3);
hc12 control(2, 3, 1, &hc);

void setup(){
  Serial.begin(9600);
  while(!control.connect()) {;};
  control.Virtual(5, INPUT);
}

void loop(){
  String leitura = control.ReadVirtual(5);
  Serial.print("Leitura: ");
  Serial.println(leitura);
}
  


