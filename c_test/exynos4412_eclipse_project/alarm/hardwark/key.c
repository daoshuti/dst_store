#include "key.h"

void key2_int() {

	timer4_start(50, 2);

	EXT_INT41_PEND = (1 << 1); // 清除中断源
	ICDICPR.ICDICPR1 = (1 << 25); //清除中断混合器ICD
}

void key3_int() {

	timer4_start(50, 3);

	EXT_INT41_PEND = (1 << 2); // 清除中断源
	ICDICPR.ICDICPR1 = (1 << 26); //清除中断混合器ICD
}

void key_init() {

	timer4_open();

	// --------------------------key2-------------------------
	GPX1.CON |= (0xf << 4); //设置为外部中断模式
	EXT_INT41_CON = (EXT_INT41_CON & (~(0XF << 4))) | (0X2 << 4); //设置 下降沿信号触发中断

	EXT_INT41_FLTCON0 |= 1 << 15;
	EXT_INT41_FLTCON0 &= ~(1 << 14); //开启并选择不精准延时滤波

	EXT_INT41_MASK &= ~(1 << 1); //使能中断传递到 GIC

	//25  57  –  EINT[9]
	fun_p[57] = key2_int;

	ICDISER.ICDISER1 |= (1 << 25); //使能57号中断 检测
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & (~(0xff << 8)))
			| (0b00000001 << 8); //将中断57 送到 cpu0

	//---------------------key3------------------------------------

	GPX1.CON |= (0xf << 8); //设置为外部中断模式
	EXT_INT41_CON = (EXT_INT41_CON & (~(0XF << 8))) | (0X2 << 8); //设置 下降沿信号触发中断

	EXT_INT41_FLTCON0 |= 1 << 23;
	EXT_INT41_FLTCON0 &= ~(1 << 22); //开启并选择不精准延时滤波

	EXT_INT41_MASK &= ~(1 << 2); //使能中断传递到 GIC

	//26  58  –  EINT[10]
	fun_p[58] = key3_int;

	ICDISER.ICDISER1 |= (1 << 26); //使能58号中断 检测
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & (~(0xff << 16)))
			| (0b00000001 << 16); //将中断58 送到 cpu0

	ICDDCR = 1; //设置 监控所有中断

	CPU0.ICCICR = 1; //使能icc

}

void eint16_31_int() {

	if (EXT_INT43_PEND & (1 << 2)) {
		timer4_start(50, 4);

		EXT_INT43_PEND = (1 << 2); // 清除中断源
	} else if (0) {

	}
	ICDICPR.ICDICPR1 = (1 << 26); //清除中断混合器ICD
}

void key4_init() {

	timer4_open();

	GPX3.CON |= (0xf << 8); //设置为外部中断模式
	EXT_INT43_CON = (EXT_INT43_CON & (~(0XF << 8))) | (0X2 << 8); //设置 下降沿信号触发中断

	EXT_INT43_FLTCON0 |= 1 << 23;
	EXT_INT43_FLTCON0 &= ~(1 << 22); //开启并选择不精准延时滤波

	EXT_INT43_MASK &= ~(1 << 2); //使能中断传递到 GIC

	//32  64  –  EINT16_31[26]
	fun_p[64] = eint16_31_int;

	ICDISER.ICDISER2 |= (1 << 0); //使能64号中断 检测
	ICDIPTR.ICDIPTR16 = (ICDIPTR.ICDIPTR16 & (~(0xff << 0)))
			| (0b00000001 << 0); //将中断64 送到 cpu0

	ICDDCR = 1; //设置 监控所有中断

	CPU0.ICCICR = 1; //使能icc

}
