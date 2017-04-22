#ifndef LED_REDUZINDO_H
#define LED_REDUZINDO_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class led_reduzindo
{
    public:
        led_reduzindo(byte = 13,int = 1000);
        void reinicia();
        void pisca();
        void setTempo(int);
        int getTempo() const;
    private:
        byte pino;
        int tempo;
};

#endif
