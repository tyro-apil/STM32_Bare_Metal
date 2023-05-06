#define STM32F411xE

#include <stm32f4xx.h>

#define GPIOAEN				(1U<<0)
#define GPIOCEN				(1U<<2)

#define PIN					(1U<<5)
#define LED_PIN				PIN


int main(void)
{
	/*Enable clock to ports A and C*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	/*Set PA5 as output and PC13 as input*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	while(1)
	{
		/*On button press LED off else LED on*/
		if(GPIOC->IDR &= (1U<<13))
		{
			GPIOA->BSRR |= LED_PIN;
		}
		else
		{
			GPIOA->BSRR &= ~(LED_PIN);
			GPIOA->BSRR |= (1U<<21);
		}
	}
}
