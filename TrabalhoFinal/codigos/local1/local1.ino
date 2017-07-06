#include "LocalHC12.h"
#include <Ethernet.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <UbidotsEthernet.h>
#define ID  "Your_variable_ID_here"  // Put here your Ubidots variable ID
#define TOKEN  "2Gpv6FS2hRH9Xzeq9cUIVoajYpIvKT"  // Put here your Ubidots TOKEN


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

Ubidots client(TOKEN);

SoftwareSerial hc(2,3);

LocalHC12 local(2, 3, 1, &hc);

void setup(){
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // try to congifure using IP address instead of DHCP:
      Ethernet.begin(mac, ip);
    }
    // give the Ethernet shield a second to initialize:
    delay(1000);
  
  while(!local.connect()) {;};
  
  local.setChave("593014a376254205f3346361");
  
}

void loop(){
  local.verify(client);

}
