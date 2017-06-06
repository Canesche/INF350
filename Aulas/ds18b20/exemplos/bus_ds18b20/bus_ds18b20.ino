/*
 * Material adaptado por Michael Canesche
 * Tutorial Original: 
 * Objetivo: Obter as temperaturas dos sensores que utilizam como protocolo o 1-wire
 */   
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_PIN 2
OneWire oneWire(ONE_WIRE_BUS_PIN);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*-----( Declare Variables )-----*/
// Veja o arquivo oneWire_adressFinder
// para obter o endereço físico do sensores
DeviceAddress Probe01 = { 0x28, 0xFF, 0x7B, 0x7B, 0x90, 0x15, 0x03, 0xB0 }; 
DeviceAddress Probe02 = { 0x28, 0xA8, 0x64, 0x01, 0x00, 0x00, 0x80, 0xEE };

void setup(){
  // start serial port to show results
  Serial.begin(9600);
  
  // Initialize the Temperature measurement library
  sensors.begin();
  
  // set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
  sensors.setResolution(Probe01, 10);
  sensors.setResolution(Probe02, 10);

  Serial.print("Numero de Sensores encontrados no barramento = ");  
  Serial.println(sensors.getDeviceCount());   
  Serial.println("Obtendo temperaturas... "); 
}

void loop(){
  
  // Comando para todos os barramentos para leitura de temperatura  
  sensors.requestTemperatures();  
  
  Serial.print("Probe 01 temperature is:   ");
  printTemperature(Probe01);

  Serial.print("Probe 02 temperature is:   ");
  printTemperature(Probe02);
 
  delay(1000); 
}

/*-----( Declaração de funções )-----*/
void printTemperature(DeviceAddress deviceAddress){
   float tempC = sensors.getTempC(deviceAddress);
   if (tempC == -127.00) {
      Serial.println("Erro ao obter a temperatura");
   } else {
      Serial.print("C: ");
      Serial.print(tempC);
      Serial.print(" F: ");
      Serial.println(DallasTemperature::toFahrenheit(tempC));
   }
}

