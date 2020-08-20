//Sending data via mqtt to a remote server
//We will use the ThingsSpeak server and test data transmission
//The data to be sent to the server will be data read from an infrared sensor
const int echoPin = 6;
const int trigPin = 7;
long duration;
float distance, prevdistance; 
float proximity;
float total = 0;
float dst;                          //Contains the distance reading to be sent to the server
float average [5];


void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    Serial3.write(Serial.read());//Forward what Serial received to Serial3(With the SIM module) Port
  }
  while(Serial3.available()) 
  {
    Serial.write(Serial3.read());//Forward what Serial3(With the SIM module) received to Serial Port
  }
}


void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  delay(3000);
  //Initializing the sim module
  Serial3.print("AT");
  updateSerial();

  //Checking if the module is readdy
  Serial3.print("AT+CPIN?");
  updateSerial();

  //Checking the signal quality
  Serial3.print("AT+CPIN?");
  updateSerial();

  //Setting up the APN parameters
  Serial3.print("AT+CSTT="safaricom", "saf", "data" ");
  updateSerial();
  Serial3.print("AT");
  updateSerial();
}

void loop() {
  
  dst = HC_SR04 ();
  //Serial.print (dst);
  //Serial.print ("cm, ");
  //Serial.println();

  while (Serial.available() > 0 ) {
    Serial3.write(Serial.read());
  }
  while (Serial3.available() > 0 ) {
    Serial.write(Serial3.read() );
  }
  
}

//Reads data from the ultrasonic sensor and runs the average of 5 samples
float HC_SR04 () {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance= (duration*0.034)/2; 

  for (int i = 0; i < 5; i++ ) {
    average [i] = distance;
    total = total + average [i];
    delay (25);
  }

  proximity = (total/5);
  total = 0;

  return proximity;
}

void sendData(int value) {
  //Starting the wireless connection with gprs
  Serial3.print("AT+CIIR");
  updateSerial();
  //Getting the ip address assigned
  Serial3.print("AT+CIFSR");
    
}
