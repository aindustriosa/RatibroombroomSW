/* Serial Port Interface.
 * This serial port is used for user interaction through commands and logging. 
 */

#ifndef __SERIAL_H
#define __SERIAL_H

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/sync.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>

#define RECEIVE_BUFFER_SIZE 256   // Used by mmlib (command) // FIXME: move to bulebule specs?

/**
 * @brief Checks if a command has arrived (command_flag == true).
 * 
 *  Used by mmlib (command)
 *
 *@return True if the buffer contains a command to be executed.
 */
bool get_received_command_flag(void);

/**
 * @brief Sets the value of command_flag (true if a command waits to be executed).
 * 
 *  Used by mmlib (command)
 *
 * @param[in] bool New flag value.
 */
void set_received_command_flag(bool value);

/**
 * @brief TODO
 * 
 *  Used by mmlib
 *
 *@return TODO
 */
bool serial_acquire_transfer_lock(void);

/**
 * @brief TODO
 * 
 *  Used by mmlib
 *
 * @param[in] data Data to send.
 * @param[in] size Size (number of bytes) to send.
 */
void serial_send(char *data, int size);

/**
 * @brief Returns the serial buffer address where the incoming bytes are stored.
 * 
 *  Used by mmlib (command)
 *
 *@return a pointer to the char array
 */
char *get_received_serial_buffer(void);

#endif /* __SERIAL_H */
