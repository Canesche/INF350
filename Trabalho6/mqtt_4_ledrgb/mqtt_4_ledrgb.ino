#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(200,235,131,37);
//IPAddress server(172, 16, 0, 2);
#define RED 3
#define BLUE 6
#define GREEN 5
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    if ( payload[i] == 'r' ) analogWrite(RED,255);
    if ( payload[i] == 'R' ) analogWrite(RED,0);
    if ( payload[i] == 'b' ) analogWrite(BLUE,255);
    if ( payload[i] == 'B' ) analogWrite(BLUE,0);
    if ( payload[i] == 'g' ) analogWrite(GREEN,255);
    if ( payload[i] == 'G' ) analogWrite(GREEN,0);  
  }
  Serial.println();
}

EthernetClient ethClient;
PubSubClient client(ethClient);
int i = 0;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      String msg = String(i); i++;
      client.publish("publico/outTopic",msg.c_str());
      // ... and resubscribe
      client.subscribe("publico/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


long int t,last; 

void setup()
{
  Serial.begin(9600);

  client.setServer("mqtt.dti.ufv.br", 1888);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);
  t = last = millis();
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
}

void loop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  t = millis();
  if ( t - last > 1000 ) {
     last = t;
     String msg = String(t);
     client.publish("publico/outTopic",msg.c_str());
  }
}
