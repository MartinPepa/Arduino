// Libraries
#include <Wire.h>                         // Library for I2C
#include <LCD.h>                          // Library for LCD functions
#include <LiquidCrystal_I2C.h>            // Library for LCD through I2C
#include <DHT.h>                          // Library for Temp and Humidity sensor
#include <DHT_U.h>                        // Library extra for Temp and Humidity sensor
#include <Adafruit_BMP280.h>              // Library for pressure sensor
#include <Adafruit_Keypad.h>              // Library for 4x4 keypad
#include <Adafruit_Keypad_Ringbuffer.h>   // Library for 4x4 keypad

// 4x4 Keypad
const byte rows = 4;
const byte columns = 4;
char keys[rows][columns] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowsPins[rows] = {9,8,7,6};
byte columnsPins[columns] = {5,4,3,2};

// DHT11 pin
int sensor = 17;

// BMP280 through SPI
#define BMP_SCK   (13)
#define BMP_MISO  (12)
#define BMP_MOSI  (11)
#define BMP_CS_1  (10)

// Objects definition
Adafruit_BMP280 pressure_sensor(BMP_CS_1);
DHT TH_sensor(sensor,DHT11);
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7);  // DIR, E, RW, RS, D4, D5, D6, D7
Adafruit_Keypad keypad = Adafruit_Keypad(makeKeymap(keys), rowsPins, columnsPins, rows, columns);

// degree character
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

// Variables
float temperature, pressure, altitude, h0 = 1013.0;
char Key, aux;
String H0;
int humidity, i, j;

// ------------------------------
void setup()
{
  lcd.setBacklightPin(3,POSITIVE);  // P3 port from PCF8574 as positive
  lcd.setBacklight(HIGH);           // Enables LCD backlight
  lcd.begin(16, 2);                 // 16 columns pby 2 rows for LCD 1602A
  lcd.clear();                      // Clears the display.
  lcd.createChar(0, deg);           // Creates thermometer.
  TH_sensor.begin();                // Initialize DHT11
  pressure_sensor.begin();          // Initialize BMP280
  keypad.begin();                   // Initialize keypad 4x4
}
// ------------------------------
void loop()
{
  temperature   = TH_sensor.readTemperature();
  humidity      = TH_sensor.readHumidity();
  pressure      = pressure_sensor.readPressure();
  altitude      = pressure_sensor.readAltitude(h0);
  keypad.tick();

  if (keypad.isPressed(keys[0][3])){
    Key = 'A';
  } else if (keypad.isPressed(keys[1][3])){
    Key = 'B';
  } else if (keypad.isPressed(keys[2][3])){
    Key = 'C';
  } else if (keypad.isPressed(keys[3][3])){
    Key = 'D';
  } else if (keypad.isPressed(keys[3][0])){
    Key = '*';
  }
  
  if (Key=='A'){
    lcd.setCursor(0, 0);
    lcd.print("Temperature:");
    lcd.setCursor(5, 1);
    lcd.print((float)temperature,1);
    lcd.print(" ");
    lcd.write(byte(0));
    lcd.print("C");
    delay(200);
    lcd.clear();
  } else if (Key=='B'){
    lcd.setCursor(0, 0);
    lcd.print("Humidity:");
    lcd.setCursor(6, 1);
    lcd.print(humidity);
    lcd.print(" %");
    delay(200);
    lcd.clear();
  } else if (Key=='C'){
    lcd.setCursor(0, 0);
    lcd.print("P atmospheric:");
    lcd.setCursor(4, 1);
    lcd.print((float)pressure/100,1);
    lcd.print(" hPa");
    delay(200);
    lcd.clear();
  } else if (Key=='D'){
    lcd.setCursor(0, 0);
    lcd.print("Altitude:");
    lcd.setCursor(5, 1);
    lcd.print((float)altitude,1);
    lcd.print(" m");
    delay(200);
    lcd.clear();
  } else if (Key=='*'){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wait...");
    delay(3000);
    while (Key!='#'){
      delay(200);
      keypad.clear();
      keypad.tick();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Patm [hPa]");
      lcd.setCursor(5, 1);
      if (keypad.available()){
        keypadEvent e = keypad.read();
        aux = (char)e.bit.KEY;
        if (aux == '*'){
          H0 += '.';
        } else if (aux == '#'){
          Key = '#';
          h0 = H0.toFloat();
          break;
        } else {
          H0 += aux;
        }
      }
      lcd.print(H0);
    }
    Key = 'D';
    lcd.clear();
    H0 = "";
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Press any letter");
  }
}
// ------------------------------