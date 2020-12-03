/**
 ******************************************************************************
 * Name:    serial.c
 * Description: USART interface Configuration Implementation
 * Version: V1.0
 *  Author: Chijoke Jiji
  
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.0 Initial Version by Chijoke Jiji
 *            
 *         
 *****************************************************************************
 */

#include"serial.h"
#include"stm32f10x_rcc.h"

/**
* Name:           void usart_init()
* Paramaters:     none
* Description:    This function configures USART2
* Preconditions:  stm32f10x.h is included in project
* Postconditions: 
*/

void usart_init()
{
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	RCC->APB2ENR |=RCC_APB2ENR_IOPBEN|RCC_APB2ENR_AFIOEN;

	GPIOB->CRH|=	GPIO_CRH_MODE10|GPIO_CRH_CNF10_1|GPIO_CRH_CNF11_0;
	GPIOB->CRH &=	~GPIO_CRH_CNF10_0 & ~GPIO_CRH_MODE11;	

	USART3->CR1 |= USART_CR1_UE;
	USART3->BRR =((unsigned int)(48000000/(16*9600)))  << 3;
	USART3->CR1|=USART_CR1_TE |USART_CR1_RE| USART_CR1_RXNEIE;
	USART3->CR1 &= ~USART_CR1_OVER8 & ~USART_CR1_M & ~USART_CR1_PCE;
	USART3->CR2 &= ~USART_CR2_STOP;	
	NVIC->ISER[1] |= NVIC_ISER_SETENA_7;	
}

/**
* Name:           void usart_tx(uint16_t data)
* Paramaters:     none
* Description:    This function writes to serial interface
* Preconditions:  stm32f10x.h is included in project
* Postconditions: 
*/
void usart_tx(uint16_t data)
{
	while((USART3->SR & USART_SR_TXE)!= USART_SR_TXE)       //Wait for the TxE bit in USART2_SR to be 1
  { };
  USART3->DR = data;
	
}

/**
* Name:           uint16_t usart_rx()
* Paramaters:     none
* Description:    This function reads from serial interface
* Preconditions:  stm32f10x.h is included in project
* Postconditions: 
*/
uint16_t usart_rx()
{  while ((USART3->SR & USART_SR_RXNE)!=USART_SR_RXNE)
	{};
return USART3->DR;	
}

void USART3_IRQHandler()
{
	
	if (USART3->DR != 0xd)
	{
   GLOBAL_USART_Received_Data = USART3->DR;
	 GLOBAL_CHAR_ENTERED = true; 
	}
	
}

