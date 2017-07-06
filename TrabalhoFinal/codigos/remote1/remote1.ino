#include <Ultrasonic.h>
#include "HC12Remote.h"
#include <SoftwareSerial.h>

Ultrasonic ultra(10,11);
SoftwareSerial hc(2,3);
hc12 control(2, 3, 1, &hc);

void setup(){
  Serial.begin(9600);
  while(!control.connect()) {;};
  control.Virtual(5, OUTPUT);
}

void loop(){
  float cmMsec;
  long microsec = ultra.timing();
  cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  control.WriteVirtual(5, cmMsec);
}
