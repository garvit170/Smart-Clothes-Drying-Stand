#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial nodemcu(7,8);      //RX=8; TX=7
int moistVal01, moistVal02; 

int controlPin1 = A0;     //SENSOR 1
int RainPin = A1;         //SENSOR 2
int dt=400;
int controlPin2 = A2;     //SENSOR 3

const int rs=11, en=10, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sdata1 = 0; // sensor1 data
int sdata2 = 0; // sensor2 data
int sdata3 = 0; // sensor3 data
String cdata; // complete data, consisting of sensors values
bool counter=false;
bool written false;

void setup () {

  Serial.begin(9600);
  nodemcu.begin(9600);
  pinMode(controlPin1, INPUT);
  pinMode(controlPin2, INPUT);
  pinMode(RainPin, INPUT);
  lcd.begin(16,2);
  
}

void loop () {
  written=false;

  //Moisture Sensor 01
  
  moistVal01=analogRead(controlPin1);
  //Serial.print(moistVal01);

  int DryRight=0;
  int PrintR=0;
  DryRight = {(100./1023.)*moistVal01};                           //Conversion Function
  PrintR=DryRight;                                                                  

  Serial.print(moistVal01);
  Serial.print("\n");



  //Moisture Sensor 02
  
  moistVal02=analogRead(controlPin2);
  //Serial.print(moistVal02);

  int DryLeft=0;
  int PrintL=0;

  DryLeft = {(100./1023.)*moistVal02};
  PrintL=DryLeft;                                                                  //Conversion Function

  Serial.print("Dry(L) - ");
  Serial.print(DryLeft);
  Serial.print("%");


  
  
  //Rain Sensor
  int rainVal=analogRead(RainPin);
  Serial.print("\t");
  Serial.print("Rain - ");
  Serial.println(rainVal);
  delay(dt);
  if (rainValprev<900 && counter==false) {
    Serial.println("It's Raining, Pick up your clothes");
    analogWrite(A5, 255);//Buzzer will active
    sdata1 = PrintR;
   sdata2 = PrintL;
   sdata3 = rainValprev;
   cdata = cdata + sdata1+","+sdata2+","+sdata3; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(2000); // 100 milli seconds
   cdata = ""; 
   written = true;
    delay(10000);
    analogWrite(A5, 0);

    counter=true;
    delay(dt);
  }
  else if(rainValprev>=900){
    Serial.println("No Worries");
    delay(dt);
    counter=false;
  }

   //LCD Display
  
  //Serial.print("\n");           
  lcd.setCursor(0,0);
  lcd.print("Dry(R) - ");
  lcd.print(PrintR);
  lcd.print("%");
  lcd.print(" ");
  

  lcd.setCursor(0,1);
  lcd.print("Dry(L) - ");
  lcd.print(PrintL);
  lcd.print("%");
  lcd.print(" ");
 
  
 

  // NODEMCU INTERFACE

   if(written == false){
    sdata1 = PrintR;
   sdata2 = PrintL;
   sdata3 = rainValprev;
   cdata = cdata + sdata1+","+sdata2+","+sdata3; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(2000); // 100 milli seconds
   cdata = ""; 
   }
  
  
}
