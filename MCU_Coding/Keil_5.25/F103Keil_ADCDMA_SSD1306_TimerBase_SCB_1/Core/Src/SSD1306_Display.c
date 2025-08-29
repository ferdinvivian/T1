#include "SCB_Header.h"

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
	}

void Display_Timing (void)
	{
		if(GSCB.SysSSD_Inc >= 50)
			{
				GSCB.SysSSD_Inc = 0;
				GSCB.SSD +=1;
				Display_Continuous();
				Display_OneTime();
			}
	}	
	
	
	
void Display_Continuous (void)
{
		if((GSCB.SSD >= PAGE_1) && (GSCB.SSD < PAGE_2))
			{
				GSCB.Pg_Numb = 1;
			}
		
		else if((GSCB.SSD >= PAGE_2) && (GSCB.SSD < PAGE_3))
			{
				GSCB.Pg_Numb = 2;
				GSCB.Pg2_Inc +=1;
				
				if(GSCB.Pg2_Inc > 1)
					{
						char Arr[25];
						memset(Arr, 0x00, sizeof(Arr));
						sprintf((char *)Arr, "Adc0:%d", (uint16_t)GFADC.ADC0_Avg);
						SSD1306_GotoXY (5,2);
						SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
						
						memset(Arr, 0x00, sizeof(Arr));
						sprintf((char *)Arr, "Adc1:%d", (uint16_t)GFADC.ADC1_Avg);
						SSD1306_GotoXY (5,15);
						SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
						
						memset(Arr, 0x00, sizeof(Arr));
						sprintf((char *)Arr, "Adc2:%d", (uint16_t)GFADC.ADC2_Avg);
						SSD1306_GotoXY (5,28);
						SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
						
						memset(Arr, 0x00, sizeof(Arr));
						sprintf((char *)Arr, "Adc3:%d", (uint16_t)GFADC.ADC3_Avg);
						SSD1306_GotoXY (5,41);
						SSD1306_Puts ((char*)Arr, &Font_7x10, 1);
						
						SSD1306_UpdateScreen(); //display
					}
			}
			
		else
			{
				GSCB.SSD = GSCB.Pg_Numb = GSCB.Pg2_Inc	=	0;
			}
}
	




void Display_OneTime (void)
	{
		if((GSCB.Pg_Numb == 1) && (GSCB.SSD == PAGE_1))
			{
				GSCB.Pg_Numb = 0 ;
				SSD1306_Clear();
				
				ADC_Calc_Old ();
				char Arr[25];
				memset(Arr, 0x00, sizeof(Arr));
				sprintf((char *)Arr, "%s", (char*)&GSCB.Data[0]);
				SSD1306_GotoXY (10,20);
				SSD1306_Puts ((char*)Arr, &Font_11x18, 1);
				SSD1306_UpdateScreen(); //display
			}
			
		else if((GSCB.Pg_Numb == 2) && (GSCB.SSD == PAGE_2))
			{
				GSCB.Pg_Numb = 0 ;
				SSD1306_Clear();
			}
	}
