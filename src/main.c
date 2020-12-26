#include "setup.h"
#include "mouse_app.h"
#include "mmlib/speed.h"

/**
 * @brief Empty main
 */
int main(void)
{

  setup();

  // FIXME: kinematic configuration goes here
  kinematic_configuration(0.25, false);
  systick_interrupt_enable();

  loop();
  
  return 0;
}
