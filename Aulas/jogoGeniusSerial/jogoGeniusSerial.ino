// exemplo do jogo
//http://labdegaragem.com/profiles/blogs/genius

// o projeto pode ser encontrado em: https://circuits.io/circuits/4832665-jogo-genius-rgb-serial

int R = 9;     //Pin 9
int G = 10;    //Pin 10
int B = 11;    //Pin 11
String l, pisca_pisca;
int qtdCores = 4; 
int dificuldade = 1;
unsigned int tempoJogada, tempoPassado;
bool venceu = true;

void setup() {
  Serial.begin(9600);
  while (!Serial){;}
  desliga();
  randomSeed(analogRead(0));
}

void loop() {
  // proxima fase
  if(venceu){
      pisca_pisca = "";
      Serial.println("\nPreparado?");
      delay(1000); 
      for(int i = 0; i < dificuldade; i++){
            int numero = (random(qtdCores)+1);
            //Serial.println(numero);
            pisca(numero);
            delay(2000);
            desliga();
            delay(2000);
            pisca_pisca += (String) numero;
      }
      //Serial.println(pisca_pisca);
      tempoJogada = tempoPassado = millis();
      venceu = false;
      Serial.println("Sua vez! YU_GI_OH!!!!!");
  }
  
  if(verificaTempo())
    Serial.println("perdeu");

  if (Serial.available()){ 
      l = Serial.readString();
        //Serial.println(l);
        //Serial.println(pisca_pisca);
        if(l != pisca_pisca){
            venceu = false;
            Serial.println("Errrrrrrouuuu da zero para ele");
        }
      else{
            Serial.println("Que a força esteja com você!");
            venceu = true;
          dificuldade++;
      }
  }
  
  
}

/// FUNCOES
bool verificaTempo(){
  tempoPassado = millis();  
  return  (tempoPassado - tempoJogada > 10000);  
}

void pisca(int i){
  switch(i){
    case 1: // vermelho
      analogWrite(R,255);
      break;
    case 2: // verde
      analogWrite(G,255);
      break;
    case 3: // azul
      analogWrite(B,255);
      break;
    case 4: // amarelo
      analogWrite(R,255);
      analogWrite(G,255);
      break;
    default:
      desliga();  
  }
}

void desliga() {
  l = "";
  analogWrite(R, 0);
  analogWrite(B, 0);
  analogWrite(G, 0);
}
