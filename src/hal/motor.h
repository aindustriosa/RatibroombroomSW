#ifndef __MOTOR_H
#define __MOTOR_H

#include "setup.h"

uint32_t motor_driver_saturation(void); // Used by mmlib (control)
void reset_motor_driver_saturation(void);  // Used by mmlib (control)
void drive_break(void); // Used by mmlib (move)
void drive_off(void); // Used by mmlib (control)
void power_left(int32_t power); // Used by mmlib (control)
void power_right(int32_t power); // Used by mmlib (control)


#endif /* __MOTOR_H */
