/*
 * buzzerDriver.c
 *
 *  Created on: Feb 22, 2019
 *      Author: lukasz
 */
#include "main.h"
#include "buzzerDriver.h"
#define CPU_FREQ	72000000
#define PRESCALER 	72

/*
 * Buzzer driver init
 */
inline void buzzerDriverInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//__HAL_RCC_GPIOA_CLK_ENABLE();
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC ->APB1ENR |= RCC_APB1ENR_TIM2EN;

	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//Base Timer configuration:
	TIM2 -> CR1 &= ~(TIM_CR1_CKD_0 | TIM_CR1_CKD_1 | TIM_CR1_DIR);	// TIME x1 and DIR UP
	TIM2 -> CR1 |= TIM_CR1_ARPE;									// Auto reload
	TIM2 -> PSC = PRESCALER - 1;									// Prescaler
	TIM2 ->ARR = 60000;												// Period

	//Pulse
	TIM2 -> CCER &= ~TIM_CCER_CC4E;
	TIM2 -> CCER |= TIM_CCER_CC4P;

	TIM2 -> CCMR2 &= ~TIM_CR2_OIS4;
	TIM2 -> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;

	//Set pulse
	TIM2 -> CCR4 = 60000/2;
}

/*
 * 	Set new frequency
 *
 * 	args:
 * 	newFreq - new frequency in Hz.
 */
void buzzerSetNewFrequency(uint32_t newFreq)
{
	uint64_t tempFreq = newFreq;
	if(newFreq == 0) tempFreq = 1;

	uint64_t tempNewValue = (uint64_t) CPU_FREQ / PRESCALER / tempFreq;

	// setting new value
	TIM2 ->ARR = (uint32_t)tempNewValue;
	TIM2 -> CCR4 = (uint32_t)tempNewValue/2;

}
