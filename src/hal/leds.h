#ifndef __LEDS_H
#define __LEDS_H

#include <libopencm3/stm32/gpio.h>

void all_leds_on(void);
void all_leds_off(void);
void all_leds_toggle(void);

void leds_binary(char binary);

void led_FL_on(void);
void led_FR_on(void);
void led_RL_on(void);
void led_RR_on(void);

void led_FL_off(void);
void led_FR_off(void);
void led_RL_off(void);
void led_RR_off(void);

void led_FL_toggle(void);
void led_FR_toggle(void);
void led_RL_toggle(void);
void led_RR_toggle(void);

// mmlib functions
void led_left_on(void);
void led_left_off(void);
void led_left_toggle(void);
void led_right_on(void);
void led_right_off(void);
void led_right_toggle(void);

#endif
