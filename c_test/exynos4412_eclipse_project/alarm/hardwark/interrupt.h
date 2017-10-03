#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "exynos_4412.h"

extern void (*fun_p[160])(); //中断函数指针数组，即中断函数入口地址表

extern void do_irq(void);

#endif
