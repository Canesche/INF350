// ubidots
#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>

#define TOKEN  " "  // Put here your Ubidots TOKEN
#define ID_temp  " "  // id da temperatura
#define ID_R " " // id do led vermelho
#define ID_G " " // id do led verde
#define ID_B " " // id do led azul

// NRF024 
#include "RF24.h"

RF24 myRadio (9, 8); // o pino 10 ja eh ocupado pelo ethernet
byte addresses[][6] = {"0"};

struct package{
  int id = 1;
  float temperature = 0.0;
  int red = 0;
  int green = 0;
  int blue = 0; 
}; 

typedef struct package Package;
Package data;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xCC, 0x04 };
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(235, 243, 131, 37);

Ubidots client(TOKEN);

int R,G,B;

void setup(){

    Serial.begin(115200);//115200
    delay(1000);
    myRadio.begin();  
    myRadio.setChannel(98); // configura o canal
    myRadio.setPALevel(RF24_PA_MAX);
    myRadio.setDataRate(RF24_250KBPS) ; 
    myRadio.openWritingPipe(addresses[0]);
    myRadio.openReadingPipe(1,addresses[0]);
    
    myRadio.startListening();
     
    delay(1000);
    
    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // try to congifure using IP address instead of DHCP:
      Ethernet.begin(mac, ip);
    }
    // give the Ethernet shield a second to initialize:
    delay(1000);
}
void loop(){

    // recebendo
    myRadio.startListening();
    delay(500);
    if (myRadio.available()){
      while (myRadio.available()){
        myRadio.read( &data, sizeof(data) );
      }
      Serial.print("Recebi: ");
      client.add(ID_temp, data.temperature);
      //client.sendAll(false); 
    }
    myRadio.stopListening();
    delay(500);

    // recebe do ubidots os valores do rgb
    R = client.getValue(ID_R);
    G = client.getValue(ID_G);
    B = client.getValue(ID_B);

    // enviando para o outro radinho
    data.id = data.id + 1;
    data.red = R;
    data.green = G;
    data.blue = B;
    myRadio.write(&data, sizeof(data));
    
    delay(5000);
}
