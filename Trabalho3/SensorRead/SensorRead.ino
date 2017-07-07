/*
 * Trabalho 3 Letra a
 * Autor: Michael Canesche - 68064
 * Professor: Ricardo dos Santos Ferreira
 * Última atualização: 25/04/17
 * Esse trabalho pode ser encontrado em: https://github.com/Canesche/INF350
 */
unsigned long time, tempoAntes;
const byte LED_PIN = 13; 
// TIME
#include <Time.h>
// DHT
#include "DHT.h"
// obs.: para a versão da bbt do dht mais recente, precisa dessa bbt
// link: https://github.com/adafruit/Adafruit_Sensor ultima visualizacao: 06/04/17
#include <Adafruit_Sensor.h> 
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
// Ultrassonic
#include <Ultrasonic.h>
#define TRIGGER_PIN 12
#define ECHO_PIN 11
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
// LDR
#define LDR_PIN A0

// variaveis globais
String s = "", c = "";
float valor, valorMIN = 9999, valorMAX = -9999, valorMEDIA = 0, valorAlertaMin = -9999, valorAlertaMax = 9999, valorAlertaMedia = -9999, valorMedioMediana = 0;
bool ligaMin = false, ligaMax = false, ligaMedia = false, ligaTempo = false, ligaLeitura = false;
unsigned int qtd = 0;
unsigned int tempo = 1000;
unsigned int time_agora = now();
int n = -1, j = 0, m = -1, k = -1, mk = 0;
int valores[20];

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT); // led 13 fica como saida
  while(!Serial){;}
  Tela_inicial();
  do {
     if(s != "1" && s != "2" && s != "3" && s != ""){
        Serial.println("Sensor " + s + " não disponivel!");
        Tela_inicial();
        s = "";
     }
     s = Serial.readString();  
  } while(s != "1" && s != "2" && s != "3");
  if(s == "1") Serial.println(" --- Sendor LDR escolhido! ---");
  else if(s == "2") Serial.println(" --- Sendor DHT22 escolhido! ---");
  else if(s == "3") Serial.println(" --- Sendor Ultrassonico escolhido! ---");
  tempoAntes = 0; // inicializa o tempo
}

