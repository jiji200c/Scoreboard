  /******************************************************************************
 * Name:    seg.c
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

#include"seg.h"
/*******************************************************************************
* Function Name		:	init_DCBA_io
* Description		:	Initialize GPIO interface for the DCBA inverters
* Input				:	None
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/
void init_DCBA_io(void){
	GPIO_InitTypeDef  GPIOA_InitStructure,  GPIOB_InitStructure, GPIOC_InitStructure;
	GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |  GPIO_Pin_4; 
																
																
	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |  GPIO_Pin_15;
	GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 |  GPIO_Pin_13;
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	GPIO_Init(GPIOA , &GPIOA_InitStructure);
	GPIO_Init(GPIOB , &GPIOB_InitStructure);
	GPIO_Init(GPIOC , &GPIOC_InitStructure);
	reset_All();

}

/*******************************************************************************
* Function Name		:	reset_All
* Description		:	Resets all the 7 segment displays to zero
* Input				:	None
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/
void reset_All(void){
	
	uint16_t a_pins  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3  |  GPIO_Pin_4;
	uint16_t b_pins  = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	
	uint16_t c_pins = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	
	home_Score = 0;
	away_Score = 0;
	innings = 0;
	
	GPIO_ResetBits(GPIOA, a_pins);
	GPIO_ResetBits(GPIOB, b_pins);
	GPIO_ResetBits(GPIOC, c_pins);

}

/*******************************************************************************
* Function Name		:	change_Home
* Description		:	Increases or decreases the home 7seg display
* Input				:	sign ('+' or '-')
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/
void change_Home(char sign){
	if(sign == '+')
	{
	home_Score++;
	}
	else if (sign =='-')
	{
	home_Score--;
	}
	uint16_t out_pins = (home_Score << 12);

	if (home_Score < 10)
	{
		GPIO_SetBits(GPIOB, out_pins);
		GPIO_ResetBits(GPIOB, (~out_pins & 0xF000));
		
	}
	else
	{
		home_Score = 0;
		out_pins = (home_Score << 12);
		GPIO_ResetBits(GPIOB, (~out_pins & 0xF000));
	}

}

/*******************************************************************************
* Function Name		:	change_Away
* Description		:	Increases or decreases the Away 7seg display
* Input				:	sign ('+' or '-')
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/
void change_Away(char sign){
	if (sign == '+')
	{
	away_Score++;
	}
	else if (sign == '-')
	{
	away_Score--;
	}
	uint16_t out_pins = (away_Score << 1);

	if (away_Score < 10)
	{
		GPIO_SetBits(GPIOA, out_pins);
		GPIO_ResetBits(GPIOA, (~out_pins & 0x01E));
		
	}
	else
	{
		away_Score = 0;
		out_pins = (away_Score << 1);
		GPIO_ResetBits(GPIOA, (~out_pins & 0x01E));
	}
	
}

/*******************************************************************************
* Function Name		:	change_Innings
* Description		:	Increases or decreases the Innings 7seg display
* Input				:	sign ('+' or '-')
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/
void change_Innings(char sign){
	if (sign == '+')
	{
	innings++;
	}
	else if (sign == '-')
	{
	 innings--;
	}
	uint16_t out_pins =(innings << 10);

	if (innings < 10)
	{
		GPIO_SetBits(GPIOC, out_pins);
		GPIO_ResetBits(GPIOC, (~out_pins & 0x3C00));
	}
	else
	{
		innings = 0;
		out_pins = innings;
		GPIO_ResetBits(GPIOC, (~out_pins & 0x3C00));
	}
	
}

