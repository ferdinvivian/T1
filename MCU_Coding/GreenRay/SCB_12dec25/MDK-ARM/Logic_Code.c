#include "SCB_Header.h"

Greenray_SCRUBBER_CONTROL_UNIT_LOGIC_STRUCTURE SCBL;

void Sys_Entire_Logic(void)
	{
		if(DBG.Status_A1)					//Master Switch Enable
			{
				On_Off_Time_Calculate();
			}
		else											//Master Switch Disable
			{
				SCBL.Motor_On_Time = SCBL.Motor_Off_Time = 0;
				SCBL.Timing_Mode = SCBL.On_Off_Time_Remaining_Mode = 0;
				SCBL.Sys_On_Time_Total = SCBL.Sys_Off_Time_Total = 0;
				SCBL.Sys_Remaining_On_Time = SCBL.Sys_Remaining_Off_Time = 0;
				
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
				Remaining_Time_Min_Sec();
			}
	}


void On_Off_Time_Calculate(void)
	{
			if(DBG.Status_A6)			//Timing POT/Switch Enable
				{
					ADC_Timing_Calc();
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
					if(SCBL.Timing_Mode == 0)
						{
							SCBL.Timing_Mode = 1;
							SCBL.On_Off_Time_Remaining_Mode = 3;
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
						}
				}
			else									//Timing POT/Switch Disable
				{
					if(SCBL.Timing_Mode == 1)
							SCBL.Timing_Mode = 2;	//disabled after enabling

					if(SCBL.Timing_Mode == 2)
							Calc_Remaining_Time();
				}
	}	
	
void ADC_Timing_Calc(void)
	{
		if(DBG.ADC0_final < 128)
			SCBL.Motor_On_Time = 0;
		else if(DBG.ADC0_final > 3968)
			SCBL.Motor_On_Time = 240;
		else
			SCBL.Motor_On_Time = (DBG.ADC0_final-128)/16;
		
		//ADC0->PA4->ON & ADC1->PA5->OFF
		
		if(DBG.ADC1_final < 128)
			SCBL.Motor_Off_Time = 0;
		else if(DBG.ADC1_final > 3968)
			SCBL.Motor_Off_Time = 240;
		else
			SCBL.Motor_Off_Time = (DBG.ADC1_final-128)/16;
		
			SCBL.Sys_On_Time_Total =(SCBL.Motor_On_Time*60*1000);
			SCBL.Sys_Off_Time_Total =(SCBL.Motor_Off_Time*60*1000);
		
			SCBL.Sys_Remaining_On_Time = SCBL.Sys_On_Time_Total;
			SCBL.Sys_Remaining_Off_Time = SCBL.Sys_Off_Time_Total;
		
			/* Next 2 lines is only for Debugging */
			//SCBL.Sys_Remaining_On_Time = SCBL.Sys_On_Time_Total = 10000;
			//SCBL.Sys_Remaining_Off_Time = SCBL.Sys_Off_Time_Total = 180000;
		
			Remaining_Time_Min_Sec();
	}
	
	
void Calc_Remaining_Time(void)
	{
		if(SCBL.On_Off_Time_Remaining_Mode == 1)
			{
				SCBL.Sys_Remaining_On_Time --;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);

				if(SCBL.Sys_Remaining_On_Time < SYS_TIME_LEFT)
					SCBL.On_Off_Time_Remaining_Mode = 2;
			}
		else if(SCBL.On_Off_Time_Remaining_Mode == 2)
			{
				SCBL.Sys_Remaining_Off_Time --;
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
				
				if(SCBL.Sys_Remaining_Off_Time < SYS_TIME_LEFT)
					SCBL.On_Off_Time_Remaining_Mode = 3;
			}
		else if(SCBL.On_Off_Time_Remaining_Mode == 3)
			{
				SCBL.Sys_Remaining_On_Time = SCBL.Sys_On_Time_Total;
				SCBL.Sys_Remaining_Off_Time = SCBL.Sys_Off_Time_Total;
				
				SCBL.On_Off_Time_Remaining_Mode = 1;
			}
		Remaining_Time_Min_Sec();
	}


void Remaining_Time_Min_Sec(void)
	{
		Disp.On_Min = (SCBL.Sys_Remaining_On_Time/60000);
		Disp.On_Sec = (SCBL.Sys_Remaining_On_Time/1000);
		
		Disp.Off_Min = (SCBL.Sys_Remaining_Off_Time/60000);
		Disp.Off_Sec = (SCBL.Sys_Remaining_Off_Time/1000);
	}