/* Serial interface implementation.
 * We are using USART1, which is configured in setup.c
 * We also use 2 DMA channels (DMA controller 2, stream 7 for TX).
 */

#include "serial.h"

/* Reveived data from serial buffer:
 * This buffer is used by the USART RX DMA channel to store the incoming bytes.
 * Note that this buffer can be use by higher levels directly.
 */
static char receive_buffer[RECEIVE_BUFFER_SIZE] = {0};
/* Serial TX mutex 
 * This mutex is used to avoid more than one source writting at the same time.
 * The mutex is adquired by the user using serial_acquire_transfer_lock() and is
 * released by the USART TX DMA channel ISR. 
 */
static mutex_t _send_lock;
/* Command received flag.
 * This flag is set to true by the USART ISR if a '\0' is found, so the arrived data can be 
 * processed as a new command in upper layers.
 * The upper layers must set it again to false once processed.
 */
static volatile bool received = false;

/**
 * @brief Try to acquire the serial transfer lock.
 *
 * @return Whether the lock was acquired or not.
 */
bool serial_acquire_transfer_lock(void)
{
	return (bool)mutex_trylock(&_send_lock);
}

/**
 * @brief Send data through serial.
 *
 * DMA is configured to read from `data` a number `size` of bytes. It then
 * writes all those bytes to USART1.
 *
 * An interruption is generated when the transfer is complete.
 * 
 * Examples of DMA configuration for F4 in
 * https://github.com/libopencm3/libopencm3-examples/blob/master/examples/stm32/f4/stm32f4-discovery/dac-dma/dac-dma.c
 * https://github.com/froj/IMU/blob/master/sleephase.c
 *
 * @param[in] data Data to send.
 * @param[in] size Size (number of bytes) to send.
 */
void serial_send(char *data, int size)
{
	dma_stream_reset(DMA2, DMA_STREAM7);

	dma_enable_memory_increment_mode(DMA2, DMA_STREAM7);
	dma_set_peripheral_size(DMA2, DMA_STREAM7, DMA_SxCR_PSIZE_8BIT);
	dma_set_memory_size(DMA2, DMA_STREAM7, DMA_SxCR_MSIZE_8BIT);
	dma_set_priority(DMA2, DMA_STREAM7, DMA_SxCR_PL_VERY_HIGH);
	dma_set_transfer_mode(DMA2, DMA_STREAM7, DMA_SxCR_DIR_MEM_TO_PERIPHERAL);

	dma_set_peripheral_address(DMA2, DMA_STREAM7, (uint32_t)&USART1_DR);
	dma_set_memory_address(DMA2, DMA_STREAM7, (uint32_t)data);
	dma_set_number_of_data(DMA2, DMA_STREAM7, size);

	dma_enable_transfer_complete_interrupt(DMA2, DMA_STREAM7);
	dma_channel_select(DMA2, DMA_STREAM7, DMA_SxCR_CHSEL_4);
	dma_enable_stream(DMA2, DMA_STREAM7);
	usart_enable_tx_dma(USART1);
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

// USART IRQ example
// https://github.com/libopencm3/libopencm3-examples/tree/master/examples/stm32/f4/stm32f4-discovery/usart_irq