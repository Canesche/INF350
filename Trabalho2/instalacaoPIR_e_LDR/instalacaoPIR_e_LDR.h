#ifndef INSTALACAOPIR_E_LDR_H
#define INSTALACAOPIR_E_LDR_H

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class instalacaoPIR_e_LDR{
    private:
    	const int pin;   
    public:
        // construtores
        lampada(int pino); // esse construtor é igual a quatro outros construtores
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
