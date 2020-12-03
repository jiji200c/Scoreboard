 
  /******************************************************************************
 * Name:    lcd.c
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
 #include "stm32f10x.h"
 #include "open103z_systick.h"
 #include"lcd.h"

/*******************************************************************************
* Function Name		:	init_lcd
* Description		:	Initialize lcd interface
* Input				:	None
* Output			:	None
* Return			:	None
* Attention			:	None
*******************************************************************************/ 
 void init_lcd(void)
{
		RCC->APB2ENR |=RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
	  //configure output modes
    GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 |GPIO_CRL_MODE5;
    GPIOB->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF5;
	
	  GPIOC->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1| GPIO_CRL_MODE2| GPIO_CRL_MODE3| GPIO_CRL_MODE4 
	                |GPIO_CRL_MODE5| GPIO_CRL_MODE6| GPIO_CRL_MODE7;
    GPIOC->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF2 & ~GPIO_CRL_CNF3 & ~GPIO_CRL_CNF4 
               & ~GPIO_CRL_CNF5 & ~GPIO_CRL_CNF6 & ~GPIO_CRL_CNF7;
	  
	  //initializing lcd
	  commandto_lcd(LCD_8B2L);
	  delay(30000);
	  commandto_lcd(LCD_8B2L);
    delay(8000);	
	  commandto_lcd(LCD_8B2L);
	  commandto_lcd(LCD_8B2L);
	  commandto_lcd(LCD_DCB);
    commandto_lcd(LCD_CLR);
    commandto_lcd(LCD_MCR);  
	
}

/*
* Name: commandToLCD
* Type: PUBLIC
* Parameters: a single byte of command information for the LCD controller
* Returns: nothing
* Description: This function generates control timing and data signals to send one command byte to the LCD
*/
void commandto_lcd(uint8_t command)
{
	GPIOB->BSRR = LCD_CM_ENA;                //RS low, E high
		
	GPIOC->ODR &= 0xFF00;                   //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= command;                   //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	GPIOB->BSRR = LCD_CM_DIS;              //RS low, E low
	delay(80000);
}
 

/*
* Name: dataToLCD
* Type: PUBLIC
* Parameters: a single byte of data information for the LCD controller
* Returns: nothing
* Description: This function generates control timing and data signals to send one data byte to the LCD
*/
void datato_lcd(uint8_t data)
{
	GPIOB->BSRR = LCD_DM_ENA;                //RS low, E high
		
	GPIOC->ODR &= 0xFF00;                   //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data;                   //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	GPIOB->BSRR = LCD_DM_DIS;              //RS low, E low
	delay(80000);
}


/*
* Name: display_mAh
* Type: PUBLIC
* Parameters: battery capacity
* Returns: nothing
* Description: This function displays the battery capacity on the lcd
*/
void display_mAh(uint16_t cap)
{
  uint16_t cap_dec = cap;
	cap_dec = (cap_dec % 10000);
	datato_lcd(0x30 + (cap_dec/1000));
	cap_dec = cap_dec % 1000;
	
	datato_lcd(0x30 + (cap_dec/100));
	
	cap_dec = cap_dec % 100;
	datato_lcd(0x30 + (cap_dec/10));
	
	cap_dec = cap_dec % 10;
	datato_lcd(0x30 + (cap_dec));
	
	datato_lcd('m');
	datato_lcd('A');
	datato_lcd('h');
	datato_lcd(' ');
	datato_lcd(' ');
}


/*
* Name: display_mA
* Type: PUBLIC
* Parameters: current
* Returns: nothing
* Description: This function displays the circuit current on the lcd
*/
void display_mA(uint16_t cap)
{
  uint16_t cap_dec = cap;
	cap_dec = (cap_dec % 10000);
	datato_lcd(0x30 + (cap_dec/1000));
	
	cap_dec = cap_dec % 1000;
	
	datato_lcd(0x30 + (cap_dec/100));
	
	cap_dec = cap_dec % 100;
	datato_lcd(0x30 + (cap_dec/10));
	
	cap_dec = cap_dec % 10;
	datato_lcd(0x30 + (cap_dec));
	
	datato_lcd('m');
	datato_lcd('A');
	datato_lcd(' ');
	datato_lcd(' ');
}

/*
* Name: display_CAP
* Type: PUBLIC
* Parameters: battery capacity
* Returns: nothing
* Description: This function writes the battery capacity as percentage to the lcd
*/
void display_CAP(double cap)
{
	char disp_text[] = "BATTERY: ";
	for(int i = 0; i < 9; i++)
	{
		datato_lcd(disp_text[i]);
	}
	
  uint16_t cap_dec = (uint16_t) (cap *100);
	
	cap_dec = (cap_dec % 10000);
	cap_dec = cap_dec % 1000;
	
	datato_lcd(0x30 + (cap_dec/100));
	
	cap_dec = cap_dec % 100;
	datato_lcd(0x30 + (cap_dec/10));
	
	cap_dec = cap_dec % 10;
	datato_lcd(0x30 + (cap_dec));
	
	datato_lcd('%');
	datato_lcd(' ');
	datato_lcd(' ');
	
}

/*
* Name: display_warning
* Type: PUBLIC
* Parameters: none
* Returns: nothing
* Description: This function writes the low battery warning to the lcd
*/
void display_warning(void)
{
	char disp_text[] = "LOW BATTERY!!!";
	for(int i = 0; i < 14; i++)
	{
		datato_lcd(disp_text[i]);
	}
}

/*
* Name:         void delay()
* Paramaters:   32 bit delay value, ( a value of 6000
                gives approximately 1 mS of delay)
* Description:  This function creates a delay
*/
void delay(uint32_t count)
{
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
}
