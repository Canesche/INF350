/*----------------------------------------- 
  Programa : Teste LCD 16x2 com Keypad
  Autores: Juliana Moreno - 75763 
           Michael Canesche - 68064 
           Vanessa Vasconcelos - 77427 
  Professor: Ricardo Ferreira dos Santos
------------------------------------------*/
unsigned long time, tempoAntes;
///const byte LED_PIN = 13; 
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
#define LDR_PIN A1
// LCD
#include <LiquidCrystal.h>
// 18B20
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(3);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;  

// variaveis globais
float valor, valorMIN = 9999, valorMAX = -9999, valorAlertaMin = -9999, valorAlertaMax = 9999, valorAlertaMedia = -9999, valorMediana;
double valorMEDIA = 0;
bool ligaMin = false, ligaMax = false, ligaMedia = false, ligaTempo = false, ligaLeitura = false;
unsigned int qtd = 0;
unsigned int tempo = 1000;
unsigned int time_agora = now();
int n = 20, j = 0, m = -1, k = -1, mk = 0, vm = 0;
float valores[20];
bool escolha;
int botao, C = 0, tamS = 4, Ci = 0, Cl = 1, tmp = tempo;
//int tmp = tempo;
time_t horas;
String sensores[4] = {"LDR          ","DHT          ","ULTRASSONICO ","18B20        "};
String MenuInterno[7] = {"MINIMO ","MAXIMO ","MEDIA ","MEDIANA ","IMPRIME ","TEMPO ","RELOGIO "};
  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  

void setup(){  
    Serial.begin(9600);
    sensors.begin();
    lcd.begin(16, 2);  
    lcd.setCursor(0,0);  
    lcd.print("Escolha o sensor");  
    lcd.setCursor(0,1);
    lcd.print(sensores[0]);
    while(true){
       botao = analogRead(0);
       //Serial.println(botao);
       delay(160);
       lcd.setCursor(0,1);
       if (botao > 100 && botao < 200) {
           // para cima
           if(C > 0)
              lcd.print(sensores[--C]);
       } else if (botao > 200 && botao < 450){
           // para baixo
           if(C != tamS-1)
              lcd.print(sensores[++C]);
       } else if (botao > 600 && botao < 800){
          break;     
       }    
    }
    Menu();
    lcd.print(MenuInterno[0]);
    escolha = false;
}  
  
