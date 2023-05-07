#include <stm32f4xx.h>
#include <stdint.h>

#define GPIOAEN				(1U<<0)
#define USART2EN			(1U<<17)

#define SYS_CLK				16000000
#define BAUD_RATE			115200

#define USART_TE			(1U<<3)
#define USART_EN 			(1U<<13)

void usart2_init(void);
void usart_set_baud_rate(USART_TypeDef* USARTx, uint32_t periph_clk, uint32_t baudrate);
uint16_t calculate_usart_bd(uint32_t periph_clk, uint32_t baudrate);


int main(void)
{


	while(1)
	{

	}
}

void usart2_init(void)
{
	/********Configure GPIOA pin 2 to desired alternate function********/
	/*clock access enable*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Change in MODER to alternate function mode*/
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Alternate Function Type Register (which type of alternate function to operate*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);


	/***********Configure USART2**********/
	/*clock access enable(APB1 bus)*/
	RCC->APB1ENR |= USART2EN;

	/*Configure Baud Rate(Store in baud rate register(BRR) of USART_Typedef*/
	usart_set_baud_rate(USART2, SYS_CLK, BAUD_RATE);

	/*Enable USART_TX*/
	USART2->CR1 = USART_TE;

	/*Enable USART communication*/
	USART2->CR1 |= USART_EN;

}


static void usart_set_baud_rate(USART_TypeDef* USARTx, uint32_t periph_clk, uint32_t baudrate)
{
	USARTx->BRR = calculate_usart_bd(periph_clk, baudrate);
}

uint16_t calculate_usart_bd(uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2U)) / baudrate); //EMPIRICAL FORMULA
}
