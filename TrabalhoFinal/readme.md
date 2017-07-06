# Trabalho Final 
    
Autores

        Michael Canesche - 68064 - https://github.com/canesche
         
        Juliana Moreno   - 75763
         
        Vanessa Cristiny - 77427 - https://github.com/VanessaCristiny
         
        Guttardo Pereira - 81823

Professor responsável: 
         
        Ricardo Ferreira dos Santos

# Objetivo

1 . Rede NodeMCU - Arduino usando HC012 - Conectar um par de Arduino com HC012. Medir a distancia nos 4 modos de programacao e a taxa de pacotes perdidos. Criar uma biblioteca para que o Arduino remoto possa ter variaveis virtuais (como Blynk e Ubidots) para enviar para o Arduino local. O Arduino remoto também pode ter saidas controladas pelo Arduino local de forma que a comunicação seja Transparente. Criar tambem uma biblioteca Ubidots_HC12 ou Blink_HC12 que permita que o codigo do ubidots seja usado remotamente com a comunicação transparente feita pelo par de HC12.

#include "RemoteHC12.h"

hc12 remote(rx,tx,ID); // Criar um par local-remoto conectado pelo pinos rx,tx. Default taxas transmissao O ID é para caso tenha varios radios perto....o transmissor e receptor irão usar mesmo ID
remote.connect(); // conectar...ter timeout, reconexão....
remote.PinMode(3,OUTPUT); // pino 3 remoto como saida
remote.DigitalWrite(3,HIGH); // mesmo para digitalRead, analog e outras funcoes
remote.Virtual(pino,OUTPUT); // pino virtual 0,1 ou..., OUTPUT ou INPUT
remote.ReadVirtual(pino) ou remote.WriteVirtual(pino,STRING)
Pensar como fazer no arduino remoto , os pinos já estarão sendo automaticamente controlados pelo arduino local.
LocalHC12 control(tx,rx,ID);
control.connect()
control.update()

Usar algo similiar ao Ubidots e Blynik para associar os pinos virtuais com sensores