
#ifndef PwmExt_h
#define PwmExt_h

#include <inttypes.h>

void PwmExt_setup(int);
void PwmExt_write(int, byte);
int PwmExt_getMaxPorts();
void PwmExt_allOff();
void PwmExt_allOn();
void PwmExt_allOTo(int, int);
void PwmExt_portInvertEnable(int);

#endif
