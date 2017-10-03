#ifndef __BEEP_H__
#define __BEEP_H__

#include "exynos_4412.h"
#include "timer.h"

extern void beep_init();
extern void beep_on(int y);
extern void beep_off();
extern void beep_short(int y, int ms);

#endif
