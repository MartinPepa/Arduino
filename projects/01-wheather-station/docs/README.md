## Quick Reference

### LCD 16x2

Library link: [LCD](https://github.com/fmalpartida/New-LiquidCrystal)

- `begin(cols, lines, dotsize) `: Initializes the LCD to a given size (col,row). This method initializes the LCD, therefore, is must be called prior to using any other method from this class.
  - cols (uint8_t): The number of columns that the display has.
  - rows (uint8_t): the number of rows that the display has.
  - charsize (uint8_t): Character size. *Default LCD_5x8DOTS*.
- `clear()`: Clears the LCD screen and positions the cursor in the upper-left corner.
- `createChar(location, charmap[])`: Creates a custom character for use on the LCD. Most chipsets only support up to eight characters of 5x8 pixels. Therefore, this methods has been limited to locations (numbered 0 to 7).
  - location (uint8_t): LCDmemorylocation of the character to create (0 to 7).
  - charmap[] (uint8_t): The bitmap array representing each row of the character.
- `setCursor(col, row)`: Position the LCD cursor.
  - col (uint8_t): LCD column.
  - row (uint8_t): LCD row - line.
- `setBacklightPin(value, pol)`: Sets the pin in the device to control the backlight.
  - value (uint8_t): Pin associated to backlight control.
  - pol (t_backlightPol): backlight polarity control (POSITIVE, NEGATIVE).
- `setBacklight(value)`: Sets the pin to control the backlight.
  - value (uint8_t): 0 -255.

### TM1637 Display

Library link: [TM1637 Library](https://github.com/avishorp/TM1637)

- ``clear()``: Clear the display. Recommended to use it in Setup.
- ``showNumberDecEx(num, dots, leading_zero, lenght, pos)``: Display the given argument as a decimal number. The dots between the digits (or colon) can be individually controlled.
  - num (int): The number to be shown.
  - dots (uint_8t):  Dot/Colon enable. *Default 0*.
    - 0.000 (0b10000000)
    - 00.00 (0b01000000)
    - 000.0 (0b00100000)
    - 0.0.0.0 (0b11100000)
    - 00:00 (0b01000000)
    - 0.0:0.0 (0b11100000)
  - leading_zero (bool): When true, leading zeros are displayed. Otherwise unnecessary digits are blank. *Default false*.
  - lenght (uint8_t): The number of digits to set. The user must ensure that the number to be shown fits to the number of digits requested (for example, if two digits are to be displayed, the number must be between 0 to 99). *Default 4*.
  - pos (uint8_t): The position of the most significant digit (0: leftmost, 3: rightmost). *Default 0*.
- ``setBrightness(brightness, on)``: Sets the brightness of the display.
  - brightness (uint8_t): A number from 0 (lowes brightness) to 7 (highest brightness).
  - on (bool): Turn display on or off. *Default true*

### DHT11 / DHT12 / DHT21 / DHT22 

Library link: [DHT Library](https://github.com/adafruit/DHT-sensor-library)

- ``DHT(pin, type, count)``: Instantiates a new DHT class.
  - pin (uint8_t): pin number that sensor is connected.
  - type (uint8_t): type of sensor.
    - DHT11: 11.
    - DHT12: 12.
    - DHT21: 21.
    - DHT22: 22.
    - AM2301: 21.
  - count (uint8_t): number of sensors. *Default 6*.
- ``begin(usec)``: Setup sensor pins and set pull timings.
  - usec (uint8_t): Optionally pass pull-up time (in microseconds) before DHT reading. *Default 55*.
- ``readTemperature(S, force)``: Read temperature.
  - S (bool): Scale. *Default false*
  - force (bool): true if in force mode. *Default false*.
- ``readHumidity(force)``: Read humidity in percent.
  - force (bool): force read mode. *Default false*.

### BMP280

Library link: [BMP280 Library](https://github.com/adafruit/Adafruit_BMP280_Library)

- ``readPressure()``: Reads barometric pressure from device. Returns barometric pressure in Pa.
- ``readAltitude(seaLevel1hPa)``: Calculates the aproximate altitude in meters using barometric pressure and the supplied sea level hPa as a reference.
  - seaLevel1hPa (float): The current hPa at sea level. *Default 1013.25*.