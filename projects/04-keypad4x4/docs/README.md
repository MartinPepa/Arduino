## Quick Reference

### 4x4 Keypad

Library link: [Adafruit_keypad](https://github.com/adafruit/Adafruit_Keypad)

- `begin()`: Set all the pin modes and set up variables.
- `tick()`: Read the array of switches and place any events in the buffer.
- `isPressed(key)`: Check if the given key is currently pressed. Return *true* if it is currently pressed, *false* otherwise
  - key (byte): The name of the key to be checked.
- `read()`: Pop the next event off of the FIFO. Return the next event in the FIFO.
- `clear()`: Clear out the event buffer and all the key states.