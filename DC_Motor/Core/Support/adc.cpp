
#include "adc.h"

void AdcInit(){

/*
 * Enable clock for gpioa.0
 * Enable clock for adc
 * PA3,4 as analog input
 * Continuous mode
 * Align right
 * 2 conversion
 *
 */
	RCC->APB2ENR |= (1<<2);
	RCC->APB2ENR |= (1<<9);

	GPIOA->CRL &=~ (0b1111<<12);	// 12 - ADC3
	GPIOA->CRL &=~ (0b1111<<16);	// 16 - ADC4

	ADC1->CR2 &=~ (1<<8);		// disable scan mode
	ADC1->CR2 &=~ (1<<11);		// discontinuous mode

	ADC1->CR1 &=~ (0b1111<<16);		// Regular simultaneous mode only
	ADC1->CR2 &=~ (1<<11);			// Right Alignment
	ADC1->SMPR2 &=~ (0b111<<9);		// ADC3 1.5cycles
	ADC1->SMPR2 &=~ (0b111<<12);	// ADC4 1.5cycles
}

uint16_t AdcGet(uint8_t channel){
	ADC1->SQR3 = (channel<<0);
	ADC1->CR2 |= (1<<0);					// Enable ADC and to start conversion
	while((ADC1->SR)&(1<<1) != 0);			// wait
	return (uint16_t)ADC1->DR;				// read
}
