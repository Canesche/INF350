#ifndef LED_PISCANDO_H
#define LED_PISCANDO_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class led_piscando{
    private:
    	const int pin;
        int tempo, passo;    
    public:
        // construtores
        led_piscando(int pino = 13, int valor_inicial = 1000); // esse construtor é igual a quatro outros construtores
        // destrutor
        ~led_piscando(){};
        // construtor de copia
        led_piscando(const led_piscando &led);
        // funções membros
        void pisca();
        void incrementa_valor(int v);
        void reinicia();
        void setTempo(int t);
        int getTempo() const;
        void setPasso(int p);
        int getPasso() const;

};


#endif
