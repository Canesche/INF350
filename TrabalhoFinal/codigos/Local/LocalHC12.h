#ifndef LOCALHC12_H
#define LOCALHC12_H

#include "Arduino.h"
#include <String.h>
#include <SoftwareSerial.h>
#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>

class LocalHC12{
private:
	int _TX;
	int _RX;
	int _id;
	SoftwareSerial *p;
	String chave;
public:
	LocalHC12(const int RX, const int TX, int id, SoftwareSerial*);
	bool connect();
	void verify(Ubidots client);
	void setChave(String);

};

#endif