void loop() {
  // atualiza o tempo 
  time = millis();

  if(time - tempoAntes > tempo){
      tempo = time = millis();
      if(s == "1"){ // LDR
        valor = analogRead(LDR_PIN);
        if(Verifica(valor,"Erro ao ler o sensor LDR!")) return;
        Serial.print("Intensidade: "); Serial.println(valor);
      } else if(s == "2"){ // DHT22
        valor = dht.readTemperature();
        if(Verifica(valor,"Erro ao ler o sensor DHT!")) return;
        Serial.print("Temperature: "); Serial.println(valor); 
      } else if(s == "3"){
        valor = ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
        if(Verifica(valor,"Erro ao ler o sensor Ultrassonic!")) return;
        Serial.print("distancia (cm): "); Serial.println(valor);
      }
      // pega o menor/maiores valores atuais
      if(ligaMin && valor < valorMIN) valorMIN = valor;
      if(ligaMax && valor > valorMAX) valorMAX = valor;
      if(ligaMedia) valorMEDIA = ((valorMAX + valor) / ++qtd);
      if(ligaTempo) time_agora = now(); 
      if(ligaLeitura){
          // ordena vetor
          for(int i = 0; i < n; i++)
              for(int j = i+1; j < n; j++)
                  if(valores[i] < valores[j]){
                      int aux = valores[i];
                      valores[i] = valores[j];
                      valores[j] = aux;  
                  }
          // calcula o valor medio da mediana
          valorMedioMediana = 0;
          for(int i = (n/2-mk/2); i < (n/2+mk/2); i++)
              valorMedioMediana += valores[i];
          valorMedioMediana /= mk;
          ligaLeitura = false;        
      }
      // valores para o vetor
      if(n > 0 && j < n) valores[j++] = valor;
      else j = 0;      
  }      
  
  // alertas
  if(valor < valorAlertaMin) digitalWrite(LED_PIN,HIGH);
  else digitalWrite(LED_PIN,LOW);
  if(valor > valorAlertaMax) digitalWrite(LED_PIN,HIGH); 
  else digitalWrite(LED_PIN,LOW);
  if(valor < valorAlertaMedia) digitalWrite(LED_PIN,HIGH);
  digitalWrite(LED_PIN,LOW);
  
  if(Serial.available()){
      c = Serial.readString();
      int ind1 = c.indexOf("/");
      int ind2 = c.indexOf("/",ind1+1);
      int ind3 = c.indexOf("/",ind2+1);
      if(c.substring(0,ind1) == "Min"){
          if(c.substring(ind1+1) == "ON"){
            Serial.println("Ligou o medidor de minimo!");
            ligaMin = true;
          }else if(c.substring(ind1+1) == "OFF"){
            Serial.println("Desligou o medidor de minimo!");
            ligaMin = false; 
          } else if(c.substring(ind1+1) == "PRINT"){
            Serial.print("Valor do MIN: ");
            Serial.println(valorMIN);  
          } else if(c.substring(ind1+1,ind2) == "Event"){
            Serial.println("Alerta Acionado!");
            valorAlertaMin = c.substring(ind2+1).toInt(); 
          }
      }else if(c.substring(0,ind1) == "Max"){
          if(c.substring(ind1+1) == "ON"){
              Serial.println("Ligou o medidor de maximo!");
              ligaMax = true;
          }else if(c.substring(ind1+1) == "OFF"){
              Serial.println("Desligou o medidor de maximo!");
              ligaMax = false; 
          } else if(c.substring(ind1+1) == "PRINT"){
              Serial.print("Valor do MAX: ");
              Serial.println(valorMAX);  
          } else if(c.substring(ind1+1,ind2) == "Event"){
              Serial.println("Alerta Acionado!");
              valorAlertaMax = c.substring(ind2+1).toInt(); 
          }  
      } else if(c.substring(0,ind1) == "Average"){
          if(c.substring(ind1+1) == "ON"){
              Serial.println("Ligou o medidor de media!");
              ligaMax = true;
          }else if(c.substring(ind1+1) == "OFF"){
              Serial.println("Desligou o medidor de media!");
              ligaMax = false; 
          } else if(c.substring(ind1+1) == "PRINT"){
              Serial.print("Valor da MEDIA: ");
              Serial.println(valorMAX);  
          } else if(c.substring(ind1+1,ind2) == "Event"){
              Serial.println("Alerta Acionado!");
              valorAlertaMax = c.substring(ind2+1).toInt(); 
          }  
      } else if(c.substring(0,ind1) == "Rate"){
          if(c.substring(ind1+1,ind2) == "SET"){
              Serial.println("Tempo de cada medida mudado!");
              tempo = c.substring(ind2+1).toInt(); 
          }
      } else if(c.substring(0,ind1) == "Clock"){
          if(c.substring(ind1+1) == "ON"){
              Serial.println("Ligou o medidor de tempo do arduino!");
              ligaTempo = true;
          }else if(c.substring(ind1+1) == "OFF"){
              Serial.println("Desligou o medidor de tempo do arduino!");
              ligaTempo = false; 
          } else if(c.substring(ind1+1) == "PRINT"){
              Serial.print("HORARIO: ");
              if(hour(time_agora) < 10) Serial.print("0");
              Serial.print(hour(time_agora)); Serial.print(":");
              if(minute(time_agora) < 10) Serial.print("0");
              Serial.print(minute(time_agora)); Serial.print(":");
              if(second(time_agora) < 10) Serial.print("0");
              Serial.println(second(time_agora));  
          }
      } else if(c.substring(0,ind1) == "Sample"){
          if(c.substring(ind1+1,ind2) == "SET"){
              n = c.substring(ind2+1).toInt();
              if(n > 20) n = 20;
              if(n < 1) n = 1;
              Serial.println("Setado a quantidade de leituras");
          } else if(c.substring(ind1+1) == "PRINT"){
              Serial.print("Valores: [");
              for(int i = 0; i < n; i++){
                  if(i == n-1) Serial.print(valores[i]); 
                  else{
                      Serial.print(valores[i]); Serial.print(",");
                  }
              }
              Serial.println("]");  
          }
      } else if(c.substring(0,ind1) == "Drop"){
          if(c.substring(ind1+1) == "ON"){
              if(k == -1 || m == -1) Serial.println("Ainda nao foi setado os valores de k e m");
              else{
                  Serial.println("Fazendo m leituras e descarta k leituras!");
                  ligaLeitura = true;  
              }
          }else if(c.substring(ind1+1) == "OFF"){
              Serial.println("Desligou o m leituras e descarta k leituras!");
              ligaLeitura = false;
          }else if(c.substring(ind1+1) == "PRINT"){
              Serial.print("Valor Medio da mediana: ");
              Serial.println(valorMedioMediana);
              ligaLeitura = false; 
          } else if(c.substring(ind1+1,ind2) == "SET"){
              m = c.substring(ind2+1,ind3).toInt();
              k = c.substring(ind3+1).toInt();
              if(m > k){
                if(k > 19) k = 19;
                if(k < 1) k = 1;
                if(m > 20) m = 20;
                if(m < 1) m = 1;
                mk = m - k;
              }
              Serial.print("m = "); Serial.println(m);
              Serial.print("k = "); Serial.println(k);
              Serial.print("m - k = "); Serial.println(mk);  
          }
      }
  }
}

/* FUNCOES CRIADAS */
void Tela_inicial(){
  Serial.println("Digite outro numero do sensor interessado:");
  Serial.println("[1] LDR");
  Serial.println("[2] DHT22");
  Serial.println("[3] Ultrassonico");  
}

bool Verifica(float v, String frase){

  if(isnan(v)){
    Serial.println(frase);
    return true;
  }
  return false;
}
