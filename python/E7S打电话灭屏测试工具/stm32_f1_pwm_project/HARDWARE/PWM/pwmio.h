#ifndef __PWMIO__H
#define __PWMIO__H	 
#include "sys.h"

#define PWM_IO PBout(7)// PB7

void PWM_IO_Init(void);//初始化
void SetPWM_Threshold(int val);//设置PWM阈值
void PWM_Handler(void);//PWM处理句柄

		 				    
#endif
