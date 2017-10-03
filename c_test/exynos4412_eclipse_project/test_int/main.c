/*
 *@brief	This example describes how to use GPIO to drive LEDs
 *@date:	02. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
 */

#include "exynos_4412.h"
#include "beep.h"
#include "key.h"

const char b[200]={
			5,3,4,5,3,4,5,5,6,7,1,2,3,4,3,1,2,3,3,4,5,6,5,4,5,1,7,1,6,1,7,6,
			5,4,5,4,3,4,5,6,7,1,6,1,7,1,7,1,7,6,7,1,2,3,4,5,5,3,4,5,3,4,5,5,
			6,7,1,2,3,4,3,1,2,3,3,4,5,6,5,4,5,1,7,1,6,1,7,6,5,4,5,4,3,4,5,6,
			1,7,6,1,7,1,7,6,7,1,2,1,7,1,6,7,1};

void liushuideng();
/**********************************************************************
 * @brief		mydelay_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int ms) {
	int i, j;
	while (ms--) {
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++)
				;
	}
}
void mydelay_10us(int us) {
	int i, j;
	while (us--) {
		for (i = 0; i < 5; i++)
			for (j = 0; j < 5; j++)
				;
	}
}

void (*fun_p[160])();
void do_irq(void) {
	int irq_number;
	irq_number = CPU0.ICCIAR & 0x3ff;//读取中断号，通知 中断开始执行
	printf("irq_number = %d\n", irq_number);

	if (irq_number <= 159)
		(*fun_p[irq_number])();

	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3ff) | irq_number; //通知icc中断结束
}


int main(void) {

	int c,i;
	beep_init();
	uart_init();

	key_init();
	key4_init();
//	liushuideng();

	while(1)
	{

		c = b[i];
		beep_short(c,300);
//		music(a[c]*2,500);
		i++;
		if(i>143)i=0;
	}

	while (1)
		;
	return 0;
}



void liushuideng() {
	int i;

	//led5
	GPF3.CON = (GPF3.CON & (~(0xf << 20))) | (0x1 << 20);
	GPF3.DAT |= (1 << 5);
	//lde4
	GPF3.CON = (GPF3.CON & (~(0xf << 16))) | (0x1 << 16);
	GPF3.DAT |= (1 << 4);
	//lde3
	GPX1.CON = (GPX1.CON & (~(0xf << 0))) | (0x1 << 0);
	GPX1.DAT |= (1 << 0);
	//LDE2
	GPX2.CON = (GPX2.CON & (~(0XF << 28))) | (0X1 << 28);
	GPX2.DAT &= ~(1 << 7);

	i = 2;
	while (1) {
		GPF3.DAT &= ~(1 << 5);
		GPF3.DAT &= ~(1 << 4);
		GPX1.DAT &= ~(1 << 0);
		GPX2.DAT &= ~(1 << 7);

		switch (i) {
		case 2:
			GPX2.DAT |= (1 << 7);
			break;
		case 3:
			GPX1.DAT |= (1 << 0);
			break;
		case 4:
			GPF3.DAT |= (1 << 4);
			break;
		case 5:
			GPF3.DAT |= (1 << 5);
			break;
		default:
			break;
		}
		i++;
		if (i > 5)
			i = 2;
		mydelay_ms(500);
	}
}
