#ifndef __MYUSART_H
#define __MYUSART_H

#include <libopencm3/stm32/usart.h>

void usart_enable_idle_line_interrupt(uint32_t usart);
void usart_disable_idle_line_interrupt(uint32_t usart);
bool usart_idle_line_detected(uint32_t usart);
void usart_clear_idle_line_detected(uint32_t usart);


#endif /* __MYUSART_H */
