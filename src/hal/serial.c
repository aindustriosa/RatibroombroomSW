#include "serial.h"


static char receive_buffer[RECEIVE_BUFFER_SIZE];


/**
 * @brief Try to acquire the serial transfer lock.
 *
 * @return Whether the lock was acquired or not.
 */
bool serial_acquire_transfer_lock(void)
{
  //FIXME: mock
  return false;

}


/**
 * @brief Send data through serial.
 *
 * DMA is configured to read from `data` a number `size` of bytes. It then
 * writes all those bytes to USART3 (Bluetooth).
 *
 * An interruption is generated when the transfer is complete.
 *
 * @param[in] data Data to send.
 * @param[in] size Size (number of bytes) to send.
 */
void serial_send(char *data, int size)
{
  //FIXME: mock
  
}

bool get_received_command_flag(void)
{
  // FIXME: mock
  return false;
}

void set_received_command_flag(bool value)
{
  // FIXME: mock
}

char *get_received_serial_buffer(void)
{
	return receive_buffer;
}
