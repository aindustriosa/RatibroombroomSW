# Hardware Abstraction Layer (HAL) code

The code in this directory leverages libopencm3 (https://libopencm3.org/) to offer low level access to the robot capabilities.

## MMLIB Interface

The micromouse library (https://github.com/Bulebots/mmlib) uses this code, so it must implement all the low level functions that MMLIB needs. These functions are defined in the following header files, which names are already defined in MMLIB, so cannot be changed:
 - buttons.h
 - detection.h
 - leds.h
 - platform.h
 - setup.h
 - voltage.h
 - config.h
 - eeprom.h
 - motor.h
 - serial.h
 - speaker.h
