/*
 * Material adaptado por Michael Canesche
 * Tutorial Original: FilipeFlop
 * Objetivo: Encontrar os endereços físicos dos sensores que utilizam como protocolo o 1-wire
 */
 
#include <OneWire.h>
#include <DallasTemperature.h>
 
// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 2
 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);
 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
 
void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();
}
 
void mostra_endereco_sensor(DeviceAddress deviceAddress){
  for (uint8_t i = 0; i < 8; i++){
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
 
void loop(){
  // Le a informacao do sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);
  // Atualiza temperaturas minima e maxima
  
  // Mostra dados no serial monitor
  Serial.print("Temp C: ");
  Serial.println(tempC);
   
  delay(3000);
}

