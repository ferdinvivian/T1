#include "SCB_Header.h"

Greenray_DISPLAY_STRUCTURE Disp;

void SSD1306_Init_Code(void)
	{
		SSD1306_Init();
		
		SSD1306_Clear();
		SSD1306_GotoXY (0, 5);
		SSD1306_Puts ("GASION", &Font_16x26, 1); // Changed from " GREEN " to " GASION "
		SSD1306_GotoXY (0, 32);
		SSD1306_Puts ("AIRTEC", &Font_16x26, 1); // Changed from " RAY " to " AIRTEC"
		SSD1306_UpdateScreen(); //display
		HAL_Delay(1000);
		
		SSD1306_Clear();
		SSD1306_GotoXY (0, 5);
		SSD1306_Puts (" Have a ", &Font_16x26, 1);
		SSD1306_GotoXY (0, 32);
		SSD1306_Puts ("niceday", &Font_16x26, 1);
		SSD1306_UpdateScreen(); //display
		HAL_Delay(1000);
		
		SSD1306_Init();
		SSD1306_Clear();
	}
	
	
void Display_Continuous(void)
	{
		if(Sys.Display_Refresh > 30000)
			{
				SSD1306_Init();
				SSD1306_Clear();
				Sys.Display_Refresh = 0;
				Disp.Page = 0;
			}
		else
			{
				if(DBG.Status_A1)
				{
					if(((Disp.Page == 0)||(Disp.Page == 1)) && (DBG.Status_A1 == 1))
						{
								SSD1306_Init();
								SSD1306_Clear();
								Disp.Page = 2;
						}
					if(Sys.Disp_on_off < DISP_BLINK_TIME)
						{
							Display_Function_on();
						}
					else
						{
								if(Sys.Disp_on_off > (DISP_BLINK_TIME*2))
									Sys.Disp_on_off = 0;
								else
									Display_Function_off();
						}
						
				}
			else
				{
					if(((Disp.Page == 0)||(Disp.Page == 2)) && (DBG.Status_A1 == 0))
						{
								SSD1306_Init();
								SSD1306_Clear();
								Disp.Page = 1;
						}
						
					Display_Page2_Master_Control();
					SSD1306_UpdateScreen(); //display
				}
				
			}
	}
	
	
void Display_Function_on(void)
	{
			char Arr[25];
		
			memset(Arr, 0x00, sizeof(Arr));
			if(Disp.On_Min > MIN_OR_SEC)
				{
					if(Disp.On_Min < 10)
							sprintf((char *)Arr, "On_Time :00%d min", (uint8_t)Disp.On_Min);
					else if((Disp.On_Min  < 100) && (Disp.On_Min  >= 10))
							sprintf((char *)Arr, "On_Time :0%d min", (uint8_t)Disp.On_Min);
					else
							sprintf((char *)Arr, "On_Time :%d min", (uint8_t)Disp.On_Min);
				}
			else
				{
					if(Disp.On_Sec < 10)
							sprintf((char *)Arr, "On_Time :00%d sec", (uint8_t)Disp.On_Sec);
					else if((Disp.On_Sec  < 100) && (Disp.On_Sec  >= 10))
							sprintf((char *)Arr, "On_Time :0%d sec", (uint8_t)Disp.On_Sec);
					else
							sprintf((char *)Arr, "On_Time :%d sec", (uint8_t)Disp.On_Sec);
				}
			SSD1306_GotoXY (5,1);
			SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			
			
			memset(Arr, 0x00, sizeof(Arr));
			if(Disp.Off_Min > MIN_OR_SEC)
				{
					if(Disp.Off_Min < 10)
							sprintf((char *)Arr, "Off_Time:00%d min", (uint8_t)Disp.Off_Min);
					else if((Disp.Off_Min  < 100) && (Disp.Off_Min  >= 10))
							sprintf((char *)Arr, "Off_Time:0%d min", (uint8_t)Disp.Off_Min);
					else
							sprintf((char *)Arr, "Off_Time:%d min", (uint8_t)Disp.Off_Min);
				}
			else
				{
					if(Disp.Off_Sec < 10)
							sprintf((char *)Arr, "Off_Time:00%d sec", (uint8_t)Disp.Off_Sec);
					else if((Disp.Off_Sec  < 100) && (Disp.Off_Sec  >= 10))
							sprintf((char *)Arr, "Off_Time:0%d sec", (uint8_t)Disp.Off_Sec);
					else
							sprintf((char *)Arr, "Off_Time:%d sec", (uint8_t)Disp.Off_Sec);
				}
			SSD1306_GotoXY (5,14);
			SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			
			
			sprintf((char *)Arr, "%s", (char*)&Disp.RPM_Data[0]);
			SSD1306_GotoXY (5,27);
			SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			
			
			memset(Arr, 0x00, sizeof(Arr));
			if(DBG.Status_A2)
				sprintf((char *)Arr, "Motor is ON ");
			else
				sprintf((char *)Arr, "Motor is OFF");
			SSD1306_GotoXY (5,40);
			SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			
			
			if(SCBL.Timing_Mode)
				{
					if(DBG.Status_A6)
					{
						memset(Arr, 0x00, sizeof(Arr));
						sprintf((char *)Arr, "Timing Ctrl EN ");
						SSD1306_GotoXY (5,53);
						SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
					}
					else
					{
						Display_Max_OnOff_Time();
					}
				}
			else
			{
					memset(Arr, 0x00, sizeof(Arr));
					sprintf((char *)Arr, "Time to be Set ");

					SSD1306_GotoXY (5,53);
					SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			}
	
			SSD1306_UpdateScreen(); //display
	}
	


