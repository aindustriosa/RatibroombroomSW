#include "platform.h"


#define MPU_READ 0x80


/**
 * @brief Read the microcontroller clock cycle counter.
 *
 * This counter increases by one at `SYSCLK_FREQUENCY_HZ`.
 */
uint32_t read_cycle_counter(void)
{

  return dwt_read_cycle_counter();
}


/**
 * @brief Read left motor encoder counter.
 */
uint16_t read_encoder_left(void)
{
  return (uint16_t)timer_get_counter(TIM3);
}

/**
 * @brief Read right motor encoder counter.
 */
uint16_t read_encoder_right(void)
{
  return (uint16_t)timer_get_counter(TIM4);
}

/**
 * @brief Read a MPU register.
 *
 * @param[in] address Register address.
 */
uint8_t mpu_read_register(uint8_t address)
{
  uint8_t reading;
  
  gpio_clear(GPIOA, GPIO15);
  spi_send(SPI3, (MPU_READ | address));
  spi_read(SPI3);
  spi_send(SPI3, 0x00);
  reading = spi_read(SPI3);
  gpio_set(GPIOA, GPIO15);

  return reading;
}


/**
 * @brief Write a MPU register with a given value.
 *
 * @param[in] address Register address.
 * @param[in] address Register value.
 */
void mpu_write_register(uint8_t address, uint8_t value)
{
  gpio_clear(GPIOA, GPIO15);
  spi_send(SPI3, address);
  spi_read(SPI3);
  spi_send(SPI3, value);
  spi_read(SPI3);
  gpio_set(GPIOA, GPIO15);
}


/**
 * @brief Sleep for a number of microseconds.
 *
 * @param[in] us Sleep period, in microseconds.
 */
void sleep_us(uint32_t us)
{
	uint32_t initial_cycles = read_cycle_counter();
	uint32_t sleep_cycles = (uint32_t)(
	    SYSCLK_FREQUENCY_HZ * ((float)us / (float)MICROSECONDS_PER_SECOND));

	while (read_cycle_counter() - initial_cycles <= sleep_cycles)
		;
}

/**
 * @brief Sleep for a number of microseconds since `cycle_counter`.
 *
 * @param[in] cycle_counter Cycle counter value used as starting point.
 * @param[in] us Sleep period, in microseconds.
 */
void sleep_us_after(uint32_t cycle_counter, uint32_t us)
{
	uint32_t sleep_cycles = (uint32_t)(
	    SYSCLK_FREQUENCY_HZ * ((float)us / (float)MICROSECONDS_PER_SECOND));

	while (read_cycle_counter() - cycle_counter <= sleep_cycles)
		;
}
