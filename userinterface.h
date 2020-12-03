		
 /**
 ******************************************************************************
 * Name:    userinterfacr.h
 * Description: CLI functions and initialization
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
#include"string.h"

extern bool GLOBAL_CHAR_ENTERED;
extern char GLOBAL_USART_Received_Data;


void writeToCLI(const char data[]);
char getCommand(void);