void Display_Function_off(void)
	{
			char Arr[25];
		
			memset(Arr, 0x00, sizeof(Arr));
			if(Disp.On_Min > MIN_OR_SEC)
				{
					if(Disp.On_Min < 10)
							sprintf((char *)Arr, "On_Time  00%d min", (uint8_t)Disp.On_Min);
					else if((Disp.On_Min  < 100) && (Disp.On_Min  >= 10))
							sprintf((char *)Arr, "On_Time  0%d min", (uint8_t)Disp.On_Min);
					else
							sprintf((char *)Arr, "On_Time  %d min", (uint8_t)Disp.On_Min);
				}
			else
				{
					if(Disp.On_Sec < 10)
							sprintf((char *)Arr, "On_Time  00%d sec", (uint8_t)Disp.On_Sec);
					else if((Disp.On_Sec  < 100) && (Disp.On_Sec  >= 10))
							sprintf((char *)Arr, "On_Time  0%d sec", (uint8_t)Disp.On_Sec);
					else
							sprintf((char *)Arr, "On_Time  %d sec", (uint8_t)Disp.On_Sec);
				}
			SSD1306_GotoXY (5,1);
			SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			
			
			memset(Arr, 0x00, sizeof(Arr));
			if(Disp.Off_Min > MIN_OR_SEC)
				{
					if(Disp.Off_Min < 10)
							sprintf((char *)Arr, "Off_Time 00%d min", (uint8_t)Disp.Off_Min);
					else if((Disp.Off_Min  < 100) && (Disp.Off_Min  >= 10))
							sprintf((char *)Arr, "Off_Time 0%d min", (uint8_t)Disp.Off_Min);
					else
							sprintf((char *)Arr, "Off_Time %d min", (uint8_t)Disp.Off_Min);
				}
			else
				{
					if(Disp.Off_Sec < 10)
							sprintf((char *)Arr, "Off_Time 00%d sec", (uint8_t)Disp.Off_Sec);
					else if((Disp.Off_Sec  < 100) && (Disp.Off_Sec  >= 10))
							sprintf((char *)Arr, "Off_Time 0%d sec", (uint8_t)Disp.Off_Sec);
					else
							sprintf((char *)Arr, "Off_Time %d sec", (uint8_t)Disp.Off_Sec);
				}
			SSD1306_GotoXY (5,14);
			SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			
			
			sprintf((char *)Arr, "%s", (char*)&Disp.RPM_Data[0]);
			SSD1306_GotoXY (5,27);
			SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			
			
			memset(Arr, 0x00, sizeof(Arr));
			if(DBG.Status_A2)
				sprintf((char *)Arr, "Motor is ON ");
			else
				sprintf((char *)Arr, "Motor is OFF");
			SSD1306_GotoXY (5,40);
			SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
			
			
			if(SCBL.Timing_Mode)
				{
					if(DBG.Status_A6)
					{
						memset(Arr, 0x00, sizeof(Arr));
						sprintf((char *)Arr, "Timing Ctrl EN ");
						SSD1306_GotoXY (5,53);
						SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
					}
					else
					{
						Display_Max_OnOff_Time();
					}
				}
			else
				{
						memset(Arr, 0x00, sizeof(Arr));
						sprintf((char *)Arr, "               ");

						SSD1306_GotoXY (5,53);
						SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
				}
	
			SSD1306_UpdateScreen(); //display
	}
		
	
	
	
