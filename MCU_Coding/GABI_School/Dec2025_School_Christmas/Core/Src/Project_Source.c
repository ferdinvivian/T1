#include "Proj_Header.h"

GABI_TIMER11_STRUCTURE 	Tim11;
PROJ_SOURCE_STRUCTURE 	prj;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM11)
    {
				tim11_function();
			
			  if(prj.Song_Play_Status)
				{
					STEPPER_MOTOR_ON();
					if((Tim11.Timer_Inc%PC13_DELAY) == 0)
						HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				}
				else
				{
					STEPPER_MOTOR_OFF();
					if((Tim11.Timer_Inc%(PC13_DELAY*4)) == 0)
						HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
				}
				
				if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
					prj.Song_Play_Status = 0;		//Song Not Playing
				else
					prj.Song_Play_Status = 1;		//Song Playing
    }
}

/*********************************************************************/

void init_function()
	{
		prj.Song_Play_Status = 0;
		STEPPER_MOTOR_OFF();
		
		HAL_TIM_Base_Start_IT(&htim11);
		HAL_Delay(1000);		//DF PLAYER START DELAY, Must
		
		DF_Init(DF_VOLUME);
		DF_PlayFromStart();
	}

void while_function()
	{
		GABI_SONG_PLAY();
	}

void tim11_function()
	{
		Tim11.Timer_Inc+=1;
		Tim11.DF_STOP+=1;
		Tim11.DF_REPEAT+=1;
		Tim11.Motor_Inc+=1;
	}



void GABI_SONG_PLAY (void)
{
		if(Tim11.DF_STOP > (DF_STOP_SEC*1000))
			{
					DF_Reset();
					DF_Pause();
					Tim11.DF_STOP = (Tim11.DF_STOP - 5000);
					//To avoid starting again, doing pause and reset
			}
			
		if(Tim11.DF_REPEAT > 38000)
			{
					Tim11.DF_REPEAT = 1000;
					prj.Loop_song+=1;
					
					if(prj.Loop_song < 2)
						DF_PlayFromStart();
			}
}



void STEPPER_MOTOR_ON (void)
{
	if(Tim11.Motor_Inc > STEP_DELAY)
	{
		Tim11.Motor_Inc = 0;
		switch(prj.Motor_Step)
		{
			case 1:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
				prj.Motor_Step = 2;
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
				prj.Motor_Step = 3;
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
				prj.Motor_Step = 4;
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
				prj.Motor_Step = 1;
				break;
			default:
				prj.Motor_Step = 1;
				break;
		}
	}
}


void STEPPER_MOTOR_OFF (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}