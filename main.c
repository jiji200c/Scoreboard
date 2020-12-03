#include"stm32f10x_gpio.h"
#include"stm32f10x_i2c.h"
#include"stm32f10x_rcc.h"
#include"stm32f10x_ina219.h"
#include"lcd.h"
#include"extio.h"
#include"pwm.h"
#include"seg.h"
#include"stdio.h"
#include"serial.h"
#include"userinterface.h"


bool GLOBAL_CHAR_ENTERED =false;
char GLOBAL_USART_Received_Data;
double CAPACITY_LEFT;



uint16_t home_Score = 0;
uint16_t away_Score = 0;
uint16_t innings = 0;

void commandMenu(void);
void bsm_Init(void);
void battery_cap(void);

int main(){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_Init(GPIOC , &GPIO_InitStructure);
	
	char command;
	
	SystemInit();
	init_DCBA_io();
	PWM_Init();
	init_lcd();
	ina219_init();
	EXTIO_Init();
	usart_init();
	
	bsm_Init();
	commandMenu();
	writeToCLI("COM0>");
	
	while(1)
	{
			bsm_Init();
			battery_cap();
			
			if(GLOBAL_CHAR_ENTERED == true)
			{	
			command = getCommand();
			if (command =='h' || command =='H') 
			{ 
			change_Home('+');
			GPIOC->ODR ^= GPIO_ODR_ODR9;
			}
			else if (command =='j' || command =='J') 
			{ 
			change_Home('-');
			GPIOC->ODR ^= GPIO_ODR_ODR9;
			}
			else if (command =='a' || command =='A') 
			{ 
			change_Away('+');
			GPIOC->ODR ^= GPIO_ODR_ODR9;
			}
			else if (command =='s' || command =='S') 
			{ 
			change_Away('-');
			GPIOC->ODR ^= GPIO_ODR_ODR9;
			}
			else if (command =='r' || command =='R') 
			{ 
			reset_All();
			GPIOC->ODR ^= GPIO_ODR_ODR9;
			
			}
			else if (command =='i' || command =='I') 
			{ 
			change_Innings('+');
			GPIOC->ODR ^= GPIO_ODR_ODR9;
			}
			else if (command =='o' || command =='O') 
			{ 
			change_Innings('-');
			GPIOC->ODR ^= GPIO_ODR_ODR9;
			}
			else if (command =='?') 
			{ 
			writeToCLI("\n\r");
			commandMenu();
			writeToCLI("COM0>");
			GPIOC->ODR ^= GPIO_ODR_ODR9;
			}
			else
			{
				writeToCLI("\n\r");
				writeToCLI("Invalid Command!");
				writeToCLI("\n\r");
				writeToCLI("COM0>");
			}
			GLOBAL_CHAR_ENTERED = false;
		
			}
	}
	
}	

void commandMenu(void)
{
	
	writeToCLI("MAJOR LEAGUE BASEBALL");
	writeToCLI("\n\r");
	writeToCLI("Enter r to reset scoreboard");
	writeToCLI("\n\r");
	writeToCLI("Enter h to increase home team score");
	writeToCLI("\n\r");
	writeToCLI("Enter j to decrease home team score");
	writeToCLI("\n\r");
	writeToCLI("Enter a to increase away team score");
	writeToCLI("\n\r");
	writeToCLI("Enter s to decrease away team score");
	writeToCLI("\n\r");
	writeToCLI("Enter i to increase innings");
	writeToCLI("\n\r");
	writeToCLI("Enter o to decrease innings");
	writeToCLI("\n\r");
	writeToCLI("Enter ? for command menu");
	writeToCLI("\n\r");
	
}

void bsm_Init(void)
{
	volatile double voltage = ina219_getBusVoltage_V();
	
	if (voltage >= 8000)
	{
		CAPACITY_LEFT = TOTAL_CAPACITY;
	}
	else if ((voltage > 7920) && ( voltage < 8000))
	{
		CAPACITY_LEFT = 2574;
	}
	else if ((voltage > 7820) && ( voltage < 7920))
	{
		CAPACITY_LEFT = 2548;
	}
	else if ((voltage > 6500) && ( voltage < 7820))
	{
		CAPACITY_LEFT = (voltage-6451.8)/0.5358;
	}
	else if ((voltage > 6492) && ( voltage < 6500))
	{
		CAPACITY_LEFT = 104;
	}
	else if ((voltage > 6432) && ( voltage < 6492))
	{
		CAPACITY_LEFT = 78;
	}
	else if ((voltage > 6332) && ( voltage < 6432))
	{
		CAPACITY_LEFT = 52;
	}
	else if ((voltage > 6216) && ( voltage < 6332))
	{
		CAPACITY_LEFT = 26;
	}
	else
	{
		CAPACITY_LEFT = 0;
	}
}

void battery_cap(void)
{
	commandto_lcd(LCD_LN1);
	display_CAP(CAPACITY_LEFT/TOTAL_CAPACITY);
	//display_mA(ina219_getCurrent_mA());
	commandto_lcd(LCD_LN2);
	
	if (CAPACITY_LEFT <= 260)
		{
			PWM_Mod(50);
			display_warning();
		}
		else
		{
			PWM_Mod(0);
		}
		
		delay(120000);
		
	
}
