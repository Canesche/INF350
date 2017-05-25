void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.write("1"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
    Serial.write(Serial.read());
}
