#define GPIOAEN				(1U<<0)
#define PIN					(1U<<5)
#define LED_PIN				PIN



#include <stdint.h>
#include <stm32f4xx.h>

#include <stdio.h>
#include "uart.h"

char received;

/*******Testing UART receiver*******/

int main(void)
{
	/*initialise USART2 tx/rx*/
	usart2_rxtx_init();


	/*Enable clock access to port A; user led2 = PA5*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set pin 5 to output mode*/
	GPIOA->MODER |= 1U<<10;
	GPIOA->MODER &= ~(1U<<11);

	while(1)
	{
		received = usart_read();

		if(received == '1')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else
		{
			GPIOA->ODR &= ~LED_PIN;
		}
	}
}

