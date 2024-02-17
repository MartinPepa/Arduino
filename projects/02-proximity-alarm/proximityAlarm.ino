// Libraries
#include <Wire.h>                 // I2c communication
#include <LCD.h>                  // LCD functions
#include <LiquidCrystal_I2C.h>    // LCD with I2C

// Define variables
int trig = 8;
int echo = 9;
int active_buz = 7;
int duration;
float distance;

// Create LCD
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

//------------------------------
void setup(){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(active_buz, OUTPUT);

  lcd.setBacklightPin(3,POSITIVE);    // Port P3 of PCF8574 as positive
  lcd.setBacklight(HIGH);             // Enables backlight
  lcd.begin(16, 2);                   // Set 16 column and 2 rows for LCD 1602A
  lcd.clear();                        // Clears the display
}
//------------------------------
void loop()
{
  lcd.clear();
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration / 58.2;
  
  if(distance > 20 && distance >= 0){
    lcd.setCursor(0, 0);
    lcd.print("    Distance:");
    lcd.setCursor(0, 1);
    lcd.print("      ");
    lcd.print(distance,0);
    lcd.print(" cm");
    delay(500);
  }
  if(distance <= 20 && distance > 10){
    lcd.setCursor(0, 0);
    lcd.print("    Caution!    ");
    lcd.setCursor(1, 1);
    lcd.print("     ");
    lcd.print(distance,0);
    lcd.print(" cm");
    digitalWrite(active_buz, HIGH);
    delay(200);
    digitalWrite(active_buz, LOW);
    delay(300);
  }
  if(distance <= 10 && distance >= 0){
    lcd.setCursor(0, 0);
    lcd.print("    Warning!    ");
    lcd.setCursor(1, 1);
    lcd.print("      ");
    lcd.print(distance,0);
    lcd.print(" cm");
    digitalWrite(active_buz, HIGH);
    delay(100);
    digitalWrite(active_buz, LOW);
    delay(50);
    digitalWrite(active_buz, HIGH);
    delay(100);
    digitalWrite(active_buz, LOW);
    delay(250);
  }
}
//------------------------------