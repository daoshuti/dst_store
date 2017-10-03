/*
 *@brief	This example describes how to use GPIO to drive LEDs
 *@date:	02. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"


/**********************************************************************
 * @brief		mydelay_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	/*
	 *Config
	 */
	int s,m,h,d,moon,y;
	uart_init();
	printf("RTC:\n");

	RTCCON |= (1<<0);
	RTCCON &= ~(1<<3);

	RTC.BCDSEC = 0x0;
	RTC.BCDMIN = 0x20;
	RTC.BCDHOUR = 0x15;

	RTC.BCDDAY = 0x28;
//	RTC.BCDWEEK = 0x28;
	RTC.BCDMON = 0x10;
	RTC.BCDYEAR = 0x016;
	RTCCON &= ~(1<<0);

	while(1)
	{
		s = ((0xf0 & RTC.BCDSEC)>>4)*10+(0xf & RTC.BCDSEC);
		m = ((0xf0 & RTC.BCDMIN)>>4)*10+(0xf & RTC.BCDMIN);
		h = ((0xf0 & RTC.BCDHOUR)>>4)*10+(0xf & RTC.BCDHOUR);

		d = ((0xf0 & RTC.BCDDAY)>>4)*10+(0xf & RTC.BCDDAY);
//		d = ((0xf0 & RTC.BCDWEEK)>>4)*10+(0xf & RTC.BCDWEEK);
		moon = ((0xf0 & RTC.BCDMON)>>4)*10+(0xf & RTC.BCDMON);
		y = ((0xf0 & RTC.BCDYEAR)>>4)*10+(0xf & RTC.BCDYEAR);
		printf("20%d/%d/%d %d:%d:%d\n",y,moon,d,h,m,s);
		mydelay_ms(500);
	}
	return 0;
}
