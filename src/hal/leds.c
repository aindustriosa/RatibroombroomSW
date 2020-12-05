#include "leds.h"

/**
 * @brief LED_FL ON
 */
void led_FL_on(void) { gpio_set(GPIOA, GPIO0); }

/**
 * @brief LED_FR ON
 */
void led_FR_on(void) { gpio_set(GPIOA, GPIO1); }

/**
 * @brief LED_RL ON
 */
void led_RL_on(void) { gpio_set(GPIOA, GPIO2); }

/**
 * @brief LED_RR ON
 */
void led_RR_on(void) { gpio_set(GPIOA, GPIO3); }

/**
 * @brief LED_FL OFF
 */
void led_FL_off(void) { gpio_clear(GPIOA, GPIO0); }

/**
 * @brief LED_FR OFF
 */
void led_FR_off(void) { gpio_clear(GPIOA, GPIO1); }

/**
 * @brief LED_RL OFF
 */
void led_RL_off(void) { gpio_clear(GPIOA, GPIO2); }

/**
 * @brief LED_RR OFF
 */
void led_RR_off(void) { gpio_clear(GPIOA, GPIO3); }

/**
 * @brief LED_FL toggle
 */
void led_FL_toggle(void) { gpio_toggle(GPIOA, GPIO0); }

/**
 * @brief LED_FR toggle
 */
void led_FR_toggle(void) { gpio_toggle(GPIOA, GPIO1); }

/**
 * @brief LED_RL toggle
 */
void led_RL_toggle(void) { gpio_toggle(GPIOA, GPIO2); }

/**
 * @brief LED_RR toggle
 */
void led_RR_toggle(void) { gpio_toggle(GPIOA, GPIO3); }

/**
 * @brief Set binary number in leds array
 *
 * @param binary 4-bit number represting FL,FR,RL,RR
 */
void leds_binary(char binary) {

  led_FL_off();
  led_FR_off();
  led_RL_off();
  led_RR_off();

  if (binary && 0b0001) {
    led_FL_on();
  }
  if (binary && 0b0010) {
    led_FR_on();
  }
  if (binary && 0b0100) {
    led_RL_on();
  }
  if (binary && 0b1000) {
    led_RR_on();
  }
}

/**
 * @brief All LEDs ON
 */
void all_leds_on(void) { leds_binary(0b1111); }

/**
 * @brief All LEDs OFF
 */
void all_leds_off(void) { leds_binary(0b0000); }

/**
 * @brief All LEDs toggle
 */
void all_leds_toggle(void)
{
    led_FL_toggle();
    led_FR_toggle();
    led_RL_toggle();
    led_RR_toggle();
}


/*******************************************************
 * MMLIB Functions
 *******************************************************/

/**
 * @brief Function to toggle the left LED.
 */
void led_left_toggle(void)
{
	led_RL_toggle();
}

/**
 * @brief Function to toggle the right LED.
 */
void led_right_toggle(void)
{
	led_RR_toggle();
}

/**
 * @brief Function to power ON the left LED.
 */
void led_left_on(void)
{
	led_RL_on();
}

/**
 * @brief Function to power ON the right LED.
 */
void led_right_on(void)
{
	led_RR_on();
}

/**
 * @brief Function to power OFF the left LED.
 */
void led_left_off(void)
{
	led_RR_off();
}

/**
 * @brief Function to power OFF the right LED.
 */
void led_right_off(void)
{
	led_RR_off();
}