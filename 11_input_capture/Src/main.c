#include <stm32f4xx.h>
#include <stdio.h>
#include "uart.h"
#include "tim.h"

int capture_value;

int main(void)
{

	tim2_pa5_output_compare();
	tim5_ch1_input_capture();

	while(1)
	{
		/*wait for input capture flag : Bit 1*/
		while(!(TIM5->SR & SR_CC1IF)){}

		/*read input capture data from CCR1 register*/
		capture_value = TIM5->CCR1;
	}
}
