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
/* Some helpers for the serial functions.
 * They are implemented at the end of this file.
 */
void usart_enable_idle_line_interrupt(uint32_t usart);
void usart_disable_idle_line_interrupt(uint32_t usart);
bool usart_idle_line_detected(uint32_t usart);
void usart_clear_idle_line_detected(uint32_t usart);


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


/**
 * @brief Receive data from serial.
 *
 * DMA2 is configured to read from USART1 (Bluetooth) a number `size` of bytes.
 * It writes all those bytes to `data`.
 *
 * An interruption is generated when the transfer is complete.
 */
static void serial_receive(void)
{
  dma_stream_reset(DMA2, DMA_STREAM5);
  dma_enable_memory_increment_mode(DMA2, DMA_STREAM5);
  dma_set_peripheral_size(DMA2, DMA_STREAM5, DMA_SxCR_PSIZE_8BIT);
  dma_set_memory_size(DMA2, DMA_STREAM5, DMA_SxCR_MSIZE_8BIT);
  dma_set_priority(DMA2, DMA_STREAM5, DMA_SxCR_PL_VERY_HIGH);
  dma_set_transfer_mode(DMA2, DMA_STREAM5, DMA_SxCR_DIR_PERIPHERAL_TO_MEM);
  
  dma_set_peripheral_address(DMA2, DMA_STREAM5, (uint32_t)&USART3_DR);
  
  dma_set_peripheral_address(DMA2, DMA_STREAM5, (uint32_t)&USART1_DR);
  dma_set_memory_address(DMA2, DMA_STREAM5, (uint32_t)receive_buffer);
  dma_set_number_of_data(DMA2, DMA_STREAM5, RECEIVE_BUFFER_SIZE);

  dma_enable_transfer_complete_interrupt(DMA2, DMA_STREAM5);
  dma_channel_select(DMA2, DMA_STREAM5, DMA_SxCR_CHSEL_4);
  dma_enable_stream(DMA2, DMA_STREAM5);
  usart_enable_rx_dma(USART1);
  
}


/**
 * @brief DMA 2 stream 7 interruption routine.
 *
 * Executed on serial transfer complete. Clears the interruption flag, and
 * disables serial transfer DMA until next call to `serial_send()`.
 *
 * It will also release the serial transfer lock.
 */
void dma2_stream7_isr(void)
{
	if (dma_get_interrupt_flag(DMA2, DMA_STREAM7, DMA_TCIF))
		dma_clear_interrupt_flags(DMA2, DMA_STREAM7, DMA_TCIF);

	dma_disable_transfer_complete_interrupt(DMA2, DMA_STREAM7);
	usart_disable_tx_dma(USART1);
	dma_disable_stream(DMA2, DMA_STREAM7);
	mutex_unlock(&_send_lock);
}

/**
 * @brief DMA 2 stream 5 interruption routine.
 *
 * Executed on serial receive complete. Clears the interruption flag, and
 * resets the receive DMA by calling `serial_receive()`.
 *
 * This function should never be reached. Commands should be processed before
 * on USART idle line interruption.
 * see streams DMA mapping in section 10.3.3 (channel selection) of stm32f4 reference manual
 **/
void dma2_stream5_isr(void)
{
	if (dma_get_interrupt_flag(DMA2, DMA_STREAM5, DMA_TCIF))
		dma_clear_interrupt_flags(DMA2, DMA_STREAM5, DMA_TCIF);

	dma_disable_transfer_complete_interrupt(DMA2, DMA_STREAM5);
	usart_disable_rx_dma(USART1);
	dma_disable_stream(DMA2, DMA_STREAM5);
	// LOG_ERROR("Receive buffer is full! Resetting..."); //FIXME: check after making logging functinality
	serial_receive();
}



/**
 * @brief USART interruption routine.
 *
 * On RX interruption it will process the data received and, in case it finds
 * a `'\0'` character, the `process_command` function will be executed.
 */
void usart1_isr(void)
{
  /* Only execute on idle interrupt */
  if (((USART_CR1(USART1) & USART_CR1_IDLEIE) != 0) &&
      usart_idle_line_detected(USART1)) {
    received = true;
    usart_clear_idle_line_detected(USART1);
    serial_receive();
  }
}


// USART IRQ example
// https://github.com/libopencm3/libopencm3-examples/tree/master/examples/stm32/f4/stm32f4-discovery/usart_irq


bool get_received_command_flag(void)
{
  return received;
}

void set_received_command_flag(bool value)
{
  received = value;
}

char *get_received_serial_buffer(void)
{
  return receive_buffer;
}


/**
 * @brief USART idle line interrupt enable.
 *
 * @param[in] usart USART block register address base.
 */
void usart_enable_idle_line_interrupt(uint32_t usart)
{
	USART_CR1(usart) |= USART_CR1_IDLEIE;
}

/**
 * @brief USART idle line interrupt disable.
 *
 * @param[in] usart USART block register address base.
 */
void usart_disable_idle_line_interrupt(uint32_t usart)
{
	USART_CR1(usart) &= ~USART_CR1_IDLEIE;
}

/**
 * @brief Check USART idle line detected bit in Status Register.
 *
 * @param[in] usart USART block register address base.
 */
bool usart_idle_line_detected(uint32_t usart)
{
	return ((USART_SR(usart) & USART_SR_IDLE) != 0);
}

/**
 * @brief Clear USART idle line detected bit in Status Register.
 *
 * Clear is performed by a software sequence: a read to the USART_SR register
 * followed by a read to the USART_DR register.
 *
 * @param[in] usart USART block register address base.
 *
 * @see Reference Manual (RM0008): Status register (USART_SR).
 */
void usart_clear_idle_line_detected(uint32_t usart)
{
	USART_SR(usart);
	USART_DR(usart);
}
