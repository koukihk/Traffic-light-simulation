#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "timer.h"

#define uchar unsigned char

u8 red=0;
u8 green=5;
u8 state=0;
u8 keystate=0;


void Signal(){
	uchar i,k;
	LED_SEL=0;
	
	for(k=0;k<200;k++){
		if(k%2 == 0){
			LED_SEL = 1;
			GPIOE->ODR &= ~(0xff<<8);
			GPIOE->ODR |= (0xcf<<8);
			delay_ms(3);
		}
		else{
			LED_SEL=0;
			for(i=0;i<8;i++){
				switch(i){
					case 0:
						SetLed(i,red/10);
						delay_ms(3);
						break;
					case 1:
						SetLed(i,red%10);
						delay_ms(3);
						break;
					case 6:
						SetLed(i,green/10);
						delay_ms(3);
						break;
					case 7:
						SetLed(i,green%10);
						delay_ms(3);
						break;
					default:
						break;
				}
			}
			
		}
	}
	red++;
	green--;

}

void SignalV(){
	uchar i,k;
	LED_SEL=0;
	
	for(k=0;k<200;k++){
		if(k%2 == 0){
			LED_SEL = 1;
			GPIOE->ODR &= ~(0xff<<8);
			GPIOE->ODR |= (0xf3<<8);
			delay_ms(3);
		}
		else{
			LED_SEL=0;
			for(i=0;i<8;i++){
				switch(i){
					case 1:
						SetLed(i,green/10);
						delay_ms(3);
						break;
					case 2:
						SetLed(i,green%10);
						delay_ms(3);
						break;
					case 5:
						SetLed(i,red/10);
						delay_ms(3);
						break;
					case 6:
						SetLed(i,red%10);
						delay_ms(3);
						break;
					default:
						break;
				}
			}
			
		}
	}
	red++;
	green--;

}




int main(void)
{			
 	Stm32_Clock_Init(6); //系统时钟设置
	delay_init(72);	     //延时初始化
	LED_Init();		  	 //初始化与LED连接的硬件接口
	EXTIX_Init();		 //外部中断初始化
	
	while(1)
	{	    
		if(state==0){
			Signal();  
			if(green==0){
				delay_ms(300);
				green=5;
				red=0;
				state=1;
			}
		}else{
			SignalV();
			if(green==0){
				delay_ms(300);
				green=5;
				red=0;
				state=0;
			}
		}
	}	 
}

























