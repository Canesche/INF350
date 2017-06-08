/*
 * Material adaptado por Michael Canesche
 * Tutorial Original: exemplo blynk biblioteca
 * Objetivo: Conectar o blynk com o arduino via ethernet
 */
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

#define W5100_CS  10
#define SDCARD_CS 4

void setup(){
  // Debug console
  Serial.begin(9600);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  Blynk.begin(auth);
  // Você pode especificar o servidor
  //Blynk.begin(auth, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8442);
  // For more options, see Boards_Ethernet/Arduino_Ethernet_Manual example
}

void loop(){
  Blynk.run();
}

