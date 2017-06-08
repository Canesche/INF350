/*
 * Material adaptado por Michael Canesche
 * Tutorial Original: ???
 * Objetivo: Conectar o blynk com o arduino e o sensor dht via serial
 */
#define BLYNK_PRINT DebugSerial

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#include <BlynkSimpleStream.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3db38f13c8274b2c87eee83356d13e99";

#define DHTPIN 2 // What digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup(){
  // Debug no console
  DebugSerial.begin(9600);

  // Blynk irá funcionar através do Serial
  // Não leia ou escreva o serial manualmente em seu código
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  dht.begin();

  // Configura uma função para ser chamado cada segundo
  timer.setInterval(1000L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
