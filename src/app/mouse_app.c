#include "mouse_app.h"


/**
 * @brief Check battery voltage and warn if the voltage is getting too low.
 */
static void check_battery_voltage(void)
{
	float voltage;

	voltage = get_battery_voltage();
	if (voltage < 3.6)
		speaker_warn_low_battery();
	if (voltage < 3.5)
		speaker_warn_low_battery();
	if (voltage < 3.4)
		speaker_warn_low_battery();
	if (voltage < 3.3)
		speaker_play_error();
}

/**
 * @brief Includes the functions to be executed before robot starts to move.
 */
static void before_moving(void)
{
	reset_motion();
	disable_walls_control();
	repeat_blink(10, 100);
	sleep_us(5000000);
	check_battery_voltage();
	led_left_on();
	led_right_on();
	wait_front_sensor_close_signal(0.12);
	srand(read_cycle_counter());
	led_left_off();
	led_right_off();
	sleep_us(2000000);
	calibrate();
	enable_motor_control();
	set_starting_position();
}

/**
 * @brief Functions to be executed after moving (running or exploring).
 */
static void after_moving(void)
{
	reset_motion();
	if (collision_detected())
		blink_collision();
	else
		speaker_play_success();
	check_battery_voltage();
}

/**
 * @brief Let the user configure the mouse forces before exploring or running.
 *
 * The user selects the force to apply to the tires while exploring or running.
 *
 * Data logging is always active during movement phase.
 *
 * @param[in] run Whether the robot should be running.
 */
static void movement_phase(bool do_run)
{
	float force;

	force = hmi_configure_force(0.1, 0.05);
	kinematic_configuration(force, do_run);

	start_data_logging(log_data_control);
	before_moving();
	if (!do_run) {
		explore(force);
	} else {
		run(force);
		run_back(force);
	}
	after_moving();
	stop_data_logging();
}

/**
 * @brief Configure the goal for the search phase.
 */
static void configure_goal(void)
{
	switch (button_user_wait_action()) {
	case BUTTON_SHORT:
		add_goal(1, 0);
		break;
	case BUTTON_LONG:
		set_goal_classic();
		speaker_play_competition();
		break;
	}
}

/**
 * @brief Execute the exploration phase.
 */
static void exploration_phase(void)
{
	set_search_initial_direction(NORTH);
	configure_goal();
	set_target_goal();

	movement_phase(false);

	set_run_sequence();
	save_maze();
}

/**
 * @brief Configure the robot and execute the search/run.
 */
static void configure_and_move(void)
{
	if (!maze_is_saved())
		exploration_phase();

	// Using one of the front leds for this (instead of led_bluepil)
	led_FL_on();
	
	switch (button_user_wait_action()) {
	case BUTTON_SHORT:
		load_maze();
		break;
	case BUTTON_LONG:
		reset_maze();
		led_FL_off();		
		exploration_phase();
		led_FL_on();
		break;
	}
	while (1)
		movement_phase(true);
}

/**
 * @brief Log encoder info
 */
void log_encoders_counts(void)
{
	LOG_DATA("[%d, %d]", get_encoder_left_total_count(), get_encoder_right_total_count());
}

/**
 * @brief main application loop
 *
 */
