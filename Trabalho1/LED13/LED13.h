#ifndef LED13_H
#define LED13_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class LED13 { 
public:
	LED13();
	~LED13();
    void on();
	void off();
	void blink(int time);
	
};


#endif
