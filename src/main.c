#include "setup.h"
#include "app/mouse_app.h"
#include "mmlib/speed.h"

/**
 * @brief Program entry point
 */
int main(void)
{

  setup();

  kinematic_configuration(0.25, false);
  systick_interrupt_enable();

  loop();
  
  return 0;
}
