/**
 ******************************************************************************
 * Name:    serial.h
 * Description: USART interface Configuration Initialization
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
#include"stm32f10x.h"
#include<stdbool.h>



extern bool GLOBAL_CHAR_ENTERED;
extern char GLOBAL_USART_Received_Data;


void usart_init(void);
void usart_tx(uint16_t data);
uint16_t usart_rx(void);


