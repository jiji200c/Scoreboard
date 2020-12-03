  /******************************************************************************
 * Name:    extio.h
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

#include"stm32f10x.h"


#define TOTAL_CAPACITY (2600) //2600mAh battery capacity 

extern double CAPACITY_LEFT;

void EXTIO_Init(void);
void EXTIO_IRQHandler(void);
