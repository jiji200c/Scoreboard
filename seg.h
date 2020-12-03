  /******************************************************************************
 * Name:    seg.h
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

#include"stm32f10x_gpio.h"
#include"stm32f10x_rcc.h"
#include "stm32f10x.h"

extern uint16_t home_Score;
extern uint16_t away_Score;
extern uint16_t innings;

void init_DCBA_io(void);
void reset_All(void);
void change_Home(char sign);
void change_Away(char sign);
void change_Innings(char sign);

