#ifndef __PLATFORM_H
#define __PLATFORM_H


#include "setup.h"

void mpu_write_register(uint8_t address, uint8_t value); // Used by mmlib (mpu)
uint8_t mpu_read_register(uint8_t address);  // Used by mmlib (mpu)
uint16_t read_encoder_left(void);  // Used by mmlib (encoder)
uint16_t read_encoder_right(void);  // Used by mmlib (encoder)
uint32_t read_cycle_counter(void);  // Used by mmlib (clock)

void sleep_us(uint32_t us);
void sleep_us_after(uint32_t cycle_counter, uint32_t us);

#endif /* __PLATFORM_H */
