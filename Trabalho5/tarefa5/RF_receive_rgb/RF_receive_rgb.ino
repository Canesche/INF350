#include <SPI.h>  
#include "RF24.h" 

/* RGB */
int R = 2, G = 4, B = 2;
bool sinal = false;

/** cores escolhidas
 * verde = sinal com 0 ate 1 perda 
 * amarelo = sinal com 2 ate 4 perda 
 * vermelho = sinal acima de 4 perdas
 * azul = nao recebeu nenhum sinal (so para caso que nao esteja config. direito)
 */

RF24 myRadio (9, 10); 
struct package{
  int id=0;
  char  text[1024] ="empty";
};

byte addresses[][6] = {"0"}; 

unsigned count = 0;

typedef struct package Package;
Package data;


void setup() 
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(98); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  delay(1000);

  if ( myRadio.available()) {
     while (myRadio.available()){
     myRadio.read( &data, sizeof(data) );
    }
    count = data.id;  
  }
}


void loop()  
{

  if ( myRadio.available()){
    while (myRadio.available()){
      myRadio.read( &data, sizeof(data) );
    }
    sinal = true;
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.temperature);
    Serial.println(data.text);
    int diff = data.id - count - 1;
    Serial.print("QTD Pacote perdido: ");
    Serial.println(diff);
    count = data.id;
    limpa();
    if(diff < 2){
      analogWrite(G,255);
    }else if(diff < 4){
      analogWrite(R,255);
      analogWrite(G,255);   
    }else{
      analogWrite(R,255);
    }
  }

  if(!sinal)
    analogWrite(B,255);

  //delay(500);
}

void limpa(){
   analogWrite(R,0); 
   analogWrite(G,0); 
   analogWrite(B,0);  
}
