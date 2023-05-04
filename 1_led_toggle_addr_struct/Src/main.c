//Where is LED connected?
//Port:  A
//Pin:   5
//From Nucleo-64 board user guide stm32f411RE

//address of modules
#include <stdint.h>

#define PERIPH_BASE				(0x40000000UL)

#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

//RCC : TO ENABLE CLOCK
#define RCC_OFFSET 				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define PIN 					(1U<<5)
#define LED_PIN					 PIN


#define GPIOAEN					(1U<<0) //0b 0000 0000 0000 0000 0000 0000 0000 0001

/*
 * (1U<<10) //SET BIT 10 TO 1
 * &= ~(1U<<11) //SET BIT 11 TO 0
 *
 * */
#define __IO 					volatile

typedef struct
{
	__IO uint32_t MODER;
	__IO uint32_t DUMMY[4];
	__IO uint32_t ODR;
}GPIO_handler;

typedef struct
{
	__IO uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR;
}RCC_handler;

#define GPIO					((GPIO_handler*)GPIOA_BASE)
#define RCC 					((RCC_handler*)RCC_BASE)

int main(void)
{
	/*1. Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2. Set PA5 as output*/
	GPIO->MODER |= (1U<<10); //SET BIT 10 TO 1
	GPIO->MODER &= ~(1U<<11); //SET BIT 11 TO 0

	while(1)
	{
		/*3. Set PA5 as high*/
		GPIO->ODR |= LED_PIN;

		/*4. Experiment : Toggle*/
		GPIO->ODR ^= LED_PIN;
		for(int i=0; i<1000000; i++);
	}
}


