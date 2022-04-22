#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//外部中断 驱动代码			   
////////////////////////////////////////////////////////////////////////////////// 	

#define uchar unsigned char

extern u8 red,green,keystate;
u8 rtimes=0,gtimes=0;
extern void Decline();


//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY3==0)	 //按键3
	{
		keystate=0;
		gtimes=0;
		++rtimes;
		if(rtimes>=1){
			++red;
		}
	}
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}

//外部中断1服务程序
void EXTI1_IRQHandler(void)
{
	delay_ms(13);//消抖
	if(KEY2==0)	 //按键2
	{
		if(keystate==0){
			--red;
		}else if(keystate==1){
			--green;
		}
		//Decline();
	}		 
	EXTI->PR=1<<1;  //清除LINE1上的中断标志位  
}

//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==0)	 //按键1
	{
		keystate=1;
		rtimes=0;
		++gtimes;
		if(gtimes>=1){
			++green;
		}
	}	
	EXTI->PR=1<<2;  //清除LINE2上的中断标志位  
}

//外部中断初始化程序
//初始化PC0-2为中断输入.
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<4;     //使能PORTC时钟
	GPIOC->CRL&=0XFFFFF000;//PC0-2设置成输入	  
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,1,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,2,FTIR);//下降沿触发

	MY_NVIC_Init(2,2,EXTI0_IRQChannel,2);//抢占2，子优先级2，组2
	MY_NVIC_Init(2,1,EXTI1_IRQChannel,2);//抢占2，子优先级1，组2	   
	MY_NVIC_Init(2,0,EXTI2_IRQChannel,2);//抢占2，子优先级1，组2
}












