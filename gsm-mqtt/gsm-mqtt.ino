//Sending data via mqtt to a remote server
//We will use the ThingsSpeak server and test data transmission
//The data to be sent to the server will be data read from an infrared sensor
const int echoPin = 6;
const int trigPin = 7;
long duration;
int distance; 
long inches, cm;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  distance= (duration*0.034)/2;
  
  Serial.print(microsecondsToInches(duration));
  Serial.print("in, Method 1 ");
  Serial.print(distance);
  Serial.print("cm,How to Mechatronics ");
  Serial.print(microsecondsToCentimeters(duration));
  Serial.print("cm. ");
  Serial.println();
  delay(100);

}

long microsecondsToInches(long microseconds) {
   return (microseconds / 74 / 2);
}

long microsecondsToCentimeters(long microseconds) {
   return (microseconds / 29 / 2);
}
