// Libraries
#include <Wire.h>                 // I2C comunication library
#include <LCD.h>                  // Library for LCD functions
#include <LiquidCrystal_I2C.h>    // Library for LCD with I2C
#include <MechaQMC5883.h>         // Library for magnetometer

// Instancies
MechaQMC5883 magnetometer;
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

// Special character
byte deg[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00111,
  0b00000,
  0b00000,
  0b00000
};

//----------------------------------------
void setup()
{
  Wire.begin();
  lcd.setBacklightPin(3,POSITIVE);    // Port P3 of PCF8574 positive
  lcd.setBacklight(HIGH);             // Enables LCD backlight
  lcd.begin(16, 2);                   // Begins 16 columns by 2 rows for LCD 1602A
  lcd.clear();                        // Clars the display
  lcd.createChar(0, deg);             // Creates degree
  magnetometer.init();                // Initialize the magnetometer
}
//----------------------------------------
void loop()
{
  int x,y,z,azimut;
  magnetometer.read(&x,&y,&z,&azimut);

  lcd.setCursor(0, 0);    // Set cursor in column 0 row 0
  lcd.print("X:");
  if(abs(x)<10){
    lcd.print("  ");
    if(x>0){
      lcd.print(" ");
    }
    lcd.print(x);
  } else if (abs(x)>=10 && abs(x)<=99){
    lcd.print(" ");
    if(x>0){
      lcd.print(" ");
    }
    lcd.print(x);
  } else if (abs(x)>99){
    if(x>0){
      lcd.print(" ");
    }
    lcd.print(x);
  }
  
  lcd.setCursor(8, 0);    // Set cursor in column 8 row 0
  lcd.print("Y:");
  if(abs(y)<10){
    lcd.print("  ");
    if(y>0){
      lcd.print(" ");
    }
    lcd.print(y);
  } else if (abs(y)>=10 && abs(y)<=99){
    lcd.print(" ");
    if(y>0){
      lcd.print(" ");
    }
    lcd.print(y);
  } else if (abs(y)>99){
    if(y>0){
      lcd.print(" ");
    }
    lcd.print(y);
  }
  
  lcd.setCursor(0, 1);    // Set cursor in column 0 row 1
  lcd.print("  Azimut: ");
  if (azimut>99){
    lcd.print(azimut);
  }else if(azimut<=99 && azimut>=10){
    lcd.print(" ");
    lcd.print(azimut);
  } else if (azimut<10){
    lcd.print("  ");
    lcd.print(azimut);
  }
  lcd.write(byte(0));
  delay(1000);
  lcd.clear();
}
//----------------------------------------