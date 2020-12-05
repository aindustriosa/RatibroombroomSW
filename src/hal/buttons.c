#include "buttons.h"

/**
 * @brief Function to read user button.
 */
bool button_read_user(void)
{
  return button_read_right();
}

/**
 * @brief Function to read SW1 - Left button.
 */
bool button_read_left(void)
{
  return (bool)(gpio_get(GPIOB, GPIO12));
}

/**
 * @brief Function to read SW2 - Right button.
 */
bool button_read_right(void)
{
  return (bool)(gpio_get(GPIOC, GPIO13));
}