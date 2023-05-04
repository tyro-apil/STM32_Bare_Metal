//Where is LED connected?
//Port:  A
//Pin:   5
//From Nucleo-64 board user guide stm32f411RE

//address of modules
#define PERIPH_BASE				(0x40000000UL)

#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

//RCC : TO ENABLE CLOCK
#define RCC_OFFSET 				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

//registers
#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET 			(0X0000UL)
#define GPIOA_MODE_R			(*(volatile unsigned *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET 			(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned *)(GPIOA_BASE + OD_R_OFFSET))

#define PIN 					(1U<<5)
#define LED_PIN					 PIN


#define GPIOAEN					(1U<<0) //0b 0000 0000 0000 0000 0000 0000 0000 0001

/*
 * (1U<<10) //SET BIT 10 TO 1
 * &= ~(1U<<11) //SET BIT 11 TO 0
 *
 * */


int main(void)
{
	/*1. Enable clock access to GPIOA*/
	RCC_AHB1EN_R |= GPIOAEN;

	/*2. Set PA5 as output*/
	GPIOA_MODE_R |= (1U<<10); //SET BIT 10 TO 1
	GPIOA_MODE_R &= ~(1U<<11); //SET BIT 11 TO 0

	while(1)
	{
		/*3. Set PA5 as high*/
		GPIOA_OD_R |= LED_PIN;

		/*4. Experiment : Toggle*/
		GPIOA_OD_R ^= LED_PIN;
		for(int i=0; i<1000000; i++);
	}
}


