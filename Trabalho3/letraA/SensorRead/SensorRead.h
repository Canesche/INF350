#ifndef SENSORREAD_H
#define SENSORREAD_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class SensorRead { 
public:
	SensorRead(); // construtor
    ~SensorRead(); // destrutor	
};


#endif
