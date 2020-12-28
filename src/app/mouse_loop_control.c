#include "mouse_loop_control.h"

/**
 * @brief execute cron tasks in interruption routine
 *
 */
void mouse_loop_control(void)
{
	clock_tick();
	update_distance_readings();
	update_gyro_readings();
	update_encoder_readings();
	motor_control();
	log_data();
}
	

