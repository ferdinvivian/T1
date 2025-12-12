#include "SCB_Header.h"

Greenray_SYSTICK_STRUCTURE 		Sys;
Greenray_DEBUG_STRUCTURE 			DBG;
extern Greenray_ADC_STRUCTURE	GADC;

void Init_Code(void)
	{
		SSD1306_Init_Code();
	}

void While_Code(void)
	{
			Sys.While_Inc+=1;
			HAL_IWDG_Refresh(&hiwdg);
		
			Display_Continuous();
			//Display_Debug_Purpose();
	}

void Systick_Code(void)
	{
		SysInc_Funct();
		SysADC_Function();
		SysGPIO_Check_Status();
		Sys_Entire_Logic();
	}


void SysInc_Funct(void)
	{
		Sys.systick_Inc+=1;
		Sys.Adc_Inc+=1;
		Sys.LED_C13_Inc+=1;
		
		Sys.OnTime_SysInc+=1;
		Sys.OffTime_SysInc+=1;
		Sys.Display_Refresh+=1;
		Sys.Disp_on_off+=1;
	}


void SysGPIO_Check_Status(void)
	{
		DBG.Status_A1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
		DBG.Status_A2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
		DBG.Status_A10 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
		DBG.Status_C13 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	
		
		if(DBG.Status_A2)	//Motor is ON Indication LED C13
			{
				if(Sys.LED_C13_Inc >= 50)
					{
						HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
						Sys.LED_C13_Inc = 0;
					}
			}
		else							//Motor is OFF Indication LED C13
			{
				if(Sys.LED_C13_Inc >= 200)
					{
						HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
						Sys.LED_C13_Inc = 0;
					}
			}
			
		if(DBG.ADC2_final > 3000)
			DBG.Status_A6 = 1;
		else if (DBG.ADC2_final < 1000)
			DBG.Status_A6 = 0;
	}
