#ifndef LED_INTERVALO_H
#define LED_INTERVALO_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class led_ciclo
{
    public:
        led_ciclo(byte pino = 13,int valor_inicial = 0, int maximo = 3000);
        void passo(int p);
        void pisca();
    private:
        byte pino;
        int vIni, vMax, passo;
};

#endif
