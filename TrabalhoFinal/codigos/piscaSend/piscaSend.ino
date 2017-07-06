/**
 * Exemplo básico para HC-12
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

String r;
int pacoteAtual, pacoteAntes, dif, qtd;
boolean flag;

void setup() {
  Serial.begin(9600);
  /*Serial.println("---Modulo Mode---");
  Serial.println("\"AT+yyy\"");
  Serial.print("yyy => FU1, FU2, FU3, FU4");
  Serial.println("\nEnter AT commands:");
  */
  mySerial.begin(9600);
  //while(!Serial.available()){;}
 
  //mySerial.write(Serial.read());
  pacoteAtual = 0;
  pacoteAntes = 0;
  qtd = 0;
  dif = 0;
  flag = true;
  
}

void loop() {
  String s = "";
  while(mySerial.available() > 0){    
    //pacoteAntes = mySerial.read();
    char c = mySerial.read();
    if(c == '\n'){
      //pacoteAtual = s.toInt();
      break;
    }
    s += c;
  }
  if(s != "")
    pacoteAtual = s.toInt();

  if(pacoteAtual == 0)
    qtd = 0;

  Serial.print("pacote:" );
  Serial.println(pacoteAtual);
    
  dif = pacoteAtual - pacoteAntes - 1;
  if(dif >= 0 && dif < 100)
      qtd += dif;
  pacoteAntes = pacoteAtual;
  
  Serial.println(qtd);
 
  delay(500);
}

