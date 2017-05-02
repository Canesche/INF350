int R = 9;  //Pin 9
int G = 10; //Pin 10
int B = 11; //Pin 11
String l;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  l = "";
  analogWrite(R, 0);
  analogWrite(G, 0);
  analogWrite(B, 0);
  Serial.println("\n------------------------------------");
  Serial.println("RGB -- Letras disponiveis:");
  Serial.println("VERMELHO => v, red, vermelho");
  Serial.println("VERDE => g, green, verde");
  Serial.println("AZUL => b, blue, azul");
  Serial.println("AMARELO => y, yellow, amarelo");
  Serial.println("------------------------------------\n");
}

void loop() {
  if (Serial.available())
    l = Serial.readString();

  if (l == "v" || l == "vermelho" || l == "red") {
    desliga();
    analogWrite(R, 255);
  } else if (l == "g" || l == "verde" || l == "green") {
    desliga();
    analogWrite(G, 255);
  } else if (l == "b" || l == "azul" || l == "blue") {
    desliga();
    analogWrite(B, 255);
  } else if (l == "y" || l == "amarelo" || l == "yellow") {
    desliga();
    analogWrite(R, 255);
    analogWrite(G, 255);
  } else {
    desliga();  
  }
}

void desliga() {
  analogWrite(R, 0);
  analogWrite(B, 0);
  analogWrite(G, 0);
}
