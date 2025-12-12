#include "SCB_Header.h"

Greenray_ADC_STRUCTURE						GADC;


void SysADC_Function(void)
	{
		if(Sys.Adc_Inc >= ADC_SPEED)
			{
					HAL_ADC_Start_DMA(&hadc1 , (uint32_t *)GADC.ADC_Arr , 4);
				
					if(GADC.ADC_Arr_Inc	>=	ADC_AVG)
						{
							ADC_Ascending();
							ADC_Mid_Avg();
							ADC_RPMCalc_Old();
							GADC.ADC_Arr_Inc = 0;
						}
					else
						{
							GADC.ADC0_Arr[GADC.ADC_Arr_Inc]	=	GADC.ADC_Arr[0];
							GADC.ADC1_Arr[GADC.ADC_Arr_Inc]	=	GADC.ADC_Arr[1];
							GADC.ADC2_Arr[GADC.ADC_Arr_Inc]	=	GADC.ADC_Arr[2];
							GADC.ADC3_Arr[GADC.ADC_Arr_Inc]	=	GADC.ADC_Arr[3];
							GADC.ADC_Arr_Inc+=1;
						}
					Sys.Adc_Inc=0;
			}
	}
	
	
	
void ADC_Ascending(void)
	{
		GADC.ADC0_Max	=	GADC.ADC1_Max	=	GADC.ADC2_Max	=	GADC.ADC3_Max	=	0;
		for (uint8_t i = 0; i < GADC.ADC_Arr_Inc; ++i)
			{
				for (uint8_t j = i + 1; j < GADC.ADC_Arr_Inc; ++j)
					{
						if (GADC.ADC0_Arr[i] > GADC.ADC0_Arr[j])
							{
								GADC.ADC0_Max	  =	GADC.ADC0_Arr[i];
								GADC.ADC0_Arr[i]  = GADC.ADC0_Arr[j];
								GADC.ADC0_Arr[j]	= GADC.ADC0_Max	;
							}
						if (GADC.ADC1_Arr[i] > GADC.ADC1_Arr[j])
							{
								GADC.ADC1_Max	  = GADC.ADC1_Arr[i];
								GADC.ADC1_Arr[i]  = GADC.ADC1_Arr[j];
								GADC.ADC1_Arr[j]  = GADC.ADC1_Max	;
							}
						if (GADC.ADC2_Arr[i] > GADC.ADC2_Arr[j])
							{
								GADC.ADC2_Max	  = GADC.ADC2_Arr[i];
								GADC.ADC2_Arr[i]  = GADC.ADC2_Arr[j];
								GADC.ADC2_Arr[j]  = GADC.ADC2_Max	;
							}
						if (GADC.ADC3_Arr[i] > GADC.ADC3_Arr[j])
							{
								GADC.ADC3_Max    = GADC.ADC3_Arr[i];
								GADC.ADC3_Arr[i]  = GADC.ADC3_Arr[j];
								GADC.ADC3_Arr[j]  = GADC.ADC3_Max	;
							}
					}
			}
	}
	
	
void ADC_Mid_Avg(void)
	{
		uint8_t Adc_Mid = ADC_AVG/2;
		
		DBG.ADC0_final = ((GADC.ADC0_Arr[Adc_Mid-2]	+	GADC.ADC0_Arr[Adc_Mid-1]	+	
											GADC.ADC0_Arr[Adc_Mid]	+	GADC.ADC0_Arr[Adc_Mid+1])/4);
		
		DBG.ADC1_final = ((GADC.ADC1_Arr[Adc_Mid-2]	+	GADC.ADC1_Arr[Adc_Mid-1]	+	
											GADC.ADC1_Arr[Adc_Mid]	+	GADC.ADC1_Arr[Adc_Mid+1])/4);
		
		DBG.ADC2_final = ((GADC.ADC2_Arr[Adc_Mid-2]	+	GADC.ADC2_Arr[Adc_Mid-1]	+	
											GADC.ADC2_Arr[Adc_Mid]	+	GADC.ADC2_Arr[Adc_Mid+1])/4);
		
		DBG.ADC3_final = ((GADC.ADC3_Arr[Adc_Mid-2]	+	GADC.ADC3_Arr[Adc_Mid-1]	+	
											GADC.ADC3_Arr[Adc_Mid]	+	GADC.ADC3_Arr[Adc_Mid+1])/4);
	}
	
	
	
void ADC_RPMCalc_Old (void)
	{
		//ADC3->PA7->RPM
		float RPM_Value = 0;
		memset(Disp.RPM_Data, 0x00, sizeof(Disp.RPM_Data));		
		
		if(DBG.ADC3_final>=2450)//13.6
				RPM_Value = (DBG.ADC3_final/1.25);
		else if(	DBG.ADC3_final<=2150)//1.22
				RPM_Value = (DBG.ADC3_final/1);
		else
				RPM_Value = (DBG.ADC3_final/1.2);
		
		if(RPM_Value < 220)
			RPM_Value = 0;
		else
			RPM_Value = (RPM_Value - 220);

		if((uint16_t)RPM_Value < 10)
			sprintf((char *)Disp.RPM_Data,"RPM_SET :000%d ",(uint16_t)RPM_Value);	
		else if(((uint16_t)RPM_Value< 100) && ((uint16_t)RPM_Value >= 10))
			sprintf((char *)Disp.RPM_Data,"RPM_SET :00%d  ",(uint16_t)RPM_Value);	
		else if(((uint16_t)RPM_Value< 1000) && ((uint16_t)RPM_Value >= 100))
			sprintf((char *)Disp.RPM_Data,"RPM_SET :0%d   ",(uint16_t)RPM_Value);
		else
			sprintf((char *)Disp.RPM_Data,"RPM_SET :%d    ",(uint16_t)RPM_Value);			
	}
