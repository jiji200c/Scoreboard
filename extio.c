  /******************************************************************************
 * Name:    extio.c
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

#include"extio.h"

/*******************************************************************************
* Function Name		:	EXTIO_Init
* Description		:	Initialize EXTIO
* Input				:	None
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/
void EXTIO_Init(void)
{
	 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN ;       //turn on clock
	 AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;  //select PA
	 EXTI->IMR |= EXTI_IMR_MR0;                 //unmask PA0
   EXTI->FTSR |= EXTI_FTSR_TR0;               //select falling edge of PA0 as trigger
	 NVIC->ISER[0] |= NVIC_ISER_SETENA_6;       //Unmask EXTIO as interrupt source in the NVIC
}

/*******************************************************************************
* Function Name		:	EXTI0_IRQHandler
* Description		:	Interrupt handler for EXTIO
* Input				:	None
* Output			:	Reduces CAPACITY_LEFT by 0.1707mAh for each interrupt
* Return			:	None
* Attention			:	None
*******************************************************************************/
void EXTI0_IRQHandler(void){
  EXTI -> PR |= EXTI_PR_PR0;									// 
	
	if (CAPACITY_LEFT > 0)	
	{
		CAPACITY_LEFT -= 0.1707;     								//Every INT signal subtract 0.1707mAh  from remaining capacity
	}
  GPIOC->ODR ^= GPIO_ODR_ODR9; 								//toggle pc9

}
