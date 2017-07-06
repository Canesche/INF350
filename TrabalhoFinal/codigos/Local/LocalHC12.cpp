#include "LocalHC12.h"
#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>

LocalHC12::LocalHC12(const int RX, const int TX, int id, SoftwareSerial *p){
	 this->_TX = TX;
	 this->_RX = RX;
	 this->_id = id;
	 this->p = p;
}

bool LocalHC12::connect(){
	p->begin(9600);
	long tempoInicial = millis();
	p->write(1);
	int resposta = 0;
	Serial.println("Connect Local");
	while(millis() - tempoInicial < 5000){
		if(p->available()){
			resposta = p->read();
			break;
		}
	}
	if(resposta == 0){
		Serial.println("Falha, nao foi possivel conectar ao Arduino Remoto");
		return false;
	}

	Serial.println("Conectado ao Arduino Local");
	return true;
}

void LocalHC12::setChave(String chave){
	this->chave = chave;
}

void LocalHC12::verify(Ubidots client){

	String stream;
	while(p->available()){
		char c = p->read();
		stream += (char) c;
		if(c == '\n'){
			break;
		}		
	}

	String type;
	type = stream.substring(0, stream.indexOf(" "));
	stream = stream.substring(stream.indexOf(" ")+1);
	String pin;
	pin = stream.substring(0, stream.indexOf(" "));
	String value;
	value = stream.substring(stream.indexOf(" ")+1);

	if(type == "1"){
		client.add(pin.c_str(), 0);
    	client.sendAll();
    }else if(type == "2"){
    	client.add(chave.c_str(), value.toFloat());
    	client.sendAll();
    }else if(type == "3"){
    	float leitura = client.getValue(chave.c_str());
    	p->write(leitura);
    }
		

}