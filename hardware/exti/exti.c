#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�ⲿ�ж� ��������			   
////////////////////////////////////////////////////////////////////////////////// 	

#define uchar unsigned char

extern u8 red,green,keystate;
u8 rtimes=0,gtimes=0;
extern void Decline();


//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY3==0)	 //����3
	{
		keystate=0;
		gtimes=0;
		++rtimes;
		if(rtimes>=1){
			++red;
		}
	}
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}

//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{
	delay_ms(13);//����
	if(KEY2==0)	 //����2
	{
		if(keystate==0){
			--red;
		}else if(keystate==1){
			--green;
		}
		//Decline();
	}		 
	EXTI->PR=1<<1;  //���LINE1�ϵ��жϱ�־λ  
}

//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	 //����1
	{
		keystate=1;
		rtimes=0;
		++gtimes;
		if(gtimes>=1){
			++green;
		}
	}	
	EXTI->PR=1<<2;  //���LINE2�ϵ��жϱ�־λ  
}

//�ⲿ�жϳ�ʼ������
//��ʼ��PC0-2Ϊ�ж�����.
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
	GPIOC->CRL&=0XFFFFF000;//PC0-2���ó�����	  
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,1,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,2,FTIR);//�½��ش���

	MY_NVIC_Init(2,2,EXTI0_IRQChannel,2);//��ռ2�������ȼ�2����2
	MY_NVIC_Init(2,1,EXTI1_IRQChannel,2);//��ռ2�������ȼ�1����2	   
	MY_NVIC_Init(2,0,EXTI2_IRQChannel,2);//��ռ2�������ȼ�1����2
}












