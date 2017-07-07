#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

float valor, valorMIN = 9999, valorMAX = -9999, valorMEDIA = 0, valorAlertaMin = -9999, valorAlertaMax = 9999, valorAlertaMedia = -9999, valorMedioMediana = 0;
bool ligaMin = false, ligaMax = false, ligaMedia = false, ligaTempo = false, ligaLeitura = false;

// Update these with values suitable for your network.
byte mac[]    = { 0xDE, 0xAD, 0xBE, 0xEF, 0xCC, 0x04 };
IPAddress ip(200,235,131,37);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++){
    Serial.print((char)payload[i]);
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

void setup(){
  Serial.begin(9600);

  client.setServer("mqtt.dti.ufv.br", 1888);
  //client.setServer("broker.mqttdashboard.com", 1883);
  //client.setServer("test.mosca.io", 1883);
  //client.setServer("test.mosquitto.org", 1883);
  //client.setServer("broker.hivemq.com", 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  //Ethernet.begin(mac);
  // Allow the hardware to sort itself out
  delay(1500);
  t = last = millis();
}

void loop(){

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(client.subscribe("publico/jmv/ligamin")){   
     Serial.println("ooooppppaaa");
  }
  
  t = millis();
  if ( t - last > 1000 ) {
     valor = analogRead(0);

     if(valor < valorMIN) valorMIN = valor;
     if(valor > valorMAX) valorMAX = valor;
     
     //int r = client.subscribe("publico/inTopic");
     Serial.println(client.subscribe("publico/jmv/ligamin"));
     
     /*if(r == 1){
        Serial.println("opa");
     } else {
        Serial.println("nao ligou"); 
     }*/
     last = t;
     String msg = String(t);
     client.publish("publico/jmv/valor",String(valorMIN,1).c_str());
     client.publish("publico/jmv/teste",msg.c_str());
  }
  
}
