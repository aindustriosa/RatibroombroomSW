#ifndef __SPEAKER_H
#define __SPEAKER_H


#include <libopencm3/stm32/timer.h>
#include "setup.h"

void speaker_on(float hz);  // Used by mmlib (music)
void speaker_off(void);   // Used by mmlib (music)

#endif /* __SPEAKER_H */
