#ifndef __CONFIG_H
#define __CONFIG_H


/** Locomotion-related constants */
#define SHIFT_AFTER_180_DEG_TURN 0.010    // FIXME: bulebule specs


/** Time it takes for the robot to decide where to go next while searching */
#define SEARCH_REACTION_TIME 0.01  // FIXME: bulebule specs


/** Calibration constants for sensors */
#define SENSOR_SIDE_LEFT_A 2.806  // FIXME: bulebule specs
#define SENSOR_SIDE_LEFT_B 0.287  // FIXME: bulebule specs
#define SENSOR_SIDE_RIGHT_A 2.327  // FIXME: bulebule specs
#define SENSOR_SIDE_RIGHT_B 0.231  // FIXME: bulebule specs
#define SENSOR_FRONT_LEFT_A 2.609  // FIXME: bulebule specs
#define SENSOR_FRONT_LEFT_B 0.242  // FIXME: bulebule specs
#define SENSOR_FRONT_RIGHT_A 2.713  // FIXME: bulebule specs
#define SENSOR_FRONT_RIGHT_B 0.258  // FIXME: bulebule specs


/** Control constants */
#define KP_LINEAR 8.    // FIXME: bulebule specs
#define KD_LINEAR 16.   // FIXME: bulebule specs
#define KP_ANGULAR .05  // FIXME: bulebule specs
#define KD_ANGULAR 1.  // FIXME: bulebule specs
#define KP_ANGULAR_FRONT .5   // FIXME: bulebule specs
#define KI_ANGULAR_FRONT 2.  // FIXME: bulebule specs
#define KP_ANGULAR_SIDE 2.  // FIXME: bulebule specs
#define KI_ANGULAR_SIDE 4.   // FIXME: bulebule specs
#define KP_ANGULAR_DIAGONAL 2.  // FIXME: bulebule specs
#define KI_ANGULAR_DIAGONAL 4.  // FIXME: bulebule specs


struct control_constants {
	float kp_linear;
	float kd_linear;
	float kp_angular;
	float kd_angular;
	float kp_angular_front;
	float ki_angular_front;
	float kp_angular_side;
	float ki_angular_side;
	float kp_angular_diagonal;
	float ki_angular_diagonal;
};


void set_control_constants(struct control_constants value); // Used by mmlib (command)
void set_linear_speed_limit(float value);
void set_micrometers_per_count(float value); // used by mmlib (control)
float get_linear_speed_limit(void);
float get_micrometers_per_count(void);  // Used by mmlib (logging)
struct control_constants get_control_constants(void);


#endif /* _CONFIG_H */
