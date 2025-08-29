#include "SCB_Header.h"

Greenray_SCB_STRUCTURE 				GSCB;

void Init_Code(void)
	{
		HAL_ADC_Start_DMA(&hadc1 , (uint32_t *)GADC.ADC_Arr , 4);
		HAL_IWDG_Refresh(&hiwdg);
		SSD1306_Init_Code();
	
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		GSCB.Tim2_IT_Inc = 0;
		HAL_TIM_Base_Start_IT(&htim2);
	}
	
void While_Code(void)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(50);
		
		GSCB.While_Inc+=1;
		HAL_IWDG_Refresh(&hiwdg);
		Display_Timing();
	}

void Systick_Code(void)
	{
		GSCB.Sys_Inc+=1;
		GSCB.SysADC_Inc+=1;
		GSCB.SysSSD_Inc+=1;
		
		GSCB.Tim2_Val = __HAL_TIM_GET_COUNTER(&htim2);
		ADC_Function();
	}
	
	
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
			if(htim->Instance==TIM2)
				{
					GSCB.Tim2_Val = __HAL_TIM_GET_COUNTER(&htim2);
					__HAL_TIM_SET_COUNTER(&htim2, 0);
					HAL_TIM_Base_Start_IT(&htim2);
					GSCB.Tim2_IT_Inc+=1;
				}
	}
	
	
