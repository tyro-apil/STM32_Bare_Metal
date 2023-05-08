#include <stm32f4xx.h>
#include <stdio.h>
#include "uart.h"
#include "tim.h"

#define GPIOAEN				(1U<<0)
#define PIN					(1U<<5)
#define LED_PIN				PIN

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= 1U<<10;
	GPIOA->MODER &= ~(1U<<11);

	usart2_tx_init();
	tim2_1hz_init();

	while(1)
	{

		/*Wait for update interrupt flag*/
		while(!(TIM2->SR & SR_UIF)){}

		/*Clear update interrupt flag*/
		TIM2->SR &= ~(SR_UIF);

		printf("1 second has passed \n\r");
		GPIOA->ODR ^= LED_PIN;

	}
}
