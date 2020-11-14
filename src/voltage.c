#include "voltage.h"


/**
 * @brief Function to get battery voltage.
 *
 * This function reads the voltage of the battery from the register configured
 * on the ADC2.
 *
 * The value is converted from bits to voltage taking into account that the
 * battery voltage is read through a voltage divider.
 *
 *@return The battery voltage in volts.
 */
float get_battery_voltage(void)
{
  return 0.0;   // FIXME: mock
}


/**
 * @brief Function to get motor driver input voltage.
 *
 * In Bulebule, we assume the motor driver input voltage is constant.
 *
 *@return The motor driver input voltage in volts.
 */
float get_motor_driver_input_voltage(void)
{
  // FIXME: mock
}
