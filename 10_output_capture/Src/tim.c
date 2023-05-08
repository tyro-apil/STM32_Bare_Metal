#include <stm32f4xx.h>

#define TIM2EN			(1U<<0)
#define CR1_EN 			(1U<<0)

#define OC_TOGGLE		((1U<<4) | (1U<<5))
#define OC_EN			(1U<<0)

#define GPIOAEN				(1U<<0)
#define AFRL5_TIM2			(1U<<20)

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
	TIM2->CR1 |= CR1_EN;
}

void tim2_pa5_output_compare(void)
{
	/*****Configure PA5 to tim2_channel_1 alternate function******/
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<0);

	GPIOA->AFR[0] |= AFRL5_TIM2;


	/***********Configure timer2 module***********/

	/*Enable clock access to APB1*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler*/
	TIM2->PSC = 1600 - 1; // 16 000 000 / 1 600 = 10 000

	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1; // 10 000/ 10 000 = 1

	/*Set to output compare mode in CCMR1 to toggle mode*/
	TIM2->CCMR1 |= OC_TOGGLE;

	/*Enable output mode through CCER*/
	TIM2->CCER |= OC_EN;

	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 |= CR1_EN;
}
