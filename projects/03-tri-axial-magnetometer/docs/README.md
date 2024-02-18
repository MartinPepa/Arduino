## Quick Reference

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
  
### LCD 16x2

Library link: [LCD](https://github.com/fmalpartida/New-LiquidCrystal)