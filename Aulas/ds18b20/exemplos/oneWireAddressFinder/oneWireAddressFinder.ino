/*
 * Material adaptado por Michael Canesche
 * Tutorial Original: http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
 * Objetivo: Encontrar os endereços físicos dos sensores que utilizam como protocolo o 1-wire
 */
#include <OneWire.h>

OneWire  ds(2); // Conectando seu sensor 1-wire para o pino 2 (pode ser qualquer outro pino)

void setup(void) {
    Serial.begin(9600);
    discoverOneWireDevices();
}

// função responsável em descobrir os endereços físicos
void discoverOneWireDevices() {
    byte i, present = 0, data[12], addr[8];
    
    Serial.print("Looking for 1-Wire devices...\n\r");
    while(ds.search(addr)) {
        Serial.print("\n\rEncontrado dispositivo \'1-Wire\' com endereço:\n\r");
        for( i = 0; i < 8; i++) {
            Serial.print("0x");
            if (addr[i] < 16) 
                Serial.print('0');
            Serial.print(addr[i], HEX);
            if (i < 7)
                Serial.print(", ");
        }
        if (OneWire::crc8( addr, 7) != addr[7]) {
            Serial.print("CRC não válido!\n");
            return;
        }
    }
    Serial.print("\n\r\n\r É só isso! \r\n");
    ds.reset_search();
    return;
}

void loop(void) {
    // nada a fazer
}


