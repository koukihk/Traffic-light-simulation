/****************��ʱ��ʵ��********************
* 
* ���ߣ�������
***************************************************/

#include "timer.h"

//�����ӵ�ʱ���֡���
extern u8 red,green;
u8 time=0;

/****************��ͨ������ʼ������********************
* ͨ�ö�ʱ���жϳ�ʼ��
* ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
* arr���Զ���װֵ��
* psc��ʱ��Ԥ��Ƶ��
* ����ʹ�õ��Ƕ�ʱ��3!
******************************************************/
void TimerxInit(u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1<<1; //TIM3ʱ��ʹ��
	TIM3->ARR = arr; //�趨�������Զ���װֵ��10Ϊ1ms
	TIM3->PSC = psc; //Ԥ��Ƶ��7200���õ�10KHZ�ļ���ʱ��
	
	TIM3->DIER |= 1<<0; //��������ж�
	TIM3->CR1 |= 0x01; //ʹ�ܶ�ʱ��3
	
	MY_NVIC_Init(1, 3, TIM3_IRQChannel, 2); //��ռ1�������ȼ�3����2
}

/****************��ʱ��3���жϺ���********************
* ��ʱ��3���жϺ���
* ÿ���жϣ�second��һ
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
	
	TIM3->SR &= ~(1<<0); //����жϱ�־λ
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