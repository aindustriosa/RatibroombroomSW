#include "motor.h"


/**
 * @brief Set left motor power.
 *
 * Power is set modulating the PWM signal sent to the motor driver.
 *
 * This function checks for possible PWM saturation. If that is the case the
 * value will be limited to the maximum PWM allowed and the `saturated_left`
 * variable will be incremented by one. This variable is later used to check
 * if multiple consecutive saturated values occurred, which is interpreted as
 * a collision.
 *
 * @param[in] power Power value from -MAX_PWM_PERIOD to MAX_PWM_PERIOD.
 */
void power_left(int32_t power)
{
  // FIXME: mock
}

/**
 * @brief Set right motor power.
 *
 * Power is set modulating the PWM signal sent to the motor driver.
 *
 * This function checks for possible PWM saturation. If that is the case the
 * value will be limited to the maximum PWM allowed and the `saturated_right`
 * variable will be incremented by one. This variable is later used to check
 * if multiple consecutive saturated values occurred, which is interpreted as
 * a collision.
 *
 * @param[in] power Power value from -MAX_PWM_PERIOD to MAX_PWM_PERIOD.
 */
void power_right(int32_t power)
{
  // FIXME: mock

}

/**
 * @brief Break both motors (short the motor winding).
 */
void drive_break(void)
{
  // FIXME: mock
}

/**
 * @brief Return the maximum consecutive motor driver saturated outputs.
 */
uint32_t motor_driver_saturation(void)
{
  // FIXME mock
  return 0;
}
  


/**
 * @brief Reset the PWM saturation counters.
 */
void reset_motor_driver_saturation(void)
{
  // FIXME: mock

}
