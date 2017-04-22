#define led 12
#define chave 11

#define ESPERA 0
#define CONTAGEM 1
#define MOSTRAR 2

int contador;
int estado;
int anterior, atual;
unsigned long times,previous;
int checar = 0;

void setup()
{
  pinMode(led,OUTPUT);
  pinMode(chave,INPUT);
  Serial.begin(9600);
  contador = 0;
  estado = ESPERA;
}

void loop ()
{
  switch(estado) 
  {
     case ESPERA:
         if ( digitalRead(chave) == HIGH )  
         {
                   contador = 1;
                   estado= CONTAGEM;
                   anterior = HIGH;
                   times = previous = millis();
                   Serial.println("Espera -> Contagem");
         }
         break;
     case CONTAGEM:
         if ( digitalRead(chave) == LOW ){
            anterior = LOW;
            delay(5);
         }
         if ( anterior == LOW && digitalRead(chave) == HIGH ) 
         {
            anterior = HIGH;
            contador++;
            times = previous = millis();
            Serial.print("contador=");
            Serial.println(contador,DEC);
            delay(5);
         }
         times = millis();
         if ( times - previous > 2000 ) {
            estado= MOSTRAR;
            times = previous = millis();
            Serial.println("Contagem -> Mostrar");
         }
         break;
     case MOSTRAR:
         times = previous = millis();
         int i = 0;
         while(i < contador)
         {
            times = millis();
            if(digitalRead(chave) == HIGH)
            {
                Serial.println("Reiniciando contador...");
                estado = CONTAGEM;
                contador = 0;
                checar = 1;
                break;
            }
            if ( times - previous >= 1000 )
            {  
                digitalWrite(led,HIGH);
                //Serial.println("liga luizinha...");        
            }
            if ( times - previous >= 2000 )
            {
                times = previous = millis();
                digitalWrite(led,LOW);
                //Serial.println("desliga luizinha..."); 
                i++;
            } 
         }
         times = previous = millis();
         while(times - previous < 5000 && checar == 0)
         {
            times = millis();
            if(digitalRead(chave) == HIGH)
            {
                Serial.println("Reiniciando contador...");
                estado = CONTAGEM;
                contador = 0;
                break;
            }
         }
         //Serial.println("Mostrar -> Mostrar");
         break;
 }
}
