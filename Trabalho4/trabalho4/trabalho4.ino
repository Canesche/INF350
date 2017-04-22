#include <SPI.h>
#include <SD.h>

String p = "", nArquivo = "";
String data = "", hora = "";
int tempo;
String *sensores; 

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
    File myFile = SD.open("config.txt"); // leitura do arquivo config.txt 
    while(myFile.available()){
        nArquivo = myFile.readString(); // obtem o nome do arquivo
        p = myFile.readString();
        int iPrimeiro = p.indexOf(" ");
        int iSegundo = p.indexOf(" ", iPrimeiro+1);
        int iTerceiro = p.lastIndexOf(" ");
        tempo = p.substring(0,iPrimeiro).toInt();
        data = p.substring(iPrimeiro+1,iSegundo);
        hora = p.substring(iSegundo+1);
        int nSensores = myFile.readString().toInt();
        sensores = new String[nSensores];
        for(int i = 0; i < nSensores; i++)
            sensores[i] = myFile.readString();
        if(myFile.readString() == "Fim") break;
    }
}

void loop() {

/*
  Hora ;T_interna ;T_externa; Luminosidade
  08:01; 21; 23; 300;
  08:11; 21; 24; 400;
  08:21; 22; 26; 500;
*/
}
