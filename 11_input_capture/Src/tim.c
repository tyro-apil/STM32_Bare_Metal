#include <stm32f4xx.h>

#define TIM2EN			(1U<<0)
#define TIM5EN			(1U<<3)

#define CR1_EN 			(1U<<0)

#define OC_TOGGLE		((1U<<4) | (1U<<5))
#define OC_EN			(1U<<0)
#define CC1S_IC			(1U<<0)
#define CC1E_CAPTURE_EN	(1U<<0)
#define CAPTURE_RISE_EDGE	(1U<<1)

#define GPIOAEN				(1U<<0)
#define AFRL0_TIM5			(1U<<1)

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


void tim5_ch1_input_capture(void)
{
	/***********Configure PA0 to alternate function type***********/
	/*Enable clock access to port A: AHB1 bus : Bit 0 = 1*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set MODER to alternate function mode: bit [1:0] = 10*/
	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER |= (1U<<1);

	/*Set AFR low register pin 0 to AF02: bit[3:0] = 0010*/
	GPIOA->AFR[0] |= AFRL0_TIM5;


	/***********Configure tim5_ch1************/
	/*Enable clock access to APB1: TIM5 : Bit 3*/
	RCC->APB1ENR |= TIM5EN;

	/*Set pre-scaler : 16000*/
	TIM5->PSC = 16000 - 1; //16 000 000 / 16000

	/*Set capture/compare mode register to input capture : Bits 1:0 = 01*/
	TIM5->CCMR1 |= CC1S_IC;

	/*Enable capture at every edge: CC enable register: Bit 0 = 1*/
	TIM5->CCER |= CC1E_CAPTURE_EN;

	/*Enable capture as rising edge: CCER Bit 1 (Output Polarity) Bit 1 = 0 (Reset value)*/
	TIM5->CCER &= ~(CAPTURE_RISE_EDGE);

	/*Enable TIM5: Control register 1 : Bit 0 = 1*/
	TIM5->CR1 |= CR1_EN;
}




















