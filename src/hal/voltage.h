#ifndef __VOLTAGE_H
#define __VOLTAGE_H


float get_battery_voltage(void); // Used by mmlib (logging)
float get_motor_driver_input_voltage(void); // Used by mmlib (control)

#endif /* __VOLTAGE_H */
