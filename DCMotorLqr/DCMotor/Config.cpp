#include "Config.h"

#define GPIOA_ENABLE_CLOCK() {RCC->APB2ENR |= (1<<2);}
#define GPIOC_ENABLE_CLOCK() {RCC->APB2ENR |= (1<<4);}
#define UART_2_ENABLE_CLOCK() {RCC->APB1ENR |= (1<<14);}

#define LED_OFF() {GPIOC->ODR |= (1<<13);}
#define LED_ON() {GPIOC->ODR &=~ (1<<13);}
#define LED_TOGGLE() {GPIOC->ODR ^= (1<<13);}

void debug_init(void){
	// Enable clock GPIOC
	GPIOC_ENABLE_CLOCK();

	GPIOC->CRH &=~ 0x00F00000;
	GPIOC->CRH |= 0x00100000;
}

extern void usart_2_init(void){
	GPIOA_ENABLE_CLOCK();									// gpioa enable clock
	GPIOA->CRL |= (B1010<<8)|(B1000<<12);	// pa9 - pa10 : alternate function mode

	UART_2_ENABLE_CLOCK();

	USART2->CR1 &=~ (1<<12);	// 8 bit
	USART2->CR1 &=~ (1<<9);		// parity none
	USART2->CR1 |= (1<<2); 		// RE=1.. Enable the Receiver
	USART2->CR1 |= (1<<3);  	// TE=1.. Enable Transmitter

	/*
	 * 	Fclk = 72Mhz
	 *	Baudrate : 115200
	 */

	USART2->BRR = 0x02D9;
	USART2->CR1 |= (1<<13);   // UE = 1... Enable USART
}

extern void encoder_init(void){

	RCC->APB2ENR |= (1<<0);  			// Enable AFIO CLOCK
	AFIO->EXTICR[0] &= ~(0xf<<4);  		// Bits[7:6:5:4] = (0:0:0:0)  -> configure EXTI1 line for PA1
	EXTI->IMR |= (1<<1);  				// Bit[1] = 1  --> Disable the Mask on EXTI 1
	EXTI->RTSR &=~ (1<<1);  			// Enable Rising Edge Trigger for PA1
	EXTI->FTSR |= (1<<1);  				// Disable Falling Edge Trigger for PA1
	NVIC_SetPriority (EXTI1_IRQn, 1);  	// Set Priority
	NVIC_EnableIRQ (EXTI1_IRQn);  		// Enable Interrupt

}

void TIM2_IRQHandler(void)
{
	if (TIM2->SR & (1<<0))
	{
	}
}

extern void tim_2_init(void){
	// Enable tim 2
	RCC->APB1ENR |= (1<<0);
	TIM1->CNT = 0;
	TIM1->PSC = 0;
	TIM1->ARR = 3599;
	/*
		NVIC TIM 2 update : 28
		28/4 = 7
		(28-4*7)= 0-> (0)*8 = 8
	*/
	NVIC->IP[7] = (0<<0);
	/*
		NVIC TIM 1 update : enable
		28/31 = 0
		28-31*0= 3
	*/
	NVIC->ISER[0] = (1<<3);
}

void TIM1_IRQHandler(void)
{
	if (TIM1->SR & (1<<0))
	{
		LED_TOGGLE();
	}
}

extern void pwm_1_init(void){
	// Enable clock GPIOA : alternate function
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRH &=~ 0x0000000F;
	GPIOA->CRH |= 0x0000000B;

	// Enable tim 1
	RCC->APB2ENR |= (1<<11);
	TIM1->CNT = 0;
	TIM1->PSC = 0;
	TIM1->ARR = 3599;

	// Center-aligned mode 1
	TIM1->CR1 |= (1<<5);
	// PWM Mode 1 : CHANNEL 1
	TIM1->CCMR1 |= (B110<<4)|(1<<3);

	// Capture/Compare 1 output polarity
	TIM1->CCER |= (1<<0)|(1<<1);

	// Capture/Compare 1 output polarity
	TIM1->DIER |= (1<<0);

	// enable tim 1
	TIM1->BDTR |= (1<<15)|(1<<13);
	TIM1->CR1 |= (1<<0);
	TIM1->CCR1 = 1000;

	/*
		NVIC TIM 1 update : 25
		25/4 = 6
		(25-4*6)= 1-> (1)*8 = 8
	*/
	NVIC->IP[6] = (0<<8);
	/*
		NVIC TIM 1 update : enable
		25/31 = 0
		25-31*0= 25
	*/
	NVIC->ISER[0] = (1<<25);
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
	USART2->DR = (uint32_t)ch;
	while((USART2->SR & (1<<6)) == 0);
	return ch;
}