#include <stm32f4xx.h>
#include <stdint.h>
#include <stdio.h>

#define GPIOAEN				(1U<<0)
#define USART2EN			(1U<<17)

#define SYS_CLK				16000000
#define APB1_CLK			SYS_CLK
#define BAUD_RATE			115200

#define USART_TE			(1U<<3)
#define USART_EN 			(1U<<13)

#define USART_TXE			(1U<<7)


static void usart_set_baud_rate(USART_TypeDef* USARTx, uint32_t periph_clk, uint32_t baudrate);
uint16_t calculate_usart_bd(uint32_t periph_clk, uint32_t baudrate);
void usart_write(int ch);
void usart2_init(void);

/*To enable use of printf; __io_putchar in syscalls.c*/
int __io_putchar(int ch)
{
	usart_write(ch);
	return ch;
}

int main(void)
{

	usart2_init();

	while(1)
	{
		printf("Hello, I am apil from stm32\n\r");
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


	/***********Configure USART2 module**********/
	/*clock access enable(APB1 bus)*/
	RCC->APB1ENR |= USART2EN;

	/*Configure Baud Rate(Store in baud rate register(BRR) of USART_Typedef*/
	usart_set_baud_rate(USART2, APB1_CLK, BAUD_RATE);

	/*Enable USART_TX*/
	USART2->CR1 = USART_TE; //why not bitwise OR?? - Set all bits except TE to 0

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

void usart_write(int ch)
{
	/*Make sure transmit data register is empty*/
	while(!(USART2->SR & USART_TXE)){}

	/*Write data*/
	USART2->DR = (ch & 0XFF);
}
