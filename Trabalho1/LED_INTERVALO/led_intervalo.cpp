#include "led_reduzindo.h"

led_intervalo::led_intervalo(byte pino,int int1, int qte1, int int2, int qt2)
{
    pinMode(pino,OUTPUT);
    this->pino = pino
    tempo = valor;
    this->int1 = int1;
    this->qtd1 = qtd1;
    this->int1 = int1;
    this->qtd2 = qtd2;
}

void led_intervalo::reinicia()
{
    // perguntar
}
        
void led_intervalo::pisca()
{    
    int i, t;
    for(i = 0; i < (qtd1+qtd2); i++)
    {
        t = (i < qt1) ? int1 : int2; // condição com operador ternário    
        digitalWrite(pino,HIGH);
        delay(t);
        digitalWrite(pino,LOW);
        delay(t);
    }
}


