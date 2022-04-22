/****************定时器实现********************
* 
* 作者：宁晓兰
***************************************************/

#include "timer.h"

//数字钟的时，分、秒
extern u8 red,green;
u8 time=0;

/****************普通按键初始化函数********************
* 通用定时器中断初始化
* 这里时钟选择为APB1的2倍，而APB1为36M
* arr：自动重装值。
* psc：时钟预分频数
* 这里使用的是定时器3!
******************************************************/
void TimerxInit(u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1<<1; //TIM3时钟使能
	TIM3->ARR = arr; //设定计数器自动重装值，10为1ms
	TIM3->PSC = psc; //预分频器7200，得到10KHZ的计数时钟
	
	TIM3->DIER |= 1<<0; //允许更新中断
	TIM3->CR1 |= 0x01; //使能定时器3
	
	MY_NVIC_Init(1, 3, TIM3_IRQChannel, 2); //抢占1，子优先级3，组2
}

/****************定时器3的中断函数********************
* 定时器3的中断函数
* 每次中断，second加一
******************************************************/

void TIM3_IRQHandler( void )
{
	if(TIM3->SR & 0x0001){
		if(red < 99){
			time++;
			red++;
		}
		if(green > 0){
			green--;
		}
	}
	
	TIM3->SR &= ~(1<<0); //清除中断标志位
}

void Decline(){
	u8 i,j,k;
	TimerxInit(9999,7199);
	while(1){
		for(k=0;k<100;k++){
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
							SetLed(i,time/10);
							delay_ms(3);
							break;
						case 1:
							SetLed(i,time%10);
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
	}
}