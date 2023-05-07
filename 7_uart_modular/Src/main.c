
#include <stdint.h>
#include <stm32f4xx.h>

#include <stdio.h>
#include "uart.h"



int main(void)
{

	usart2_init();

	while(1)
	{
		printf("Hello, I am apil from stm32\n\r");
	}
}

