#ifndef LOCALHC12_H
#define LOCALHC12_H

#include "Arduino.h"
#include <string.h>
#include <SoftwareSerial.h>
#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>
#include <string.h>

class LocalHC12{
private:
	int TX;
	int RX;
	int id;
	SoftwareSerial *p;
	String chave;
public:
	LocalHC12(const int RX, const int TX, int id, SoftwareSerial*);
	bool connect();
	void verify(Ubidots client);
	void setChave(String);

};

#endif
