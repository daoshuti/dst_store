#ifndef __TIMER_H__
#define __TIMER_H__

#include "exynos_4412.h"
#include "beep.h"
#include "interrupt.h"

#define BEEP_TIME_OFF 20

extern int key_number;

extern void timer4_open();
extern void timer4_start(int ms, int number);

#endif
