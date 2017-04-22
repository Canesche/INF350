/*
	Exemplo da Biblioteca led_piscando
	A biblioteca te permite que o LED demore 1 segundo (por padrão) a mais para piscar (aceso e apagado)
	
	Autor: Michael Canesche
	Criado: 09/03/17 
	Última Atualização: 16/03/17
*/

#include <led_piscando.h>

// Por padrão o pino é o 13 e o tempo inicial é 2000 (1000 + passo)
led_piscando L; // instancia a classe em um objeto chamado L(pino,tempo)

void setup()
{
	// nada é necessário para inicialização
}

void loop()
{	
	L.pisca(); // Faz com que o arduino pisque em tempo + 1s
}
