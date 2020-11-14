#ifndef __SERIAL_H
#define __SERIAL_H

#include <libopencm3/cm3/sync.h>
#include <libopencm3/stm32/usart.h>
#include "mmlib/logging.h"

#define RECEIVE_BUFFER_SIZE 256   // Used by mmlib (command) // FIXME: bulebule specs

bool get_received_command_flag(void); // Used by mmlib (command)
void set_received_command_flag(bool value); // Used by mmlib (command)
bool serial_acquire_transfer_lock(void);  // Used by mmlib
void serial_send(char *data, int size);  // Used by mmlib
char *get_received_serial_buffer(void); // Used by mmlib (command)

#endif /* __SERIAL_H */
