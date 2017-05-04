int objeto = 0;  
unsigned int rpm = 0;
unsigned int tempo, tempoPassado;
   
void setup()  {  
  pinMode(7, INPUT); //Pino ligado ao coletor do fototransistor  
  Serial.begin(9600);
  tempo = tempoPassado = millis();  
}  
   
void loop()  
{  
  tempoPassado = millis();

  if(tempoPassado - tempo> 60000){
    tempo = tempoPassado;
    Serial.print(rpm);
    Serial.println(" cliks por minuto");
    rpm = 0;
  }
  
  objeto = digitalRead(7);
  if (objeto == LOW){ // se ele foi detectado  
    rpm++;
    //Serial.println("Objeto : Detectado");  
    Serial.println(rpm);
    delay(150);
  }  
}
