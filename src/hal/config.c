#include "config.h"

static volatile struct control_constants control = {
    .kp_linear = KP_LINEAR,
    .kd_linear = KD_LINEAR,
    .kp_angular = KP_ANGULAR,
    .kd_angular = KD_ANGULAR,
    .kp_angular_front = KP_ANGULAR_FRONT,
    .ki_angular_front = KI_ANGULAR_FRONT,
    .kp_angular_side = KP_ANGULAR_SIDE,
    .ki_angular_side = KI_ANGULAR_SIDE,
    .kp_angular_diagonal = KP_ANGULAR_DIAGONAL,
    .ki_angular_diagonal = KI_ANGULAR_DIAGONAL};


void set_micrometers_per_count(float value)
{
  // FIXME: mock
}

struct control_constants get_control_constants(void)
{
	return control;
}


void set_control_constants(struct control_constants value)
{
  // FIXME: mock
}

void set_linear_speed_limit(float value)
{
  // FIXME: mock
}


float get_micrometers_per_count(void)
{
  // FIXME: mock

  return 0.0;
}


float get_linear_speed_limit(void)
{
  // FIXME: mock
  return 0.0;
}
