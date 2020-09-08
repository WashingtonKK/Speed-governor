void setup() {
  // put your setup code here, to run once:
  Serial3.begin(115200);
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.write("1\r\n");  
  while(Serial3.available()) {
    Serial.write(Serial3.read());
    Serial.write("Debug\r\n");
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
  }
  while(Serial.available()) {
    Serial3.write(Serial.read());
    Serial3.write("Debug\r\n");
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
  }
}
