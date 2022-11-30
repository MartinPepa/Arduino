/*    
  Custom character
  https://arduinointro.com/projects/create-custom-characters-for-the-i2c-lcd-easily#:~:text=To%20create%20your%20own%20custom,defined%20in%20a%20single%20program.
*/

// Librerías
#include <Wire.h>                 // Librería de comunicacion por I2C
#include <LCD.h>                  // Librería para funciones de LCD
#include <LiquidCrystal_I2C.h>    // Librería para LCD por I2C
#include <DHT.h>                  // Librería del sensor de T y H
#include <DHT_U.h>                // Librería extra de T y H
#include <Adafruit_BMP280.h>      // Libreria del sensor de presión

/* IMPORTANTE: 
    - Sensor DHT11:
      pin izquierdo: señal.
      pin medio: VCC.
      pin derecho GND.
    - Pantalla LCD:
      Pin analógico A4 con SDA
      Pin analógico A5 con SCL
    - Sensor BMP280:
      Pin SCL = SCK   --> 13
      Pin SDA = MOSI  --> 11
      Pin CSB = SS    --> 10
      Pin SDO = MISO  --> 12
*/

// Para comunicación SPI del sensor BMP280
#define BMP_SCK   (13)
#define BMP_MISO  (12)
#define BMP_MOSI  (11)
#define BMP_CS_1  (10)
int sensor = 2;

Adafruit_BMP280 sensor_presion(BMP_CS_1);
DHT sensor_t_h(sensor,DHT11);
LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

float temperatura;
int humedad;
float presion;

// Caracteres personalizados:
byte gota[8] = {
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00000
};
byte termometro[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b01110,
  0b11111,
  0b11111,
  0b01110
};
byte flecha[8] = {
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000,
  B11111
};

void setup()
{
    lcd.setBacklightPin(3,POSITIVE);    // puerto P3 de PCF8574 como positivo
    lcd.setBacklight(HIGH);             // habilita iluminacion posterior de LCD
    lcd.begin(16, 2);                   // 16 columnas por 2 lineas para LCD 1602A
    lcd.createChar(0, termometro);      // Crea el termómetro de temperatura.
    lcd.createChar(1, gota);            // Crea la gota de humedad.
    lcd.createChar(2, flecha);          // Crea la flecha de presión.
    lcd.clear();                        // Limpia pantalla.
    sensor_t_h.begin();
    sensor_presion.begin();
    Serial.begin(9600);
    if (!sensor_presion.begin()){
      Serial.println(F("No se ha encontrado el sonsor."));
      while(1);
    }
}

void loop()
{
    temperatura = sensor_t_h.readTemperature();
    humedad     = sensor_t_h.readHumidity();
    presion     = sensor_presion.readPressure();
    
    lcd.setCursor(0, 0);    // ubica cursor en columna 0 y linea 0
    lcd.print("");
    lcd.write(byte(0));
    lcd.print(" ");
    lcd.print((float)temperatura,1);
    lcd.print(" C");

    lcd.print("  ");
    lcd.write(byte(1));
    lcd.print(" ");
    lcd.print(humedad);
    lcd.print("%");

    lcd.setCursor(0, 1);    // ubica cursor en columna 0 y linea 1
    lcd.print("  ");
    lcd.write(byte(2));
    lcd.print(" ");
    lcd.print(presion/100,1);
    lcd.print(" hPa");
    
    delay(500);
}

/* Información extra:
 * lcd.setCursor(0, 0);               // Ubica cursor en columna 0 y linea 0
 * lcd.print("texto");                // Imprime en pantalla la cadena "texto"         
 * lcd.print((float)temperatura,1);   // Imprime la variable 'temperatura' con 1 decimal
 */
