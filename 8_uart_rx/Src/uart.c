#include "uart.h"



#define GPIOAEN				(1U<<0)
#define USART2EN			(1U<<17)

#define SYS_CLK				16000000
#define APB1_CLK			SYS_CLK
#define BAUD_RATE			115200

#define USART_TE			(1U<<3)
#define USART_RE			(1U<<2)

#define USART_EN 			(1U<<13)

#define SR_TXE				(1U<<7)
#define SR_RXNE				(1U<<5)

static void usart_set_baud_rate(USART_TypeDef* USARTx, uint32_t periph_clk, uint32_t baudrate);
uint16_t calculate_usart_bd(uint32_t periph_clk, uint32_t baudrate);
void usart_write(int ch);


/*To enable use of printf; __io_putchar in syscalls.c*/
int __io_putchar(int ch)
{
	usart_write(ch);
	return ch;
}

void usart2_rxtx_init(void)
{
	/********Configure GPIOA pin 2 and pin 3 to desired alternate function********/
	/*clock access enable*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Change in MODER to alternate function mode*/
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*Alternate Function Type Register (which type of alternate function to operate*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);



	/***********Configure USART2 module**********/
	/*clock access enable(APB1 bus) USART2 : */
	RCC->APB1ENR |= USART2EN;

	/*Configure Baud Rate(Store in baud rate register(BRR) of USART_Typedef*/
	usart_set_baud_rate(USART2, APB1_CLK, BAUD_RATE);

	/*Enable USART_TX and USART_RX*/
	USART2->CR1 = USART_TE; //why not bitwise OR?? - Set all bits except TE to 0
	USART2->CR1 |= USART_RE;

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
	while(!(USART2->SR & SR_TXE)){}

	/*Write data*/
	USART2->DR = (ch & 0XFF);
}

char usart_read(void)
{
	/*Make sure receive data register is not empty*/
	while(!(USART2->SR & SR_RXNE)){}

	/*Read data*/
	return USART2->DR;
}
