#include <stm32f4xx.h>

#define TIM2EN			(1U<<0)
#define CR1_EN 			(1U<<0)

#define OC_TOGGLE		((1U<<4) | (1U<<5))
#define OC_EN			(1U<<0)

void tim2_1hz_init(void)
{
	/*Enable clock access to APB1*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler*/
	TIM2->PSC = 1600 - 1; // 16 000 000 / 1 600 = 10 000

	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1; // 10 000/ 10 000 = 1

	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 |= OC_EN;
}

