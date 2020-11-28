#include "speaker.h"

/**
 * @brief Turn on the speaker to play at the selected frequency.
 *
 * Frequency is set modulating the PWM signal sent to the speaker.
 *
 * @param[in] hz Frequency, in Hertz.
 *
 * @note The speaker and emitters both share TIM1. Therefore, this function
 * disables the emitters completely. They are enabled back on `speaker_off()`
 * call.
 */
void speaker_on(float hz)
{
  uint16_t period;

  period = (uint16_t)(SPEAKER_BASE_FREQUENCY_HZ / hz);
  timer_set_period(TIM11, period);
  timer_set_oc_value(TIM11, TIM_OC1, period / 2);
  timer_enable_counter(TIM11);
  timer_enable_oc_output(TIM11, TIM_OC1);
}


/**
 * @brief Turn off the speaker.
 *
 * @note The speaker and emitters both share TIM1. This function makes sure
 * emitters are properly configured after turning off the speaker.
 */
void speaker_off(void)
{
  timer_disable_counter(TIM11);
  timer_disable_oc_output(TIM11, TIM_OC1);
}
  
