 /**
 ******************************************************************************
 * Name:    userinterface.c
 * Description: CLI functions Implementation
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


#include"userinterface.h"


/**
* Name:           void writeToCLI(const char data[])
* Paramaters:     none
* Description:    This function writes to the Terminal
* Preconditions:  N/A
* Postconditions: Outputs characters to the CLI
*/
void writeToCLI(const char data[])
{
int i;
	for (i=0; i < strlen(data); i++){
		usart_tx(data[i]);
	}

}



/**
* Name:           void getCommand(char command[])
* Paramaters:     none
* Description:    This function gets user input from terminal
* Preconditions:  N/A
* Postconditions: reads input into a character array
*/
char getCommand(void)
{
	return GLOBAL_USART_Received_Data;
}



