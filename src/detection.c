#include "detection.h"



/**
 * @brief Get sensors values with emitter on and off.
 *
 * @param[out] on Raw sensors reading with emitter on.
 * @param[out] off Raw sensors reading with emitter off.
 */
void get_sensors_raw(uint16_t *on, uint16_t *off)
{
  // FIXME: mock
}


/**
 * @brief Apply `log()` to the raw sensor readings.
 *
 * A minimum difference of `1` is enforced to avoid applying `log()` to a zero
 * or negative value.
 *
 * @param[in] on Raw sensor reading with emitter on.
 * @param[in] off Raw sensor reading with emitter off.
 */
float sensors_raw_log(uint16_t on, uint16_t off)
{
  //FIXME: mock

  return 0.0;

}
