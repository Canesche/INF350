#ifndef LED_INTERVALO_H
#define LED_INTERVALO_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class led_intervalo
{
    public:
        led_intervalo(byte pino = 13,int int1 = 3000, int qte1 = 3, int int2 = 1000, int qt2 = 5);
        void reinicia();
        void pisca();
    private:
        byte pino;
        int int1, int2, qt1, qt2;
};

#endif
