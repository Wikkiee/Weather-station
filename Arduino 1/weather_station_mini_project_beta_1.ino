// Receiver
//
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


#define rxPin 13
#define txPin 8
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

#define rxPin1 10
#define txPin1 A4
SoftwareSerial mySerial1 =  SoftwareSerial(rxPin1, txPin1);


int baselineTemp = 0;
int celsius = 0;
int fahrenheit = 0;
int avail = 0;
int switch_stats = 0;
int light_sensor_value = 0;
int gas_value = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);
  
  pinMode(rxPin1, INPUT);
  pinMode(txPin1, OUTPUT);
  mySerial1.begin(9600);
  
  
  lcd.begin(16, 2); 
  lcd.setCursor(0,0);          
  lcd.print("Weather station"); 
  lcd.setCursor(2,1);           
  lcd.print("Mini project"); 
  delay(3000);
  display_names();
  
}

void loop()
{
  lcd.clear();
  if(digitalRead(A1)==1){
     set_lcd_temp();
     Serial.println("Block 1");
  }else if(digitalRead(A2)==1){
      mySerial.listen();
      Serial.println(mySerial1.available());
      if(mySerial.available() > 0){
        light_sensor_value = mySerial.read();
        Serial.println(light_sensor_value);
		if ( light_sensor_value >= 0 && light_sensor_value <= 40)
        {
          lcd.print("Weather Type : ");
          lcd.setCursor(0, 1);
          lcd.print("Overcast");
          delay(30);
        }
        else if ( light_sensor_value > 40 && light_sensor_value <= 70)
        {
          lcd.print("Weather Type : ");
          lcd.setCursor(0, 1);
          lcd.print("Partially Cloudy");
          delay(30);
        }
        else
        {
          lcd.print("Weather Type : ");
          lcd.setCursor(0, 1);
          lcd.print("Sunny/Clear");
          delay(30);
        }
      
      
      
      }
      Serial.println("Block 2");
     
  }else if(digitalRead(A3)==1){
    mySerial1.listen();
    if(mySerial1.available()>0){
      if ((gas_value <= 100) && (gas_value >= 0))
      {
        gas_value = mySerial1.read();
        Serial.println(gas_value);
        //gas_value = map(gas_value, 0, 255, 0, 100);
        lcd.print("Toxic Gas !");
        lcd.setCursor(0, 1);
        lcd.print("Percentage = ");
        lcd.setCursor(13, 1);
        lcd.print(gas_value);
      }else{
        lcd.print("Toxic Gas !");
        lcd.setCursor(0, 1);
        lcd.print("Percentage = ");
        lcd.setCursor(13, 1);
        lcd.print(100);
        delay(30);
      }
    }
  }else{
  	set_lcd_temp();
  }
  
  delay(2000); 
  
}

void display_names(){
  lcd.clear();
  lcd.setCursor(0,0);          
  lcd.print("    M.VIGNESH   "); 
  lcd.setCursor(2,1);           
  lcd.print("720820104111"); 
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);          
  lcd.print("PARTHIBANRAJ.B.T"); 
  lcd.setCursor(2,1);           
  lcd.print("720820104077"); 
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);          
  lcd.print(" V.S.SIVA BALAN"); 
  lcd.setCursor(2,1);           
  lcd.print("720820104098"); 
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);          
  lcd.print("   S.SANTHOSH"); 
  lcd.setCursor(2,1);           
  lcd.print("720820104092"); 
  delay(2000);
}

void set_lcd_temp(){

  lcd.setCursor(0,0);          
  lcd.print("   Celsius"); 
  lcd.setCursor(2,1);           
  lcd.print("  Fahrenheit"); 

  baselineTemp = 40;

  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  lcd.setCursor(0,0);          
  lcd.print(celsius);
  lcd.setCursor(0,1);
  lcd.print(fahrenheit);
  
}