void Display_Page2_Master_Control(void)
	{
		char Arr_Disp[25];

		memset(Arr_Disp, 0x00, sizeof(Arr_Disp));
		sprintf((char *)Arr_Disp, "Master ");

		SSD1306_GotoXY (30,3);
		SSD1306_Puts ((char*)Arr_Disp, &Font_11x18, 1);

		memset(Arr_Disp, 0x00, sizeof(Arr_Disp));
		sprintf((char *)Arr_Disp, "Control");

		SSD1306_GotoXY (20,23);
		SSD1306_Puts ((char*)Arr_Disp, &Font_11x18, 1);

		memset(Arr_Disp, 0x00, sizeof(Arr_Disp));
		sprintf((char *)Arr_Disp, "Disabled");

		SSD1306_GotoXY (15,43);
		SSD1306_Puts ((char*)Arr_Disp, &Font_11x18, 1);
	}
	
	
	
void Display_Max_OnOff_Time(void)
	{
			char Time_Arr[25];
			memset(Time_Arr, 0x00, sizeof(Time_Arr));
		
			uint8_t On_Time_Min = 0 , On_Time_Sec = 0;
			uint8_t Off_Time_Min =0 , Off_Time_Sec= 0;
		
			On_Time_Min = SCBL.Sys_On_Time_Total/60000;
			On_Time_Sec = SCBL.Sys_On_Time_Total/1000;
	
			Off_Time_Min = SCBL.Sys_Off_Time_Total/60000;
			Off_Time_Sec = SCBL.Sys_Off_Time_Total/1000;
		
			if((SCBL.Sys_On_Time_Total <= 120000) && (SCBL.Sys_Off_Time_Total <= 120000))
			{
				sprintf((char *)Time_Arr, "ON:%ds OFF:%ds  ",On_Time_Sec, Off_Time_Sec);
			}
			else if((SCBL.Sys_On_Time_Total <= 120000) && (SCBL.Sys_Off_Time_Total > 120000))
			{
				sprintf((char *)Time_Arr, "ON:%ds OFF:%dm  ",On_Time_Sec, Off_Time_Min);
			}
			else if((SCBL.Sys_On_Time_Total > 120000) && (SCBL.Sys_Off_Time_Total <= 120000))
			{
				sprintf((char *)Time_Arr, "ON:%dm OFF:%ds  ",On_Time_Min, Off_Time_Sec);
			}
			else
			{
				sprintf((char *)Time_Arr, "ON:%dm OFF:%dm  ",On_Time_Min, Off_Time_Min);
			}

		
			SSD1306_GotoXY (5,53);
			SSD1306_Puts ((char*)Time_Arr, &Font_7x10, 1);
	}	

/*******************************************************************************/		
//ONLY FOR DEBUGGING
/*******************************************************************************/	

void Display_Debug_Purpose(void)
	{
			char Arr[25];
			if(Sys.Display_Refresh > 3000)
				{
					SSD1306_Init();
					SSD1306_Clear();
					Sys.Display_Refresh = 0;
				}
			else
				{
					memset(Arr, 0x00, sizeof(Arr));
					if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))
					{
						sprintf((char *)Arr, "PA1_Pin_Read:ON ");
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
						DBG.pin_a1_read = 1;
						DBG.pin_a2_read = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
					}
					else
					{
						sprintf((char *)Arr, "PA1_Pin_Read:OFF");
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
						DBG.pin_a1_read = 0;
						DBG.pin_a2_read = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
					}
					SSD1306_GotoXY (5,1);
					SSD1306_Puts ((char*)Arr, &Font_7x10, 1);

					memset(Arr, 0x00, sizeof(Arr));
					DBG.fpin_a4_volt = ((DBG.ADC0_final*3.3)/4095);
					sprintf((char *)Arr, "PA4_Pin:%0.2f v",DBG.fpin_a4_volt);
					SSD1306_GotoXY (5,14);
					SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
					
					memset(Arr, 0x00, sizeof(Arr));
					DBG.fpin_a5_volt = ((DBG.ADC1_final*3.3)/4095);
					sprintf((char *)Arr, "PA5_Pin:%0.2f v",DBG.fpin_a5_volt);
					SSD1306_GotoXY (5,27);
					SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
					
					memset(Arr, 0x00, sizeof(Arr));
					DBG.fpin_a6_volt = ((DBG.ADC2_final*3.3)/4095);
					sprintf((char *)Arr, "PA6_Pin:%0.2f v",DBG.fpin_a6_volt);
					SSD1306_GotoXY (5,40);
					SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
					
					memset(Arr, 0x00, sizeof(Arr));
					DBG.fpin_a7_volt = ((DBG.ADC3_final*3.3)/4095);
					sprintf((char *)Arr, "PA7_Pin:%0.2f v",DBG.fpin_a7_volt);
					SSD1306_GotoXY (5,53);
					SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
					
					SSD1306_UpdateScreen(); //display
				}
	}