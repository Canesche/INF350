/*
	Exemplo da Biblioteca led_piscando
	A biblioteca te permite que o LED demore 1 segundo (por padrão) a mais para piscar (aceso e apagado)
	
	Autor: Michael Canesche
	Criado: 09/03/17 
	Última Atualização: 16/03/17
*/

// inclusão da biblioteca
#include <led_piscando.h>

// Por padrão o pino é o 13 e o tempo inicial é 2000 (1000 + passo)
// se tempo for negativo, ele torna-se por padrão t = 1s
led_piscando L(13,-2000); // instancia a classe em um objeto chamado L(pino,tempo)

void setup()
{
	// nada é necessário para inicialização
}

void loop()
{	
	// valor negativo no passo é aceito desde que o tempo + passo >= 0
	// caso contrário o passo torna-se 1s
	L.incrementa_valor(-500);  
	L.pisca(); // Faz com que o arduino pisque em tempo + 1s
	L.reinicia(); // inicia o tempo para 1s
}
