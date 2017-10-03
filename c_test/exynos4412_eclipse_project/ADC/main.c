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

int main(void)
{
	int value;

	uart_init();
	printf("ADC test:\n");

	GPK2.CONPDN &= (~(0xff << 8));//GPIOK2_2设置为input

	ADCMUX = 0b0011;//通道3 AIN3

	ADCCON |= (1<<16);//转换精度设为16位
	ADCCON |= (1<<14);//使能ADC时钟信号分频器
	ADCCON |= (0xff<<6);//分频系数为256
	ADCCON &= (~(1<<2));//Normal operation mode 正常工作模式
	ADCCON |= (1<<1);//设置为可读

	while(1)
	{
		ADCCON |= (1<<0);//开始ADC转换
		while( !(ADCCON&(~(1<<15))) );
		value =ADCDAT &0xfff;
		printf("ADC value = %d\tV:%d mv\n",value,value*1800/4096);
		mydelay_ms(500);
	}
	return 0;
}
