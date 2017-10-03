#include "beep.h"

#define YINDIAO(x) (100000000 / (x) )

void beep_init() {
	PWM.TCFG0 = (PWM.TCFG0 & (~(0XFF << 0))) | (99 << 0); //100 / (99 + 1) = 1Mhz
	PWM.TCFG1 = (PWM.TCFG1 & (~(0XF << 0))) | (0B0000 << 0); // 1M
}

void beep_on(int y) {
	static unsigned int yinjie[22] = { 0,
			YINDIAO(22000),YINDIAO(24697),YINDIAO(27719),YINDIAO(29367),YINDIAO(32963),YINDIAO(37000),YINDIAO(41531),
			YINDIAO(44000),YINDIAO(49388),YINDIAO(55437), YINDIAO(58733), YINDIAO(65933), YINDIAO(73999),YINDIAO(83061),
			YINDIAO(88000),YINDIAO(98776),YINDIAO(110873),YINDIAO(117466),YINDIAO(131852),YINDIAO(147998),YINDIAO(166122)};

	PWM.TCNTB0 = yinjie[y];
	PWM.TCMPB0 = yinjie[y] / 2;

	GPD0.CON = (GPD0.CON & (~(0xf << 0))) | (0x2 << 0);
	PWM.TCON = (PWM.TCON & (~0XFF)) | (0B1010 << 0); // AUTO_RELOAD = 1 ,UPDATE = 1 ,START = 0

	PWM.TCON = (PWM.TCON & (~0XFF)) | (0B1001 << 0); // AUTO_RELOAD = 1 ,UPDATE = 0 ,START = 1
}

void beep_short(int y, int ms) {
	beep_on(y);
	timer4_start(ms, BEEP_TIME_OFF);
}

void beep_off() {
	GPD0.CON = (GPD0.CON & (~(0xf << 0)));
	PWM.TCON = (PWM.TCON & (~0XFF));
}

