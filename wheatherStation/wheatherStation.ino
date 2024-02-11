/*    
  Custom character
  https://arduinointro.com/projects/create-custom-characters-for-the-i2c-lcd-easily#:~:text=To%20create%20your%20own%20custom,defined%20in%20a%20single%20program.
*/

// Libraries
#include <Wire.h>                 // Library for I2C
#include <LCD.h>                  // Library for LCD functions
#include <LiquidCrystal_I2C.h>    // Library for LCD through I2C
#include <DHT.h>                  // Library for Temp and Humidity sensor
#include <DHT_U.h>                // Library extra for Temp and Humidity sensor
#include <Adafruit_BMP280.h>      // Library for Patm sensor
#include <TM1637Display.h>        // Library for TM1637 7 segment display

/* ATENTION: 
- DHT11 sensor:
  Left pin: signal.
  Middle pin: VCC.
  Right pin: GND.
- LCD Display:
  Analog pin A4 with SDA
  Analog pin A5 con SCL
- BMP280 sensor:
  Pin SCL = SCK   --> 13
  Pin SDA = MOSI  --> 11
  Pin CSB = SS    --> 10
  Pin SDO = MISO  --> 12
*/

// For SPI communication from BMP280 sensor
#define BMP_SCK   (13)
#define BMP_MISO  (12)
#define BMP_MOSI  (11)
#define BMP_CS_1  (10)
int sensor = 2;
// For display1 comunication (Temp)
#define CLK1 TBD         // CLK a pin TBD
#define DIO1 TBD         // DIO a pin TBD
// For display2 comunication (Humidity)
#define CLK2 TBD         // CLK a pin TBD
#define DIO2 TBD         // DIO a pin TBD
// For display3 comunication (Patm)
#define CLK3 TBD         // CLK a pin TBD
#define DIO4 TBD         // DIO a pin TBD

// Objects definition
Adafruit_BMP280 pressure_sensor(BMP_CS_1);
DHT TH_sensor(sensor,DHT11);
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7);  // DIR, E, RW, RS, D4, D5, D6, D7
TM1637Display display1(CLK1, DIO1);
TM1637Display display2(CLK2, DIO2);
TM1637Display display3(CLK3, DIO3);

float temperature;
int humidity;
float pressure;

// Customized characters
byte drop[8] = {
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00000
};
byte thermometer[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b01110,
  0b11111,
  0b11111,
  0b01110
};
byte arrow[8] = {
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000,
  B11111
};

// ------------------------------
void setup()
{
    display1.setBrightness(5);		      // Sets the brightness level
    display2.setBrightness(5);
    display3.setBrightness(5);
    lcd.setBacklightPin(3,POSITIVE);  // P3 port from PCF8574 as positive
    lcd.setBacklight(HIGH);           // Enables LCD backlight
    lcd.begin(16, 2);                 // 16 columns pby 2 rows for LCD 1602A
    lcd.createChar(0, thermometer);   // Creates thermometer.
    lcd.createChar(1, drop);          // Creates drop.
    lcd.createChar(2, arrow);         // Creates arrow.
    lcd.clear();                      // Clears the display.
    TH_sensor.begin();
    pressure_sensor.begin();
    Serial.begin(9600);
    if (!pressure_sensor.begin()){
      Serial.println(F("Pressure sensor not found."));
      while(1);
    }
}
// ------------------------------
void loop()
{
    temperature = TH_sensor.readTemperature();
    humidity    = TH_sensor.readHumidity();
    pressure    = pressure_sensor.readPressure();
    
    lcd.setCursor(0, 0);    // Set the prompt in column 0 row 0
    lcd.print("");
    lcd.write(byte(0));
    lcd.print(" ");
    lcd.print((float)temperature,1);
    lcd.print(" C");

    lcd.print("  ");
    lcd.write(byte(1));
    lcd.print(" ");
    lcd.print(humidity);
    lcd.print("%");

    lcd.setCursor(0, 1);    // Set the prompt in column 0 row 1
    lcd.print("  ");
    lcd.write(byte(2));
    lcd.print(" ");
    lcd.print(pressure/100,1);
    lcd.print(" hPa");
    
    display1.showNumberDecEx(static_cast<int>(temperature*10), 0b01000000, false, 3, 0);	
    display2.showNumberDecEx(humidity, 0, false, 2, 0);	
    display3.showNumberDecEx(static_cast<int>(pressure/100), 0b00100000, false, 3, 0);
    
    delay(500);
}
// ------------------------------

/* Extra information:
lcd.setCursor(0, 0);               // Sets cursor at column 0 and row 0
lcd.print("text");                 // Prints in the LCD the "text" string
lcd.print((float)temperature,1);   // Prints the 'temperature' variable with 1 decimal
 */
