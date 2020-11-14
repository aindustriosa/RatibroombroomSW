#include "platform.h"



/**
 * @brief Read the microcontroller clock cycle counter.
 *
 * This counter increases by one at `SYSCLK_FREQUENCY_HZ`.
 */
uint32_t read_cycle_counter(void)
{

  // FIXME: mock
  return 0;
}


/**
 * @brief Read left motor encoder counter.
 */
uint16_t read_encoder_left(void)
{
  // FIXME mock
  return 0;

}

/**
 * @brief Read right motor encoder counter.
 */
uint16_t read_encoder_right(void)
{
  // FIXME mock
  return 0;
}

/**
 * @brief Read a MPU register.
 *
 * @param[in] address Register address.
 */
uint8_t mpu_read_register(uint8_t address)
{
  // FIXME mock
  return 0;
}


/**
 * @brief Write a MPU register with a given value.
 *
 * @param[in] address Register address.
 * @param[in] address Register value.
 */
void mpu_write_register(uint8_t address, uint8_t value)
{
  // FIXME mock

}
