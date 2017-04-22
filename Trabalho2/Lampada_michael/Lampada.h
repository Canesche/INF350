#ifndef Lampada_H
#define Lampada_H

#include "Arduino.h"


#define _MAX_S 10
class Lampada { 
private:
    int Pino;
    int pirs[_MAX_S];
    int ldrs[_MAX_S];
    int p_cnt,l_cnt;
public:
	Lampada(int pino);
	~Lampada();
    void verifica();
	void PIR(int pino);
	void LDR(int pino);
};

#endif
