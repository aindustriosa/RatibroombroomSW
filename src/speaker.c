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
  // FIXME: mock

}


/**
 * @brief Turn off the speaker.
 *
 * @note The speaker and emitters both share TIM1. This function makes sure
 * emitters are properly configured after turning off the speaker.
 */
void speaker_off(void)
{
  // FIXME: mock

}
  
