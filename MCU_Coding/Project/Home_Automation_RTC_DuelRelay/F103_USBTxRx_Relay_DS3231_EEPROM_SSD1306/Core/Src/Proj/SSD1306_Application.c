#include "Driver.h"

SSD1306_Display	SSD_1306;

void SSD1306_Init_Code()
	{
		SSD1306_Init();
		SSD1306_Clear();

		SSD1306_GotoXY (5,5);
		SSD1306_Puts ("WELCOME", &Font_16x26, 1);

		SSD1306_GotoXY (10,40);
		SSD1306_Puts ("Rebooting", &Font_11x18, 1);

		SSD1306_UpdateScreen();
	}


void SSD1306_WhileCode(void)
{
	switch (SSD_1306.Inc1)
	{
		case 1 ... 14 :
				SSD1306_All_Information();
				break;
		case 16 ... 24 :
				SSD1306_Time_Information();
				break;
		case 26 ... 34 :
				SSD1306_Relay1_Information();
				break;
		case 36 ... 44 :
				SSD1306_Relay2_Information();
				break;
		case 46 ... 255 :
				SSD_1306.Inc1 = 0;
				SSD_1306.Inc2 +=1;
				break;
		default :
				SSD1306_ReInitialize();
				break;
	}

	SSD_1306.Inc1+=1;
}



void SSD1306_ReInitialize()
{
	SSD1306_Init();
	SSD1306_Clear();
}


void SSD1306_All_Information()
{
	SSD1306_GotoXY (0,0);
	SSD1306_Puts ((char*)"Hr:Mn:Sec Dt:Mt:Yr", &Font_7x10, 1);

	SSD1306_GotoXY (0,10);
	SSD1306_Puts ((char*)&Cmn.Time[0], &Font_7x10, 1);

	char Temperature[5];
	memset(Temperature, 0x00, sizeof(Temperature));
	sprintf((char *)Temperature, "%d'", (char)Time.DS_Temp);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts ((char*)Temperature, &Font_16x26, 1);

	SSD1306_GotoXY (34,32);
	SSD1306_Puts ((char*)"C ON    OFF ", &Font_7x10, 1);

	SSD1306_GotoXY (0,43);
	SSD1306_Puts ((char*)"Rly1: ", &Font_7x10, 1);

	SSD1306_GotoXY (40,43);
	SSD1306_Puts ((char*)&EE.Rly_R1[0], &Font_7x10, 1);

	SSD1306_GotoXY (0,53);
	SSD1306_Puts ((char*)"Rly2: ", &Font_7x10, 1);

	SSD1306_GotoXY (40,53);
	SSD1306_Puts ((char*)&EE.Rly_R2[0], &Font_7x10, 1);

	SSD1306_UpdateScreen();
}


void SSD1306_Time_Information()
{
	uint8_t time[10];
	uint8_t date[10];

	memset(time, 0x00, sizeof(time));
	sprintf((char *)time, " %c%c:%c%c:%c%c", Cmn.Time[0], Cmn.Time[1],
			Cmn.Time[3], Cmn.Time[4], Cmn.Time[6], Cmn.Time[7]);

	memset(date, 0x00, sizeof(date));
	sprintf((char *)date, " %c%c:%c%c:%c%c", Cmn.Time[10], Cmn.Time[11],
			Cmn.Time[13], Cmn.Time[14], Cmn.Time[16], Cmn.Time[17]);

	switch(Time.week)
		{
			case 1:
				SSD1306_GotoXY (26,5);
				SSD1306_Puts ((char*)"Sunday", &Font_11x18, 1);
				break;
			case 2:
				SSD1306_GotoXY (26,5);
				SSD1306_Puts ((char*)"Monday", &Font_11x18, 1);
				break;
			case 3:
				SSD1306_GotoXY (21,5);
				SSD1306_Puts ((char*)"Tuesday", &Font_11x18, 1);
				break;
			case 4:
				SSD1306_GotoXY (11,5);
				SSD1306_Puts ((char*)"Wednesday", &Font_11x18, 1);
				break;
			case 5:
				SSD1306_GotoXY (16,5);
				SSD1306_Puts ((char*)"Thursday", &Font_11x18, 1);
				break;
			case 6:
				SSD1306_GotoXY (26,5);
				SSD1306_Puts ((char*)"Friday", &Font_11x18, 1);
				break;
			case 7:
				SSD1306_GotoXY (16,5);
				SSD1306_Puts ((char*)"Saturday", &Font_11x18, 1);
				break;
			default:
				SSD1306_GotoXY (35,5);
				SSD1306_Puts ((char*)"Time", &Font_11x18, 1);
				break;
		}

	SSD1306_GotoXY (5,25);
	SSD1306_Puts ((char*)time, &Font_11x18, 1);

	SSD1306_GotoXY (5,45);
	SSD1306_Puts ((char*)date, &Font_11x18, 1);

	SSD1306_UpdateScreen();
}


