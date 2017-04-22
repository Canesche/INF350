#include "led_reduzindo.h"

led_reduzindo::led_reduzindo(byte pino, int valor)
{
    pinMode(pino,OUTPUT);
    this->pino = pino
    tempo = valor;
}

void led_reduzindo::reinicia()
{
    setTempo(1000);
}
        
void led_reduzindo::pisca()
{    
    digitalWrite(pino,HIGH);
    delay(tempo);
    digitalWrite(pino,LOW);
    delay(tempo);
    setTempo(tempo/2); // divide o tempo por 2
}

void led_reduzindo::setTempo(int t)
{
    tempo = t;
}

int led_reduzindo::getTempo() const
{
    return tempo;
}
