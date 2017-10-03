#include "exynos_4412.h"

void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

void do_irq(void){
	int irq_number;
	irq_number = CPU0.ICCIAR & 0x3ff;//读取中断号，通知中断开始执行

	printf("irq_number = %d\n",irq_number);

	switch(irq_number){
	case 57:
		printf("KEY2\n",irq_number);

		EXT_INT41_PEND = (1 << 1);//清除中断源
		ICDICPR.ICDICPR1 = (1 << 25);//清除中断混合器ICD
		break;
	case 58:
			mydelay_ms(50);
			if(0 == (GPX1.DAT & (1 << 2)))
				printf("KEY3\n",irq_number);

		EXT_INT41_PEND = (1 << 2);//清除中断源
		ICDICPR.ICDICPR1 = (1 << 26);//清除中断混合器ICD
		break;
	}
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3ff) | irq_number;//通知ICC中断结束
}

int main(void)
{
	/*
	 *Config
	 */
	uart_init();
	printf("Hello World!\n");

//-------------------------K2-------------------------//
	GPX1.CON |= (0xf << 4);//设置为外部中断模式
	EXT_INT41_CON = (EXT_INT41_CON & (~(0xf << 4))) | (0x2 << 4);//设置下降沿触发信号

	EXT_INT41_FLTCON0 |= 1 << 15;
	EXT_INT41_FLTCON0 &= ~(1 << 14);//开启选择不精确延时滤波

	EXT_INT41_MASK &= ~(1 << 1);//使能中断传递到GIC

	//25 57  -  EINT[9]

	ICDISER.ICDISER1 |= (1 << 25);//使能57号中断检测
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & (~(0xff << 8)))
			| (0b00000001 << 8);//将中断57送到cpu0
	ICDDCR = 1;//设置监控所有中断
	CPU0.ICCICR = 1;//使能ICC

//-------------------------K3-------------------------//

	GPX1.CON |= (0xf << 8);//设置为外部中断模式
	EXT_INT41_CON = (EXT_INT41_CON & (~(0xf << 8))) | (0x2 << 8);//设置下降沿触发信号

	EXT_INT41_FLTCON0 |= 1 << 23;
	EXT_INT41_FLTCON0 &= ~(1 << 22);//开启选择不精确延时滤波

	EXT_INT41_MASK &= ~(1 << 2);//使能中断传递到GIC

	//26 58  -  EINT[10]

	ICDISER.ICDISER1 |= (1 << 26);//使能57号中断检测
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & (~(0xff << 16)))
			| (0b00000001 << 16);//将中断57送到cpu0
	ICDDCR = 1;//设置监控所有中断
	CPU0.ICCICR = 1;//使能ICC

	while(1)
		;
	return 0;
}
