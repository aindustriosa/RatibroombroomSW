#include "setup.h"

/**
 * @brief Empty main
 */
int main(void)
{

  setup();

  // FIXME: kinematic configuration goes here
  
  systick_interrupt_enable();
  return 0;
}
