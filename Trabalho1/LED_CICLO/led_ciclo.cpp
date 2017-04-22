#include "led_ciclo.h"

led_ciclo::led_ciclo(byte pino,int valor_inicial, int maximo)
{
    pinMode(pino,OUTPUT);
    this->pino = pino
    vIni = valor_inicial;
    vMax = maximo;
    passo = 500; // se o usuario esquecer de indicar quanto vale o passo inicial
}

void led_ciclo::passo(int p)
{
    passo = p;
}
        
void led_ciclo::pisca()
{    
    int t = ()
}


