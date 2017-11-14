#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int trig = 11;
const int echo = 12;
int inter_time = 1000;
int number = 0;

void setup() {
  Serial.begin(9600);  
  lcd.begin(16, 2);
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
}
/*第22行的29.1為(1/攝氏20度的聲速)*/
void loop() {
  float duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  duration = pulseIn (echo, HIGH);
  distance = (duration/2)/29.1;
  lcd.setCursor (0,0);
  lcd.print("Data No.");
  lcd.print (number);
  number = number +1;
  lcd.setCursor(0, 1);  
  lcd.print ("Distance:");   
  lcd.print(distance);
  lcd.print ("cm");
  delay(900);
  lcd.clear();
  delay(100);
  
}

