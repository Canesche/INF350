#ifndef REMOTEHC12_H
#define REMOTEHC12_H

#include "Arduino.h"
#include <String.h>
#include <SoftwareSerial.h>

class hc12{
private:
	int _TX;
	int _RX;
	int _id;
	SoftwareSerial *p;
public:
	hc12(const int, const int, int, SoftwareSerial*);
	bool connect();
	void PinMode(const int, int);
	void Virtual(const int, int);
	String ReadVirtual(const int);
	void WriteVirtual(const int, float);
	
};



#endif

