#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <Time.h>

#define DHTTYPE DHT22
 
String p = "", nArquivo = "";
String data = "", hora = "";
int tempo;
String *sensores[3];
int nSensores;
File myFile;
int i1, i2;

void setup() {
    Serial.begin(9600);
    while (!Serial){;}

    if (!SD.begin(4)) {
        Serial.println("Erro na inicializacao!");
        return;
    }
    
  /*
    experimento1.txt
    600 11/04/17 08:00
    3
    dht 2 T_interna
    dht 3 T_externa
    ldr A0 Luminosidade
    Fim
  */
    myFile = SD.open("config.txt", FILE_READ); // leitura do arquivo config.txt 
    while(myFile.available()){
        nArquivo = myFile.readString(); // obtem o nome do arquivo
        p = myFile.readString();
        i1 = p.indexOf(" ");
        i2 = p.indexOf(" ", i1+1);
        tempo = p.substring(0,i1).toInt() * 1000; // transformando em ms
        data = p.substring(i1+1,i2);
        hora = p.substring(i2+1);
        // ajustando tempo
        i1 = data.indexOf("/");
        i2 = data.indexOf("/",i1+1);
        int i3 = hora.indexOf(":");
        // setTime(hr,min,sec,day,mnth,yr)
        setTime(hora.substring(0,i3).toInt(),hora.substring(i3+1).toInt(), 0,
                data.substring(0,i1).toInt(),data.substring(i1+1,i2).toInt(),data.substring(i2+1).toInt()); 
        nSensores = myFile.readString().toInt();
        *sensores = new String[nSensores];
        for(int i = 0; i < nSensores; i++){
            p = myFile.readString();
            i1 = p.indexOf(" ");
            i2 = p.indexOf(" ", i1+1);
            sensores[i][0] = p.substring(0,i1);    // nome do sensor
            sensores[i][1] = p.substring(i1+1,i2); // porta
            sensores[i][2] = p.substring(i2+1);    // apelido 
        }
        if(myFile.readString() == "Fim") break;
    }
    myFile.close();
    // grava o cabeçalho do arquivo .csv
    myFile = SD.open("experimento1.csv", FILE_WRITE);
    myFile.print("Hora;");
    for(int i = 0; i < nSensores; i++){
        myFile.print(sensores[i][2]);
        if(i != nSensores-1)
            myFile.print(";");
        else
            myFile.print("\n");
    }
    myFile.close();
}

void loop() {

    myFile = SD.open("experimento1.csv", FILE_WRITE);
    myFile.print(hour());
    myFile.print(":");
    myFile.print(minute());
    myFile.print(";");
    for(int i = 0; i < nSensores; i++){
        if(sensores[i][0] == "dht"){ // sensor dht
            DHT dht(sensores[i][0].toInt(),DHTTYPE);
            myFile.print(dht.readTemperature());
            myFile.print(";");  
        }else if(sensores[i][0] == "ldr"){ // sensor ldr
            #define LDR_PIN sensores[i][0]
            myFile.print(LDR_PIN);
            myFile.print(";");
        }
        if(i == nSensores-1)
            myFile.print("\n");
    }
    myFile.close();
    
    delay(tempo*1000);
/*
  Hora ;T_interna ;T_externa; Luminosidade
  08:01; 21; 23; 300;
  08:11; 21; 24; 400;
  08:21; 22; 26; 500;
*/
}
