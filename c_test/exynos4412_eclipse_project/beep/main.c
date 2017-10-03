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

void mydelay_us(int us)
{
	int i, j;
	while(us--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 51; j++);
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

	GPD0.CON = (GPD0.CON & ~(0xf<<0))| (0x1<<0);

	while(1)
	{
		GPD0.DAT |= 0x1 << 0;
		mydelay_us(800);

		GPD0.DAT &= ~(0x1 << 0);
		mydelay_us(800);

	}
	return 0;
}
