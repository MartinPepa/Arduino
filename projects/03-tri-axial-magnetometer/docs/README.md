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

### QMC5883L

Library link: [QMC5883L](https://github.com/keepworking/Mecha_QMC5883L/tree/master)

- `init()`: Initialize the module.
- `read(int* x,int* y,int* z)`: Read values from device. Magnetic components in three axis.
  - x: Variable previously declared.
  - y: Variable previously declared.
  - z: Variable previously declared.
- `read(int* x,int* y,int* z,int* a)`: Read values from device. Magnetic components in three axis.
  - a: Azimuth value as integer.
- `read(int* x,int* y,int* z,float* a)`: Read values from device. Magnetic components in three axis.
  - a: Azimuth value as float.
- `azimuth(int* a,int* b)`: Read value of *x* and *y* and returns the azimuth angle as float. Is used within read() functions.
  - a: *x* component of the magnetic field.
  - b: *y* component of the magnetic field.