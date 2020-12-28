#ifndef __MOUSE_APP_H
#define __MOUSE_APP_H

/* MMLIB imports */
#include "mmlib/hmi.h"
#include "mmlib/control.h"
#include "mmlib/calibration.h"
#include "mmlib/solve.h"
#include "mmlib/command.h"

/* HAL imports */
#include "setup.h"
#include "voltage.h"
#include "leds.h"


/**
 * @brief main application loop
 *
 */
void loop(void);

#endif /* __MOUSE_APP_H */
