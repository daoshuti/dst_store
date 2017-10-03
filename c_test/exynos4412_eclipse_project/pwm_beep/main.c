#include "exynos_4412.h"
/*
const char b[200]={
			5,3,4,5,3,4,5,5,6,7,1,2,3,4,3,1,2,3,3,4,5,6,5,4,5,1,7,1,6,1,7,6,
			5,4,5,4,3,4,5,6,7,1,6,1,7,1,7,1,7,6,7,1,2,3,4,5,5,3,4,5,3,4,5,5,
			6,7,1,2,3,4,3,1,2,3,3,4,5,6,5,4,5,1,7,1,6,1,7,6,5,4,5,4,3,4,5,6,
			1,7,6,1,7,1,7,6,7,1,2,1,7,1,6,7,1};
*/
/*
const char b[]={
		5,5,6,5,1,7,
		5,5,6,5,2,1,
		5,5,5,3,1,7,6,
		4,4,3,1,2,1
};
*/
void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

void music(int hz,int t)
{
//	PWM.TCNTB0 = hz-1;//  例计数1000次    hz=1000 1M/1000 = 1KHz
//	PWM.TCMPB0 = hz/2;
	PWM.TCNTB0 = (hz-1)*2;//  例计数1000次    hz=1000 1M/1000 = 1KHz
	PWM.TCMPB0 = hz;
	PWM.TCON = (PWM.TCON & (~0xff)) | (0b1010 << 0);//UPDATE = 1,AUTO_RELOAD = 1 START = 0
	PWM.TCON = (PWM.TCON & (~0xff)) | (0b1001 << 0);//UPDATE = 0,AUTO_RELOAD = 1 START = 1

	mydelay_ms(t);
}

int main(void)
{
	/*
	 *Config
	 */
	int i,c;
	int a[]={256,288,320,341,384,426,480};


	GPD0.CON = (GPD0.CON & (~(0xf << 0))) | (0x2 << 0);

	PWM.TCFG0 = (PWM.TCFG0 & (~(0xff<<0))) | (99 << 0);// 100M/(99+1) = 1MHz
	PWM.TCFG1 = (PWM.TCFG1 & (~(0xf<<0))) | (0b0000 << 0);// 1分频  1M/1 = 1MHz
//	PWM.TCFG1 = (PWM.TCFG1 & (~(0xf<<0))) | (0b0001 << 0);// 1分频  1M/2 = 500 KHz

	while(1)
	{

//		c = b[i];
//		music(a[c]*2,500);
//		i++;
//		if(i>=25)i=0;
		music(a[1],500);music(a[2],500);music(a[3],500);music(a[1],500);
		music(a[1],500);music(a[2],500);music(a[3],500);music(a[1],500);
		music(a[3],500);music(a[4],500);music(a[5],500);mydelay_ms(500);

		music(a[5],250);music(a[6],250);music(a[5],250);music(a[4],250);music(a[3],500);music(a[1],500);
		music(a[5],250);music(a[6],250);music(a[5],250);music(a[4],250);music(a[3],500);music(a[1],500);
		music(a[2],500);music(a[5],500);music(a[1],500);mydelay_ms(500);
		music(a[2],500);music(a[5],500);music(a[1],500);mydelay_ms(500);
	}

	while(1)
		;
	return 0;
}
