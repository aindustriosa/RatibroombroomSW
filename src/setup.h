#ifndef __SETUP_H
#define __SETUP_H

#include <libopencm3/cm3/dwt.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>

#include "mmlib/mpu.h"

/** Universal constants */
#define MICROMETERS_PER_METER 1000000  // Used by mmlib
#define MICROSECONDS_PER_SECOND 1000000  // Used by mmlib
#define PI 3.1415  // Used by mmlib

/** Maze dimensions */
#define CELL_DIMENSION 0.18
#define CELL_DIAGONAL 0.1273
#define WALL_WIDTH 0.012
#define MIDDLE_MAZE_DISTANCE ((CELL_DIMENSION - WALL_WIDTH) / 2.)


/** Mouse dimensions */
#define MOUSE_MOTOR_TAIL 0.037    // FIXME: bulebule specs
#define MOUSE_MOTOR_HEAD 0.057    // FIXME: bulebule specs
#define MOUSE_AXIS_SEPARATION 0.0223   // FIXME: bulebule specs
#define MOUSE_LENGTH (MOUSE_MOTOR_TAIL + MOUSE_MOTOR_HEAD) // FIXME: bulebule specs
#define MOUSE_HEAD (MOUSE_LENGTH - MOUSE_TAIL)  // FIXME: bulebule specs
#define MOUSE_TAIL (MOUSE_MOTOR_TAIL + MOUSE_AXIS_SEPARATION / 2.) // FIXME: bulebule specs
#define MOUSE_START_SHIFT (MOUSE_TAIL + WALL_WIDTH / 2.) // FIXME: bulebule specs

/** Mouse physics */
#define MOUSE_MASS 0.11
#define MOUSE_MOMENT_OF_INERTIA 0.000125  // FIXME: bulebule specs
#define MOUSE_WHEELS_SEPARATION 0.065   // FIXME: bulebule specs
#define MOUSE_MAX_ANGULAR_VELOCITY 20  // FIXME: bulebule specs


/** System clock frequency is set in `setup_clock` */
#define SYSCLK_FREQUENCY_HZ 168000000
#define SPEAKER_BASE_FREQUENCY_HZ 1000000
#define SYSTICK_FREQUENCY_HZ 1000
#define DRIVER_PWM_PERIOD 1024

/** Tolerance when trying to keep a defined distance from the front wall */
#define KEEP_FRONT_DISTANCE_TOLERANCE 0.001   //FIXME: bulebule specs


/**
 * Maximum time period allowed with saturated motor driver output.
 *
 * After reaching this period we consider there has been a collision. When a
 * collision occurs, the robot motor control stops working and the motor driver
 * is disabled.
 */
#define MAX_MOTOR_DRIVER_SATURATION_PERIOD 0.01


/**
 * Maximum number of movements in a smoothed path.
 */
#define MAX_SMOOTH_PATH_LEN (MAZE_AREA + 3)



/**
 * Flash module organization.
 *
 * The memory organization is based on a main memory block containing 64 pages
 * of 1 Kbyte (for medium-density devices), and an information block.
 *
 * The linker file was modified to reserve the last memory page for EEPROM.
 * FLASH_EEPROM_ADDRESS = FLASH_BASE + FLASH_EEPROM_PAGE_NUM * FLASH_PAGE_SIZE
 * FLASH_BASE = 0x08000000
 * FLASH_EEPROM_PAGE_NUM = 63
 * FLASH_PAGE_SIZE = 0x400 (1 Kbyte)
 *
 * @see Programming manual (PM0075) "Flash module organization"
 */
#define FLASH_EEPROM_ADDRESS_MAZE ((uint32_t)(0x0800fc00))  // FIXME: bulebule specs


void setup_spi_low_speed(void);   // Used by mmlib (mpu)
void setup_spi_high_speed(void);  // Used by mmlib (mpu)


#endif /* __SETUP_H */
