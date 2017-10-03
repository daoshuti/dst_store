#include "timer.h"

#define BEEP_TIME_OFF 20

int key_number;

void timer4_int() {

	switch (key_number) {
	case 2:
		if (0 == (GPX1.DAT & (1 << 1))) { // 延时判断消抖
			printf("------------------------------key2\n");
			beep_short(1, 300);
		}
		break;
	case 3:
		if (0 == (GPX1.DAT & (1 << 2))) { // 延时判断消抖
			printf("------------------------------key3\n");
			beep_short(2, 300);
		}
		break;
	case 4:
		if (0 == (GPX3.DAT & (1 << 2))) { // 延时判断消抖
			printf("------------------------------key4\n");
			beep_short(3, 300);
		}
		break;

	case BEEP_TIME_OFF:
		beep_off();
		break;
	}
	key_number = -1;
	PWM.TINT_CSTAT = (PWM.TINT_CSTAT & 0X1F) | (1 << 9);
	ICDICPR.ICDICPR2 = (1 << 9); //清除中断混合器ICD
}

void timer4_start(int ms, int number) {

	PWM.TCNTB4 = 1000 * ms;
	PWM.TCON = (PWM.TCON & (~(0Xf << 20))) | (0B110 << 20); // AUTO_RELOAD = 1 ,UPDATE = 1 ,START = 0
	PWM.TCON = (PWM.TCON & (~(0Xf << 20))) | (0B001 << 20); // AUTO_RELOAD = 0 ,UPDATE = 0 ,START = 1

	key_number = number;
}

void timer4_open() {

	PWM.TCFG0 = (PWM.TCFG0 & (~(0XFF << 8))) | (99 << 8); //100 / (99 + 1) = 1Mhz
	PWM.TCFG1 = (PWM.TCFG1 & (~(0XF << 16))) | (0B0000 << 16); // 1M / 1

	PWM.TCON = (PWM.TCON & (~(0Xf << 20))) | (0B000 << 20); //START = 0
	PWM.TINT_CSTAT = (PWM.TINT_CSTAT & 0X1F) | (1 << 4);

	fun_p[73] = timer4_int;
	//41  73  –  TIMER4
	ICDISER.ICDISER2 |= (1 << 9); //使能73号中断 检测
	ICDIPTR.ICDIPTR18 = (ICDIPTR.ICDIPTR18 & (~(0xff << 8)))
			| (0b00000001 << 8); //将中断58 送到 cpu0

	ICDDCR = 1; //设置 监控所有中断

	CPU0.ICCICR = 1; //使能icc
}
