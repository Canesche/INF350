// exemplo do jogo
//http://labdegaragem.com/profiles/blogs/genius

int R = 9, G = 11, B = 10;
String l, pisca_pisca;
int qtdCores = 4; 
int dificuldade = 1, j = 1;
unsigned int tempoJogada, tempoPassado;
bool venceu = true, parar = true, acende = true;

void setup() {
    Serial.begin(9600);
    while (!Serial){;}
    desliga();
    randomSeed(analogRead(0)); // semente para o ranomico
}

void loop() {
  if(venceu){ // se ele venceu ou primeira vez a jogar
      reinicio:
      Serial.println("\nAlready? GO! ");
      Serial.end();
      pisca_pisca = "";
      delay(500); 
      for(int i = 0; i < dificuldade; i++){
            int numero = (random(qtdCores)+1);
            pisca(numero);
            delay(1500);
            desliga();
            delay(1500);
            pisca_pisca += (String) numero;
      }
      tempoJogada = tempoPassado = millis();
      venceu = false;
      parar = true; acende = true;
      Serial.begin(9600);
      Serial.println("Sua vez! YU_GI_OH!!!!!");
  }
  
  if(verificaTempo() && parar){
    parar = false; acende = false;
    Serial.println("perdeu playboy ou playgirl");
    Serial.println("Jogar novamente? Aperte 'r' ");
  }

  if (Serial.available()){ 
      l = Serial.readString();
      if(l == "r"){
        Serial.println("Vai tentar a sorte, quero ver...");
            dificuldade = 1;
            goto reinicio;
        }
        if(l != pisca_pisca){
            venceu = false; acende = false;
            Serial.println("Errrrrrrouuuu da zero para ele");
            Serial.println("Jogar novamente? Aperte 'r' ");
        }
      else{
            Serial.println("Que a forca esteja com voce!\n");
            venceu = true;
          dificuldade++;
      }
  }

  if(verificaTempo() || !acende){
    pisca(j++%4+1);
    delay(400);
    desliga();
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
