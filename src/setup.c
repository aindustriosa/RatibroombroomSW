#include "setup.h"


/**
 * @brief Setup SPI for gyroscope read, less than 20 MHz.
 *
 * The clock baudrate is 36 MHz / 2 = 18 MHz.
 */
void setup_spi_high_speed(void)
{
  // FIXME mock
}


/**
 * @brief Setup SPI for gyroscope Write, less than 1 MHz.
 *
 * The clock baudrate is 36 MHz / 64 = 0.5625 MHz.
 */
void setup_spi_low_speed(void)
{
  // FIXME: mock
}


