#ifndef __DETECTION_H
#define __DETECTION_H

#include "config.h"
#include "setup.h"



/* Sensors IDs*/
#define SENSOR_SIDE_LEFT_ID 0
#define SENSOR_SIDE_RIGHT_ID 1
#define SENSOR_FRONT_LEFT_ID 2
#define SENSOR_FRONT_RIGHT_ID 3
#define NUM_SENSOR 4
#define SENSORS_SM_TICKS 4 // FIXME: bulebule specs


void get_sensors_raw(uint16_t *on, uint16_t *off);  // Used by mmlib (logging)
float sensors_raw_log(uint16_t on, uint16_t off); // Used by mmlib (walls)

#endif /* __DETECTION_H */
