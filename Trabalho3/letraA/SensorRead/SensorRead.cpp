#include "SensorRead.h" 

const byte LED_PIN = 13; 

// DHT
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
// Ultrassonic
#include <Ultrasonic.h>
#define TRIGGER_PIN 12
#define ECHO_PIN 11
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
// LDR

// construtor
SensorRead::SensorRead(){
    pinMode(LED_PIN, OUTPUT); //pino 13 pisca    
    // SENSOR DHT    
    dht.begin();     
    // SENSOR ULTRASSONIC
    
    // SENSOR LDR 
}

//<<destructor>>
SensorRead::~SensorRead(){/*nothing to destruct*/}


