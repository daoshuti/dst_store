#include "interrupt.h"

void (*fun_p[160])();

void do_irq(void) {
	int irq_number;
	irq_number = CPU0.ICCIAR & 0x3ff; //读取中断号，通知 中断开始执行
	printf("irq_number = %d\n", irq_number);

	if (irq_number <= 159)
		(*fun_p[irq_number])();

	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3ff) | irq_number; //通知icc中断结束
}