void SSD1306_Relay1_Information()
{
	uint8_t Data1[5];
	uint8_t Data2[5];

	for(uint8_t i=0; i<5; i++)
		Data1[i] = 	EE.Rly_R1[i];

	for(uint8_t i=0; i<5; i++)
		Data2[i] = 	EE.Rly_R1[i+6];


	if(SSD_1306.Inc2%2)
		{
			SSD1306_GotoXY (5,0);
			SSD1306_Puts ((char*)"Relay 1", &Font_16x26, 1);

			SSD1306_GotoXY (10,32);
			SSD1306_Puts ((char*)"On Time", &Font_7x10, 1);

			SSD1306_GotoXY (70,27);
			SSD1306_Puts ((char*)Data1, &Font_11x18, 1);

			SSD1306_GotoXY (5,50);
			SSD1306_Puts ((char*)"Off Time", &Font_7x10, 1);

			SSD1306_GotoXY (70,45);
			SSD1306_Puts ((char*)Data2, &Font_11x18, 1);
		}
	else
		{
			SSD1306_GotoXY (1,7);
			SSD1306_Puts ((char*)"ON1", &Font_11x18, 1);

			SSD1306_GotoXY (40,3);
			SSD1306_Puts ((char*)Data1, &Font_16x26, 1);

			SSD1306_GotoXY (1,27);
			SSD1306_Puts ((char*)"Relay", &Font_7x10, 1);

			SSD1306_GotoXY (1,41);
			SSD1306_Puts ((char*)"OFF", &Font_11x18, 1);

			SSD1306_GotoXY (40,37);
			SSD1306_Puts ((char*)Data2, &Font_16x26, 1);
		}


	SSD1306_UpdateScreen();
}


void SSD1306_Relay2_Information()
{
	uint8_t Data1[5];
	uint8_t Data2[5];

	for(uint8_t i=0; i<5; i++)
		Data1[i] = 	EE.Rly_R2[i];

	for(uint8_t i=0; i<5; i++)
		Data2[i] = 	EE.Rly_R2[i+6];

	if(SSD_1306.Inc2%2)
		{
			SSD1306_GotoXY (5,0);
			SSD1306_Puts ((char*)"Relay 2", &Font_16x26, 1);

			SSD1306_GotoXY (10,32);
			SSD1306_Puts ((char*)"On Time", &Font_7x10, 1);

			SSD1306_GotoXY (70,27);
			SSD1306_Puts ((char*)Data1, &Font_11x18, 1);

			SSD1306_GotoXY (5,50);
			SSD1306_Puts ((char*)"Off Time", &Font_7x10, 1);

			SSD1306_GotoXY (70,45);
			SSD1306_Puts ((char*)Data2, &Font_11x18, 1);
		}
	else
		{
			SSD1306_GotoXY (1,7);
			SSD1306_Puts ((char*)"ON2", &Font_11x18, 1);

			SSD1306_GotoXY (40,3);
			SSD1306_Puts ((char*)Data1, &Font_16x26, 1);

			SSD1306_GotoXY (1,27);
			SSD1306_Puts ((char*)"Relay", &Font_7x10, 1);

			SSD1306_GotoXY (1,41);
			SSD1306_Puts ((char*)"OFF", &Font_11x18, 1);

			SSD1306_GotoXY (40,37);
			SSD1306_Puts ((char*)Data2, &Font_16x26, 1);
		}


	SSD1306_UpdateScreen();
}
