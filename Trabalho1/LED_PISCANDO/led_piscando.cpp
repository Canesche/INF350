#include "led_piscando.h"

// implementação construtor
led_piscando::led_piscando(int pino, int valor_inicial)
 : pin(pino)
{    
    pinMode(pino,OUTPUT);
    digitalWrite(pino,LOW);
    setTempo(valor_inicial);
    setPasso(1000);     
}

// implementação do construtor de copia
led_piscando::led_piscando(const led_piscando &led)
 : pin(led.pin)
{
    tempo = led.tempo;
}

// implementação funções membros
void led_piscando::pisca()
{
	int temp = getTempo() + getPasso();
	digitalWrite(pin,HIGH);
	delay(temp);
	digitalWrite(pin,LOW);
	delay(temp);
}

void led_piscando::incrementa_valor(int x)
{
	setPasso(x);
}

void led_piscando::reinicia()
{
    digitalWrite(pin,LOW);
	setPasso(1000); 
}

void led_piscando::setTempo(int t)
{
	(t < 0) ? tempo = 1000 : tempo = t;
}

int led_piscando::getTempo() const
{  	
	return tempo;
}

void led_piscando::setPasso(int p)
{	
	(p + getTempo() < 0) ? passo = 1000 : passo = p;
}

int led_piscando::getPasso() const
{
	return passo;
}
