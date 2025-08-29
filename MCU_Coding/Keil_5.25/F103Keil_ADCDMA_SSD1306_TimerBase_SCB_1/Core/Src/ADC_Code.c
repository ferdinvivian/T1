#include "SCB_Header.h"

Greenray_ADC_STRUCTURE				GADC;
Greenray_FINALADC_STRUCTURE		GFADC;
uint8_t	DATA_1[30];

void ADC_Function(void)
	{
		if(GSCB.SysADC_Inc >= 100)
			{
					HAL_ADC_Start_DMA(&hadc1 , (uint32_t *)GADC.ADC_Arr , 4);
				
					if(GADC.ADC_Arr_Inc	>=	ADC_AVG)
						{
							ADC_Ascending();
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
					GSCB.SysADC_Inc=0;
			}
	}


void ADC_Ascending(void)
	{
		GFADC.ADC0_Max	=	GFADC.ADC1_Max	=	GFADC.ADC2_Max	=	GFADC.ADC3_Max	=	0;
		for (uint8_t i = 0; i < GADC.ADC_Arr_Inc; ++i)
			{
				for (uint8_t j = i + 1; j < GADC.ADC_Arr_Inc; ++j)
					{
						if (GADC.ADC0_Arr[i] > GADC.ADC0_Arr[j])
							{
								GFADC.ADC0_Max	  =	GADC.ADC0_Arr[i];
								GADC.ADC0_Arr[i]  = GADC.ADC0_Arr[j];
								GADC.ADC0_Arr[j]	= GFADC.ADC0_Max	;
							}
						if (GADC.ADC1_Arr[i] > GADC.ADC1_Arr[j])
							{
								GFADC.ADC1_Max	  = GADC.ADC1_Arr[i];
								GADC.ADC1_Arr[i]  = GADC.ADC1_Arr[j];
								GADC.ADC1_Arr[j]  = GFADC.ADC1_Max	;
							}
						if (GADC.ADC2_Arr[i] > GADC.ADC2_Arr[j])
							{
								GFADC.ADC2_Max	  = GADC.ADC2_Arr[i];
								GADC.ADC2_Arr[i]  = GADC.ADC2_Arr[j];
								GADC.ADC2_Arr[j]  = GFADC.ADC2_Max	;
							}
						if (GADC.ADC3_Arr[i] > GADC.ADC3_Arr[j])
							{
								GFADC.ADC3_Max    = GADC.ADC3_Arr[i];
								GADC.ADC3_Arr[i]  = GADC.ADC3_Arr[j];
								GADC.ADC3_Arr[j]  = GFADC.ADC3_Max	;
							}
					}
			}
			ADC_Mid_Avg();
			GADC.ADC_Avg_Inc+=1;
	}
	
	
	
void ADC_Mid_Avg(void)
	{
		uint8_t Adc_Mid = ADC_AVG/2;
		GFADC.ADC0_Avg	=	GFADC.ADC1_Avg	=	GFADC.ADC1_Avg	=	GFADC.ADC2_Avg	=	0;
		
		GFADC.ADC0_Avg = ((GADC.ADC0_Arr[Adc_Mid-2]	+	GADC.ADC0_Arr[Adc_Mid-1]	+	
											GADC.ADC0_Arr[Adc_Mid]	+	GADC.ADC0_Arr[Adc_Mid+1])/4);
		
		GFADC.ADC1_Avg = ((GADC.ADC1_Arr[Adc_Mid-2]	+	GADC.ADC1_Arr[Adc_Mid-1]	+	
											GADC.ADC1_Arr[Adc_Mid]	+	GADC.ADC1_Arr[Adc_Mid+1])/4);
		
		GFADC.ADC2_Avg = ((GADC.ADC2_Arr[Adc_Mid-2]	+	GADC.ADC2_Arr[Adc_Mid-1]	+	
											GADC.ADC2_Arr[Adc_Mid]	+	GADC.ADC2_Arr[Adc_Mid+1])/4);
		
		GFADC.ADC3_Avg = ((GADC.ADC3_Arr[Adc_Mid-2]	+	GADC.ADC3_Arr[Adc_Mid-1]	+	
											GADC.ADC3_Arr[Adc_Mid]	+	GADC.ADC3_Arr[Adc_Mid+1])/4);
	}


void ADC_Calc_Old (void)
	{
		float Adc_Value = 0;

		if(GFADC.ADC1_Avg>=2450)//13.6
			{
				Adc_Value = (GFADC.ADC1_Avg/1.25);
			}
		if(	GFADC.ADC1_Avg<=2150)//1.22
			{
				Adc_Value = (GFADC.ADC1_Avg/1);
			}
		else
			{
				Adc_Value = (GFADC.ADC1_Avg/1.2);
			}		

		memset(GSCB.Data, 0x00, sizeof(GSCB.Data));					
		sprintf((char *)GSCB.Data,"RPM:%d",(uint16_t)Adc_Value);
	}