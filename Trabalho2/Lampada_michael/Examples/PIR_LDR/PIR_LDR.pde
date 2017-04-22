#include <Lampada.h>

Lampada l(3);// lampada pino 3 

void setup(){
l.PIR(4);
l.LDR(5);
}

void loop(){
  l.verifica();
  delay(1000);
}
