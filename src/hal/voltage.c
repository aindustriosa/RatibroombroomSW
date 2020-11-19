#include "voltage.h"

// ADC2 is setup in setup.c (setup_adc2())
#define BATTERY_ADC ADC2

/** 
 * This is the amount of voltage per bit in the ADC that is connected to the voltage divider
 * connected to the battery. This could be calculated theoretically, but is better to
 * use a voltage generator connected at the battery input of the micromouse and read the 
 * real outputs of the ADC for a number of inputs, then calculate the factor 
 * and put it here. Remember not to choose input voltages very low or high,
 * as you could burn the board, use values from 6.4 to 8.1 Volts
*/
#define DIVIDER_VOLTS_PER_BIT (3.3 / 4096) // Max input volts at ADC divided by the ADC resolution 

/** Motor driver input voltage */
#define MOTOR_DRIVER_INPUT_VOLTAGE_WHEN_REGULATED 5.

/**
 * @brief Function to get battery voltage.
 *
 * This function reads one time the voltage of the battery from the register configured
 * on the ADC assigned to the battery.
 *
 * The value is converted from bits to voltage taking into account that the
 * battery voltage is read through a voltage divider.
 * 
 * Note the use of adc_start_conversion_regular instead of injected (direct is not 
 * available for STMF4, only STMF1)
 * https://electronics.stackexchange.com/questions/83426/what-is-the-difference-between-an-injected-and-regular-stm32-adc-channel
 * http://libopencm3.org/docs/latest/stm32f1/html/group__adc__file.html#ga455f91c3461744ff38517f4cd54c31b4
 * 
 * TODO: This function is mainly used to check the battery status, so we can change it if depletted.
 *       It would be interesting to avoid noise in measurements or getting a value when the motors are
 *       using a peak of current by returning a mean value of past samples. Like in 
 *       https://github.com/hmightypirate/AllMyCircuits/blob/develop/src/mightybug_a/vbatt.c#L47
 *
 *@return The battery voltage in volts.
 */
float get_battery_voltage(void)
{
	uint16_t battery_bits;

	adc_start_conversion_regular(BATTERY_ADC);
	while (!adc_eoc(BATTERY_ADC))
		;
	battery_bits = adc_read_regular(BATTERY_ADC);
	return battery_bits * DIVIDER_VOLTS_PER_BIT;
}


/**
 * @brief Function to get motor driver input voltage.
 *
 * In this micromouse, we assume the motor driver input voltage is constant, as it is
 * connected to a regulator (this is not always true, as the motors could be directly
 * connected to the battery. In this case, this voltage is get_battery_voltage()).
 *
 *@return The motor driver input voltage in volts.
 */
float get_motor_driver_input_voltage(void)
{
  return MOTOR_DRIVER_INPUT_VOLTAGE_WHEN_REGULATED;
}
