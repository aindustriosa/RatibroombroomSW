#include "fan.h"


/**
 * @brief Set fan power.
 *
 * Power is set modulating the PWM signal sent to the fan driver.
 *
 * @param[in] power Power value from 0 to MAX_PWM_PERIOD.
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