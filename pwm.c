  /******************************************************************************
 * Name:    pwm.c
 * Description: STM32 peripherals initialization and functions
 * Version: V1.00
 * Author: Chijoke Jiji 
  some codes from lab1_lib.c written by Dave Duguid / Trevor Douglas
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *          V1.1 reformatted (kjn)
 *****************************************************************************/

#include "pwm.h"
/*******************************************************************************
* Function Name		:	PWM_Init
* Description		:	Initialize timer interface for pwm
* Input				:	None
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/
void PWM_Init()
{

	RCC->APB2ENR |=RCC_APB2ENR_TIM1EN;
	RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;
	GPIOA->CRH &= 0x00;
	GPIOA->CRH |= GPIO_CRH_CNF8_1 |GPIO_CRH_MODE8;

	TIM1->CR1 |= TIM_CR1_CEN ;       						//
	TIM1->CR2 |= TIM_CR2_OIS1;    	 					//
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE ;  //
	TIM1->CCER |= TIM_CCER_CC1E ;     //	
	TIM1->PSC |= 23999;            //divide up by 1KHZ
	TIM1->ARR &= 0;
	TIM1->ARR |= 500;						  //MAX DUTY CYCLE	
	TIM1->EGR |= TIM_EGR_UG;								 	//
	TIM1->BDTR  |= TIM_BDTR_MOE | TIM_BDTR_OSSI;   //
	TIM1->CR1  |= TIM_CR1_ARPE | TIM_CR1_CEN;      //
}

/*******************************************************************************
* Function Name		:	PWM_Mod
* Description		:	modifies the duty cycle
* Input				:	duty circle
* Output			:	the PWM duty circle is changed
* Return			:	None
* Attention			:	None
*******************************************************************************/
void PWM_Mod(uint16_t duty)
{
 
	TIM1->CCR1 |= duty;	  //reaches the CCR1
	TIM1->EGR |= TIM_EGR_UG;
		
}

