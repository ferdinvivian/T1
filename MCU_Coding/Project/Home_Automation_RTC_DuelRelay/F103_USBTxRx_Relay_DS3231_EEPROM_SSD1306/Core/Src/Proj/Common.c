#include "Driver.h"

Systick Sys;
Common Cmn;


void Proj_Init_Function(void)
{
	//Set_Time(35, 17, 6, Friday, 27, June, 25);
	memset(Cmn.Test, 0x00, sizeof(Cmn.Test));
	memset(Cmn.Time, 0x00, sizeof(Cmn.Time));

	SSD1306_Init_Code();
	EE_Read_Init();

	Relay_Init_Code();
	CDC_Transmit_FS((uint8_t*)"F103_USB_Tx \n\r", 14);
}


void Proj_While_Function(void)
{
	if(Sys.Common_Inc > 1000)
		{
			Sys.Common_Inc = 0;
			HAL_IWDG_Refresh(&hiwdg);
			Cmn.Test_Inc += 1;
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

			DS3231_While_Function();
			EE_Read_while();
			Relay_While();
		}
	else
		{
			USB_Rx2Tx_Instant();
		}
}


void Systick_Function(void)
{
	Sys.Common_Inc +=1;
	Sys.EE_Inc +=1;
	Sys.RTC_Inc +=1;
	Sys.SSD_Inc +=1;
	Sys.USB_Inc +=1;
}


/*************************************************************************************/