void loop(void)
{
//   while(1) {
//      switch (button_user_response()) {
//        case BUTTON_NONE:
// 	 break;
//      default:
//        configure_and_move();
//        break;

//      }
//      execute_command();
    
//   }

	char state = 0;
	bool forward = false;
	bool backward = false;
	bool forward_motors = false;
	bool backward_motors = false;
	bool stop_motors_1 = false;
	bool stop_motors_2 = false;
	uint32_t last_clock_ticks_led = 0;
	uint32_t last_clock_ticks_action = 0;

	leds_binary(0xFF);
	LOG_INFO("Ratibroombroom Test Firmware");
	speaker_play_beeps(5);
	leds_binary(0x00);

	while(1) {

		forward = false;
		backward = false;

		if ((get_clock_ticks() - last_clock_ticks_led) > 500) {
			led_FL_toggle();
			last_clock_ticks_led = get_clock_ticks();
		}

		
		if (state == 0) { // Battery
			if ((get_clock_ticks() - last_clock_ticks_action) > 1000) {
				log_battery_voltage();
				// Must change
				// LOG_INFO("%f,%d", get_battery_voltage(), get_battery_raw());
				// in logging.c from mmlib to obtain more data
				last_clock_ticks_action = get_clock_ticks();
			}
			while(button_read_right()) {
				state = 1;
				forward = true;
			}
			if (forward) {
				speaker_play_beeps(1);
				continue;
			}
			while(button_read_left()) {
				state = 5;
				backward = true;
			}
			if (backward) {
				speaker_play_beeps(2);
				continue;
			}
		} else if (state == 1) { // Sensors
			if ((get_clock_ticks() - last_clock_ticks_action) > 500) {
				log_sensors_raw();
				last_clock_ticks_action = get_clock_ticks();
			}
			while(button_read_right()) {
				state = 2;
				forward = true;
			}
			if (forward) {
				speaker_play_beeps(1);
				continue;
			}
			while(button_read_left()) {
				state = 0;
				backward = true;
			}
			if (backward) {
				speaker_play_beeps(2);
				continue;
			}
		} else if (state == 2) { // Motors
			if ((get_clock_ticks() - last_clock_ticks_action) < 3000) {
				if (!forward_motors) {
					LOG_INFO("Motors Forward");
					forward_motors = true;
				}
				power_left(1000);
				power_right(1000);
			} else if ((get_clock_ticks() - last_clock_ticks_action) < 4000) {
				if (!stop_motors_1) {
					LOG_INFO("Motors Stop");
					stop_motors_1 = true;					
				}
				power_left(0);
				power_right(0);
			} else if ((get_clock_ticks() - last_clock_ticks_action) < 7000) {
				if (!backward_motors) {
					LOG_INFO("Motors Backward");
					backward_motors = true;
				}
				power_left(-1000);
				power_right(-1000);
			} else if ((get_clock_ticks() - last_clock_ticks_action) < 8000) {
				if (!stop_motors_2) {
					LOG_INFO("Motors Stop");
					stop_motors_2 = true;					
				}
				power_left(0);
				power_right(0);
			} else {
				LOG_INFO("Motors Test");
				forward_motors = false;
				backward_motors = false;
				stop_motors_1 = false;
				stop_motors_2 = false;
				last_clock_ticks_action = get_clock_ticks();
			}
			while(button_read_right()) {
				state = 3;
				forward = true;
				forward_motors = false;
				backward_motors = false;
				stop_motors_1 = false;
				stop_motors_2 = false;
				power_left(0);
				power_right(0);
			}
			if (forward) {
				speaker_play_beeps(1);
				continue;
			}
			while(button_read_left()) {
				state = 1;
				backward = true;
				forward_motors = false;
				backward_motors = false;
				stop_motors_1 = false;
				stop_motors_2 = false;
				power_left(0);
				power_right(0);
			}
			if (backward) {
				speaker_play_beeps(2);
				continue;
			}
		} else if (state == 3) { // Encoders
			if ((get_clock_ticks() - last_clock_ticks_action) > 200) {
				log_encoders_counts();
				last_clock_ticks_action = get_clock_ticks();
			}
			while(button_read_right()) {
				state = 4;
				forward = true;
			}
			if (forward) {
				speaker_play_beeps(1);
				continue;
			}
			while(button_read_left()) {
				state = 2;
				backward = true;
			}
			if (backward) {
				speaker_play_beeps(2);
				continue;
			}
		} else if (state == 4) { // Fan
			if ((get_clock_ticks() - last_clock_ticks_action) < 3000) {
				power_fan(256);
			} else if ((get_clock_ticks() - last_clock_ticks_action) < 4000) {
				power_fan(0);
			} else if ((get_clock_ticks() - last_clock_ticks_action) < 7000) {
				power_fan(1024);
			} else if ((get_clock_ticks() - last_clock_ticks_action) < 8000) {
				power_fan(0);
			} else {
				LOG_INFO("Fan Test");
				last_clock_ticks_action = get_clock_ticks();
			}
			while(button_read_right()) {
				state = 5;
				forward = true;
			}
			if (forward) {
				speaker_play_beeps(1);
				continue;
			}
			while(button_read_left()) {
				state = 3;
				backward = true;
			}
			if (backward) {
				speaker_play_beeps(2);
				continue;
			}

		} else if (state == 5) {
			if ((get_clock_ticks() - last_clock_ticks_action) > 1000) {
				LOG_DATA("[%x]", mpu_who_am_i());
				last_clock_ticks_action = get_clock_ticks();
			}
			while(button_read_right()) {
				state = 0;
				forward = true;
			}
			if (forward) {
				speaker_play_beeps(1);
				continue;
			}
			while(button_read_left()) {
				state = 4;
				backward = true;
			}
			if (backward) {
				speaker_play_beeps(2);
				continue;
			}

		} else {
			leds_binary(0xFF);
			speaker_play_beeps(1);
			leds_binary(0x00);
		}
	} 
}
