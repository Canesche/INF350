#include "RemoteHC12.h"
#include <string.h>
#include <SoftwareSerial.h>

hc12::hc12(const int RX, const int TX, int id, SoftwareSerial *p){
	this->_TX = TX;
	this->_RX = RX;
	this->_id = id;
	this->p = p;
}

bool hc12::connect(){
	p->begin(9600);
	int resposta = 0;
	Serial.println("Connect Remoto");

	long tempoInicial = millis();

	while(millis() - tempoInicial < 20000){
		if(p->available()){
			resposta = p->read();
			p->write(1);
			break;
		}
	}
	if(resposta == 0){
		Serial.println("Falha, nao foi possivel conectar ao Arduino Local");
		return false;
	}
	Serial.println("Conectado ao Arduino Local");
	return true;
}

void hc12::PinMode(const int pino, int str){
	if(str == 0| str == 1| str == 2)
		pinMode(pino, str);
}

void hc12::Virtual(const int pino, int str){
	String stream = "1" + String(pino) + " " + String(str) + '\n';
	p->write(stream.c_str());
}

String hc12::ReadVirtual(const int pino){
	String value;
	String stream = "3" + String(pino) + "jmv" + '\n';
	p->write(stream.c_str());
	long tempoInicial = millis();
	while(true){
		String stream;
		if(p->available())
			return (String) p->read();
		if(millis() - tempoInicial >= 20000){
			return "-1";
		}
	}
	return stream;
}

void hc12::WriteVirtual(const int pino, float value){
	String stream = "2" + String(pino) + "" + String(value) + '\n';
	p->write(stream.c_str());
}