void loop(){  
     //Leitura do valor da porta analógica A0
     botao = analogRead(0);
     if(!escolha){
         delay(160);
         if (botao > 100 && botao < 200) {
             // para cima
             if(Ci > 0){
                Menu();
                lcd.print(MenuInterno[--Ci]);
             }
         } else if (botao > 200 && botao < 450){
             // para baixo
             if(Ci < 6){
                Menu();
                lcd.print(MenuInterno[++Ci]);
             }
         } else if (botao > 600 && botao < 800){
              if(Ci == 5)
                  tmp = tempo;
              escolha = true;    
         }    
    }
     
    // atualiza o tempo 
    time = millis();

    if(botao > 100 && botao < 450){
        escolha = false;
    }
  
    if(time - tempoAntes > tempo){
      tempoAntes = time = millis();
      if(C == 0){ // LDR
        valor = analogRead(LDR_PIN);
        /*if(Verifica(valor,"Erro ao ler o sensor LDR!")) return;
        Serial.print("Intensidade: "); Serial.println(valor);*/
      } else if(C == 1){ // DHT22
        valor = dht.readTemperature();
        /*if(Verifica(valor,"Erro ao ler o sensor DHT!")) return;
        Serial.print("Temperature: "); Serial.println(valor);*/ 
      } else if(C == 2){
        valor = ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
        /*if(Verifica(valor,"Erro ao ler o sensor Ultrassonic!")) return;
        Serial.print("distancia (cm): "); Serial.println(valor);*/
      } else if(C == 3){
        sensors.requestTemperatures();
        valor = sensors.getTempC(sensor1);
        Serial.println(valor);
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
      }
      // pega o menor/maiores valores atuais
      if(valor < valorMIN) valorMIN = valor;
      if(valor > valorMAX) valorMAX = valor;
      
      valorMEDIA = valorMEDIA + valor;
      qtd++;
      time_agora = now(); 

      if(n > 0 && j < n) valores[j++] = valor;
      else j = 0; 
      
      if(vm < n) vm++;
      // ordena vetor
      for(int i = 0; i < vm; i++)
          for(int j = i+1; j < vm; j++)
              if(valores[i] > valores[j]){
                  int aux = valores[i];
                  valores[i] = valores[j];
                  valores[j] = aux;  
              }
      // calcula o valor da mediana
      if(vm % 2 == 0){
        valorMediana = (valores[(vm-1)/2]+valores[vm/2])/2.0f;
      }else
        valorMediana = valores[vm/2];

      Serial.print("Valor: ");
      Serial.println(valor);
      Serial.print("Media: ");
      Serial.println(valorMEDIA/qtd);
      Serial.print("Mediana: ");
      Serial.println(valorMediana);
      Serial.print("[");
      for(int i = 0; i < vm; i++){
          Serial.print(valores[i]);
          if(i != vm-1)
              Serial.print(", ");
          else
              Serial.println("]");  
      }
      Serial.println();
  }      

    if(escolha && Ci == 0){ // MIN VALUE
        lcd.setCursor(0,1);
        lcd.print(MenuInterno[Ci]);
        lcd.print(valorMIN);
        escolha = false; 
    } else if(escolha && Ci == 1){ // MAX VALUE
        lcd.setCursor(0,1);
        lcd.print(MenuInterno[Ci]);
        lcd.print(valorMAX);
        escolha = false;
    } else if(escolha && Ci == 2){ // AVERAGE VALUE
        lcd.setCursor(0,1);
        lcd.print(MenuInterno[Ci]);
        lcd.print(valorMEDIA/qtd);
        escolha = false;
    } else if(escolha && Ci == 3){ // GET PRINT
        lcd.setCursor(0,1);
        lcd.print(MenuInterno[Ci]);
        lcd.print(valorMediana);
        escolha = false;     
    } else if(escolha && Ci == 4){ // GET PRINT
        lcd.setCursor(0,1);
        lcd.print(MenuInterno[Ci]);
        lcd.print(valor);
    } else if(escolha && Ci == 5){ // GET RATE
        lcd.setCursor(0,1);
        lcd.print(MenuInterno[Ci]);
        lcd.print(tmp);
        lcd.print(" ms");
        // direita
        if(botao < 100){
            delay(160);
            Menu();
            tmp+=500;  
        }else if(botao > 400 && botao < 600){
            delay(160);
            Menu();
            if(tmp > 500)
              tmp-=500;  
        }else if(botao > 600 && botao < 800){
            tempo = tmp; // seta o novo valor de t    
        }
        //Serial.println(botao);   
    } else if(escolha && Ci == 6){ // GET CLOCK
        lcd.setCursor(0,1);
        lcd.print(MenuInterno[Ci]);
        if(hour() < 10) lcd.print("0");
        lcd.print(hour());
        lcd.print(":");
        if(minute() < 10) lcd.print("0");
        lcd.print(minute());
        lcd.print(":");
        if(second() < 10) lcd.print("0");
        lcd.print(second());
    } 
  
  // alertas
  //if(valor < valorAlertaMin) digitalWrite(LED_PIN,HIGH);
  //else digitalWrite(LED_PIN,LOW);
  //if(valor > valorAlertaMax) digitalWrite(LED_PIN,HIGH); 
  //else digitalWrite(LED_PIN,LOW);
  //if(valor < valorAlertaMedia) digitalWrite(LED_PIN,HIGH);
  //digitalWrite(LED_PIN,LOW);
}

bool Verifica(float v, String frase){
  if(isnan(v)){
    Serial.println(frase);
    return true;
  }
  return false;
}

void mostra_endereco_sensor(DeviceAddress deviceAddress){
  for (uint8_t i = 0; i < 8; i++){
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void Menu(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(sensores[C]);
    lcd.setCursor(0,1);
}

