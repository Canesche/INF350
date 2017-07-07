/*** MQTTT ***/
#include <ESP8266WiFi.h>  //essa biblioteca já vem com a IDE. Portanto, não é preciso baixar nenhuma biblioteca adicional
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient

// ultrassonic
#define TRIGGER 5 // D1 = 5 (GPIO)
#define ECHO    4 // D2 = 4 (GPIO)

#include "Ultrasonic.h"
Ultrasonic ultrasonic(TRIGGER,ECHO);
 
//defines
#define SSID_REDE     "DPI-2"  
#define SENHA_REDE    "CmI2bc4r44"  
#define INTERVALO_ENVIO_MQTT 1000  

#define ID_MQTT  "canesche"     //id mqtt (para identificação de sessão)
  
//constantes e variáveis globais
const char* BROKER_MQTT = "mqtt.dti.ufv.br"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1888;                      // Porta do Broker MQTT
long lastConnectionTime, lastMQTTSendTime; 
WiFiClient client;
WiFiClient clientMQTT;
PubSubClient MQTT(clientMQTT); // Instancia o Cliente MQTT passando o objeto clientMQTT
  
void initWiFi(void);
void initMQTT(void);
void reconectWiFi(void); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void); 

int i = 0;
 
void initWiFi() {
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID_REDE);
    Serial.println("Aguarde");
    reconectWiFi();
    pinMode(ECHO, INPUT); 
    pinMode(TRIGGER, OUTPUT);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    Serial.println("desligou");
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
    Serial.println("ligou");
  }

}
   
void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}
   
   
void reconnectMQTT() {
    while (!MQTT.connected())  {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            //MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } else{
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}
   
void reconectWiFi(){
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
          
    WiFi.begin(SSID_REDE, SENHA_REDE); // Conecta na rede WI-FI
      
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID_REDE);
    Serial.print(" IP obtido: ");
    Serial.println(WiFi.localIP());
}
  
void VerificaConexoesWiFIEMQTT(void){
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita 
    reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}

float valor = 0, valorMIN = 9999, valorMAX = -9999, valorMEDIA = 0, valorAlertaMin = -9999, valorAlertaMax = 9999, valorAlertaMedia = -9999;
bool ligaMin = false, ligaMax = false, ligaMedia = false;
int qtd = 0;
  
void setup(){  
    Serial.begin(115000);
    lastConnectionTime = 0; 
    lastMQTTSendTime = 0;
    initWiFi();
    initMQTT();
}
  
//loop principal
void loop(){
    VerificaConexoesWiFIEMQTT(); 
    
    long microsec = ultrasonic.timing();
    valor = ultrasonic.convert(microsec, Ultrasonic::CM);

    // verifica 
    if(MQTT.subscribe("publico/jmv/envia/ligamin") == '0')
      ligaMin = true;
    else
      ligaMin = false;
      
    if(MQTT.subscribe("publico/jmv/envia/ligaMax") == '0')
      ligaMax = true;
    else
      ligaMax = false;
      
    if(MQTT.subscribe("publico/jmv/envia/ligaMedia") == '0')
      ligaMedia = true;
    else
      ligaMedia = false;

    if(ligaMin && valor < valorMIN) valorMIN = valor;
    if(ligaMax && valor > valorMAX) valorMAX = valor;
    if(ligaMedia){
        qtd++; 
        valorMEDIA += valor;
    }   
    
    //verifica se é o momento de enviar informações via MQTT
    if ((millis() - lastMQTTSendTime) > INTERVALO_ENVIO_MQTT){
       if(ligaMin)
          MQTT.publish("publico/jmv/recebe/valorMin", String(valorMIN).c_str());
       if(ligaMax)
          MQTT.publish("publico/jmv/recebe/valorMax", String(valorMAX).c_str());
       if(ligaMedia)
          MQTT.publish("publico/jmv/recebe/valorMedia", String(valorMEDIA/qtd).c_str());
          
       //Serial.println(valor);
       // imprime o valor do sensor
       MQTT.publish("publico/jmv/recebe/valor", String(valor).c_str());
    }

    MQTT.loop();
    //delay(1000);
}
