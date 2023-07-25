//Transmitter 

#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 13
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

#define rxPin1 9
#define txPin1 12
SoftwareSerial mySerial1 =  SoftwareSerial(rxPin1, txPin1);


int light_sensor_val = 0;
int gas = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

  pinMode(rxPin1, INPUT);
  pinMode(txPin1, OUTPUT);
  mySerial1.begin(9600);

  pinMode(A0,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  Serial.begin(9600);
}

void loop()
{
 
   light_sensor_val = analogRead(A3);
   light_sensor_val = map(light_sensor_val,1,700,0,255);
   //Serial.println(light_sensor_val);
   mySerial.write(light_sensor_val);
   gas = analogRead(A4);
   //Serial.println(gas);
   gas = map(gas, 20, 120, 0, 100);
   Serial.println(gas);
   mySerial1.write(gas);
  
  delay(2000);
}