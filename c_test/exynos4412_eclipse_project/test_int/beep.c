#include "exynos_4412.h"
#include "timer.h"
extern void (*fun_p[160])();

#define C (1000000 / 440)
#define YINDIAO(x) (100000000 / (x) )

void beep_init() {
	PWM.TCFG0 = (PWM.TCFG0 & (~(0XFF << 0))) | (99 << 0); //100 / (99 + 1) = 1Mhz
	PWM.TCFG1 = (PWM.TCFG1 & (~(0XF << 0))) | (0B0000 << 0); // 1M

}



void beep_on(int y) {
	static unsigned int yinjie[7] = {YINDIAO(44000),YINDIAO(49388),YINDIAO(55437),
			YINDIAO(58733),YINDIAO(65933),YINDIAO(73999),YINDIAO(83061)};

	PWM.TCNTB0 =  yinjie[y] ;
	PWM.TCMPB0 = yinjie[y] / 2;

	GPD0.CON = (GPD0.CON & (~(0xf << 0))) | (0x2 << 0);
	PWM.TCON = (PWM.TCON & (~0XFF)) | (0B1010 << 0);// UPDATE = 1 ,AUTO_RELOAD = 1  START = 0

	PWM.TCON = (PWM.TCON & (~0XFF)) | (0B1001 << 0);// UPDATE = 0 ,AUTO_RELOAD = 1  START = 1

}

void beep_short(int y,int ms){

	beep_on(y);

	timer4_start(ms,BEEP_TIME_OFF);


}
void beep_off() {

	GPD0.CON = (GPD0.CON & (~(0xf << 0))) ;
	PWM.TCON = (PWM.TCON & (~0XFF));
}

