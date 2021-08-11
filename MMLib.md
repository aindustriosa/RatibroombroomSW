# Introduction

This document describes all the mmlib dependencies that the system must implement correctly in order to use the current version of MMLIB


# Dependencies

This section describes the files that your system must implement with the functions and variables that must be in there.

## MPU (mpu.h)

This file must include the following functions:

* `void gyro_z_calibration(void)` : Calibration of the gyroscope's Z axis (executed at startup). Used by *mmlib* (calibration)
* `float get_gyro_z_radps(void)`: Get gyroscope's Z-axis angular speed in radians per second. Used by *mmlib* (control)

## SETUP (setup.h)

This file must include the following variables and functions:

* `MICROMETERS_PER_METER`: number of micrometer in one meter (10^6). Used by *mmlib* (in encoder, move and speed)
* `PI`: hte pi number 3.1415 . Used by *mmlib* (calibration, move and speed)
* `MAX_MOTOR_DRIVER_SATURATION_PERIOD`: TBD. Used by *mmlib* (control)


Setup is also imported by other files in mmlib in order to get some var types. This file is imported in calibration, clock, control, encoder, move, solve and speed.

## BUTTONS (buttons.h)

* `bool button_read_user(void)` : A button used by mmlib to configure the run. Used by *mmlib* (hmi)

## CONFIG (config.h)

* `void set_control_constants(struct control_constants value)`: TBD. Used by *mmlib* (command)
* `void set_micrometers_per_count(float value)`: Set the micrometers per each tick count of the encoder. Used by *mmlib* (control)
* `float get_micrometers_per_count(void)`: Micrometers per each tick count of the encoder. Used by *mmlib* (logging)

## DETECTION (detection.h)

* `void get_sensors_raw(uint16_t *on, uint16_t *off)`:  Get sensors values with emitter on and off. Used by *mmlib* (logging)
* `float sensors_raw_log(uint16_t on, uint16_t off)`: Apply log operation to sensor readings. Used by *mmlib* (walls)

## EEPROM (eeprom.h)

* `uint32_t eeprom_flash_page(uint32_t page_address, uint8_t *input_data, uint16_t num_bytes)`:  Function to save data on a page of EEPROM (erases EEPROM first) . Used by *mmlib* (sove)
* `uint32_t eeprom_erase_page(uint32_t page_address)`:  Function to erase a page of EEPROM. Used by *mmlib* (solve)

## LEDS (leds.h)
* `void led_left_on(void)`:  Function to power ON the left LED. Used by *mmlib* (hmi)
* `void led_left_off(void)`: Function to power OFF the left LED. Used by *mmlib* (hmi)
* `void led_left_toggle(void)`:  Function to toggle the left LED. Used by *mmlib* (hmi)
* `void led_right_on(void)`:   Function to power on the right LED. Used by *mmlib* (hmi)
* `void led_right_off(void)`: Function to power OFF the right LED. Used by *mmlib* (hmi)
* `void led_right_toggle(void)`:  Function to toggle the right LED.Used by *mmlib* (hmi)

## PLATFORM (platform.h)

* `uint16_t read_encoder_left(void);`: Used by Read left motor encoder counter (ticks). *mmlib* (encoder)
* `uint16_t read_encoder_right(void)`: Read right motor encoder counter (ticks). Used by *mmlib* (encoder)
* `uint32_t read_cycle_counter(void)`: Read the microcontroller clock cycle counter. Used by *mmlib* (clock)

## MOTOR (motor.h)

* `uint32_t motor_driver_saturation(void)`: ; Return the maximum consecutive motor driver saturated outputs. Used by *mmlib* (control)
* `void reset_motor_driver_saturation(void)`:  Reset the PWM saturation counters. Used by *mmlib* (control)
* `void drive_break(void)`: Brake both motors (short the motor winding). Used by *mmlib* (move)
* `void drive_off(void)`: Break both motors (short the motor winding).  Used by *mmlib* (control)
* `void power_left(int32_t power)`: Set left motor power (Power is set modulating the PWM signal sent to the motor driver). Used by *mmlib* (control)
* `void power_right(int32_t power)`: Set right motor power (Power is set modulating the PWM signal sent to the motor driver). Used by *mmlib* (control)



## SERIAL (serial.h)

* `RECEIVE_BUFFER_SIZE`: TBD.  Used by *mmlib* (command)
* `get_received_command_flag`: Checks if a command has arrived (command_flag == true). Used by *mmlib* (command)
* `void set_received_command_flag(bool value)`: Sets the value of command_flag (true if a command waits to be executed). Used by *mmlib* (command)
* `bool serial_acquire_transfer_lock(void)`: TBD. Used by *mmlib* (logging.h)
* `void serial_send(char *data, int size)`: TBD. Used by *mmlib* (logging.h)
* `char *get_received_serial_buffer(void)`: Returns the serial buffer address where the incoming bytes are stored. Used by *mmlib* (command)


## SPEAKER (speaker.h)

* `void speaker_on(float hz)`:  Turn on the speaker to play at the selected frequency. Used by *mmlib* (music)
* `void speaker_off(void)`: Turn off the speaker. Used by *mmlib* (music)


## VOLTAGE (voltage.h)

* `float get_battery_voltage(void)`: get battery voltage, used to check battery levels. Used by *mmlib* (logging)
* `float get_motor_driver_input_voltage(void)`: Function to get motor driver input voltage. Used by *mmlib* (control)
