#include "Driver.h"

Relay Rly;

void Relay_While()
{
	Rly.While_Inc += 1;

	Relay_Time_Calculate();
	Relay_Possible_Scenario();

	Relay1_Control();
	Relay2_Control();
}


void Relay_Time_Calculate()
{
	Time.Get = (Time.hour * 100) + Time.min ;

	Rly.ON1 = (((EE.Rly_R1[0]-0x30)*1000) + ((EE.Rly_R1[1]-0x30)*100) +
			((EE.Rly_R1[3]-0x30)*10) + (EE.Rly_R1[4]-0x30));

	Rly.OFF1 = (((EE.Rly_R1[6]-0x30)*1000) + ((EE.Rly_R1[7]-0x30)*100) +
			((EE.Rly_R1[9]-0x30)*10) + (EE.Rly_R1[10]-0x30));

	Rly.ON2 = (((EE.Rly_R2[0]-0x30)*1000) + ((EE.Rly_R2[1]-0x30)*100) +
			((EE.Rly_R2[3]-0x30)*10) + (EE.Rly_R2[4]-0x30));

	Rly.OFF2 = (((EE.Rly_R2[6]-0x30)*1000) + ((EE.Rly_R2[7]-0x30)*100) +
			((EE.Rly_R2[9]-0x30)*10) + (EE.Rly_R2[10]-0x30));
}


void Relay_Possible_Scenario()
{
	if( Rly.ON1 < Rly.OFF1)
		Rly.Scenario1 = 0;		//Evening
	else
		Rly.Scenario1 = 1;		//Whole Night


	if( Rly.ON2 < Rly.OFF2)
		Rly.Scenario2 = 0;		//Evening
	else
		Rly.Scenario2 = 1;		//Whole Night
}


void Relay1_Control()
{
	if(Rly.Scenario1)		//Whole Night
		{
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))		//Relay is OFF
				{
					if(Time.Get >= Rly.ON1)
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	//Turn ON the Relay
				}
			else										//Relay is ON
				{
					if((Time.Get >= Rly.OFF1) && (Time.Get <= 1200))		//Before Afternoon
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	//Turn OFF the Relay
				}
		}
	else					//Evening
		{
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))		//Relay is OFF
				{
					if((Time.Get >= Rly.ON1) && (Time.Get < Rly.OFF1))
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);	//Turn ON the Relay
				}
			else										//Relay is ON
				{
					if(Time.Get >= Rly.OFF1)
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	//Turn OFF the Relay
				}
		}
}

void Relay2_Control()
{
	if(Rly.Scenario2)		//Whole Night
		{
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))		//Relay is OFF
				{
					if(Time.Get >= Rly.ON2)
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);	//Turn ON the Relay
				}
			else										//Relay is ON
				{
					if((Time.Get >= Rly.OFF2) && (Time.Get <= 1200))		//Before Afternoon
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);	//Turn OFF the Relay
				}
		}
	else					//Evening
		{
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))		//Relay is OFF
				{
					if((Time.Get >= Rly.ON2) && (Time.Get < Rly.OFF2))
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);	//Turn ON the Relay
				}
			else										//Relay is ON
				{
					if(Time.Get >= Rly.OFF2)
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);	//Turn OFF the Relay
				}
		}
}
