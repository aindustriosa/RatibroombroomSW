#ifndef __VOLTAGE_H
#define __VOLTAGE_H

#include <libopencm3/stm32/adc.h>

/**
 * @brief Function to get battery voltage, used to check battery levels.
 * 
 *  Used by mmlib (logging)
 *
 *@return The battery voltage in volts.
 */
float get_battery_voltage(void); //

/**
 * @brief Funtion to get raw adc battery value
 * 
 * @return The adc raw value
 */
uint16_t get_battery_raw(void);

/**
 * @brief Function to get motor driver input voltage.
 * 
 * Used by mmlib (control)
 *
 *@return The motor driver input voltage in volts.
 */
float get_motor_driver_input_voltage(void);

#endif /* __VOLTAGE_H */
