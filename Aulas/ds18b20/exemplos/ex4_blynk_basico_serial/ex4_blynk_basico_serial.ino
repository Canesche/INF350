/*
 * Material adaptado por Michael Canesche
 * Tutorial Original: ???
 * Objetivo: Exemplo básico do blynk
 */

#define BLYNK_PRINT DebugSerial
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>

// Coloque seu token obtido via aplicativo Blynk 
// Vá no configuração do projeto (botão hexagono)  
char auth[] = "3db38f13c8274b2c87eee83356d13e99";

void setup(){
  DebugSerial.begin(9600);

  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}

void loop(){
  Blynk.run();
}
