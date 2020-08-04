#include <TinyGPS++.h>
TinyGPSPlus gps;
HardwareSerial Serial2(USART2); //PA3(TX) & PA2(RX)     With the GPS
HardwareSerial Serial3(USART3); //PB11(TX) & PB10(RX)   With the SIM800L
double lat_val, lng_val;
boolean health;


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


static void GPSDelay(unsigned long ms)          //Delay for receiving data from GPS
{
  unsigned long start = millis();
  do
  {
    while (Serial2.available()) 
    gps.encode(Serial2.read());
  } while (millis() - start < ms);
}





void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  delay(1000); //Initializing the modules

  Serial3.println("AT"); //Once the handshake test is successful, it will reply OK
  updateSerial();
  Serial3.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  Serial3.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  Serial3.println("AT+CREG"); //Check whether it has registered in the network
  updateSerial();
  }

void loop() {
  updateSerial();

  GPSDelay(1000);
  unsigned long start;
  bool loc_valid;  
  lat_val = gps.location.lat();        
  loc_valid = gps.location.isValid(); 
  lng_val = gps.location.lng();        
  if (!loc_valid)                     //Excecutes when invalid data is received from GPS
  {
    Serial.print("Latitude : ");
    Serial.println("*****");
    Serial.print("Longitude : ");
    Serial.println("*****");
    delay(4000);
  }
  else                              //Excutes when valid data is received from GPS
  {    
    Serial.println("GPS READING: ");
    Serial.print("Latitude : ");
    Serial.println(lat_val, 6);   //Prints latitude at Serial Monitor
    Serial.print("Longitude : ");
    Serial.println(lng_val, 6);   //Prints longitude at Serial monitor
    delay(4000);
  }
}
