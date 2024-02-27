## Quick Reference

### LCD 16x2

Library link: [LCD](https://github.com/fmalpartida/New-LiquidCrystal)

### 4x4 Keypad

Library link: [Adafruit_keypad](https://github.com/adafruit/Adafruit_Keypad)

- `Adafruit_Keypad(*userKeymap, *row, *col, numRows, numCols)`: Default constructor.
  - *userKeymap (byte): A multidimensional array of key characters.
  - *row (byte): An array of GPIO pins that are connected to each row of the keypad.
  - *col (byte): An array of GPIO pins that are connected to each column of the keypad.
  - numRows (int): The number of rows on the keypad.
  - numCols (int): The number of columns on the keypad.
- `begin()`: Set all the pin modes and set up variables.
- `tick()`: Read the array of switches and place any events in the buffer.
- `isPressed(key)`: Check if the given key is currently pressed. Return *true* if it is currently pressed, *false* otherwise
  - key (byte): The name of the key to be checked.
- `read()`: Pop the next event off of the FIFO. Return the next event in the FIFO.
- `clear()`: Clear out the event buffer and all the key states.

### BMP280

Library link: [BMP280 Library](https://github.com/adafruit/Adafruit_BMP280_Library)

- `Adafruit_BMP280(cspin, *theSPI)`: BMP280 constructor using hardware SPI.
  - cspin (int8_t): Chip select pin number.
  - *theSPI (SPIClass): Optional SPI object.
- `begin(uint8_t addr, uint8_t chipid)`: Initialises the sensor. Returns *true* if the init was successful, otherwise *false*.
  - addr (uint8_t): The I2C address to use. *Default 0x77*.
  - chipid (uint8_t): The expected chip ID (used to validate connection).
- `readPressure()`: Reads barometric pressure from device. Returns barometric pressure in Pa.
- `readAltitude(seaLevel1hPa)`: Calculates the aproximate altitude in meters using barometric pressure and the supplied sea level hPa as a reference.
  - seaLevel1hPa (float): The current hPa at sea level. *Default 1013.25*.

### DHT11 / DHT12 / DHT21 / DHT22 

Library link: [DHT Library](https://github.com/adafruit/DHT-sensor-library)

- `DHT(pin, type, count)`: Instantiates a new DHT class.
  - pin (uint8_t): pin number that sensor is connected.
  - type (uint8_t): type of sensor.
    - DHT11: 11.
    - DHT12: 12.
    - DHT21: 21.
    - DHT22: 22.
    - AM2301: 21.
  - count (uint8_t): number of sensors. *Default 6*.
- `begin(usec)`: Setup sensor pins and set pull timings.
  - usec (uint8_t): Optionally pass pull-up time (in microseconds) before DHT reading. *Default 55*.
- `readTemperature(S, force)`: Read temperature.
  - S (bool): Scale. *Default false*
  - force (bool): true if in force mode. *Default false*.
- `readHumidity(force)`: Read humidity in percent.
  - force (bool): force read mode. *Default false*.