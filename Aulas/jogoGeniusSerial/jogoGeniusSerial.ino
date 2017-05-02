int R = 9;      //Pin 9
int G = 10;    //Pin 10
int B = 11;      //Pin 11
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
}

void loop() {
  if (Serial.available())
    l = Serial.readString();

  if (l == "v" || l == "vermelho" || l == "red") {
    Serial.println(l);
    desliga();
    analogWrite(R, 255);
  } else if (l == "g" || l == "verde" || l == "green") {
    Serial.print(l);
    desliga();
    analogWrite(G, 255);
  } else if (l == "b" || l == "azul" || l == "blue") {
    Serial.print(l);
    desliga();
    analogWrite(B, 255);
  } else if (l == "y" || l == "amarelo" || l == "yellow") {
    Serial.print(l);
    desliga();
    analogWrite(R, 255);
    analogWrite(G, 255);
  }
}

void desliga() {
  l = "";
  analogWrite(R, 0);
  analogWrite(B, 0);
  analogWrite(G, 0);
}
