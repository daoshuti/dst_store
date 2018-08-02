#include "pwmio.h"
#include "led.h"

static int threshold = 0;

//PWM IO初始化
void PWM_IO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //PWM IO-->PB.7 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOCB.7
 GPIO_SetBits(GPIOB,GPIO_Pin_7); 						 //PB.7 输出高 

}

void SetPWM_Threshold(int val)
{
	threshold = val;
}

void PWM_Handler(void)
{
	static int count = 0;
	count++;
	if (count > 2000)
		count = 0;
	else if(count > threshold)
	{
		PWM_IO = 0;
	}
	else
	{
		PWM_IO = 1;
	}
}
