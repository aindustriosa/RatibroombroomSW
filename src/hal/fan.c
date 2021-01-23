#include "fan.h"


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
void power_fan(int32_t power)
{
	if (power < 0) {
		power = 0;
	}
	else if (power > MAX_PWM_PERIOD) {
		power = MAX_PWM_PERIOD;
	}
	timer_set_oc_value(TIM10, TIM_OC1, power); // PWM
}

