#include "Driver.h"

DS3231 Time;

uint8_t decToBcd(int val)
{
  return (uint8_t)( (val/10*16) + (val%10) );
}

int bcdToDec(uint8_t val)
{
  return (int)( (val/16*10) + (val%16) );
}

void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t week, uint8_t date, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(week);
	set_time[4] = decToBcd(date);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDR, 0x00, 1, set_time, 7, 1000);
}

void Get_Time (void)
{
	uint8_t get_time[7];
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x00, 1, get_time, 7, 1000);
	Time.sec = bcdToDec(get_time[0]);
	Time.min = bcdToDec(get_time[1]);
	Time.hour = bcdToDec(get_time[2]);
	Time.week = bcdToDec(get_time[3]);
	Time.date = bcdToDec(get_time[4]);
	Time.month = bcdToDec(get_time[5]);
	Time.year = bcdToDec(get_time[6]);
}

float Get_Temp (void)
{
	uint8_t temp[2];

	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x11, 1, temp, 2, 1000);
	return ((temp[0])+(temp[1]>>6)/4.0);
}

void force_temp_conv (void)
{
	uint8_t status=0;
	uint8_t control=0;

	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x0F, 1, &status, 1, 100);  // read status register
	if (!(status&0x04))  // if the BSY bit is not set
	{
		HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, 0x0E, 1, &control, 1, 100);  // read control register
		HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDR, 0x0E, 1, (uint8_t *)(control|(0x20)), 1, 100);  // write modified control register with CONV bit as'1'
	}
}

/****************************************************************************************/

void Split_Time_Function(void)
{
	//Hr:Min:Sec  Date:Month:Year
	memset(Cmn.Time, 0x00, sizeof(Cmn.Time));

	Cmn.Time[2] = Cmn.Time[5] = Cmn.Time[12] = Cmn.Time[15] = ':';
	Cmn.Time[8] = Cmn.Time[9] = ' ';

	Cmn.Time[0] = (Time.hour/10) + 0x30;
	Cmn.Time[1] = (Time.hour%10) + 0x30;

	Cmn.Time[3] = (Time.min/10) + 0x30;
	Cmn.Time[4] = (Time.min%10) + 0x30;

	Cmn.Time[6] = (Time.sec/10) + 0x30;
	Cmn.Time[7] = (Time.sec%10) + 0x30;

	Cmn.Time[10] = (Time.date/10) + 0x30;
	Cmn.Time[11] = (Time.date%10) + 0x30;

	Cmn.Time[13] = (Time.month/10) + 0x30;
	Cmn.Time[14] = (Time.month%10) + 0x30;

	Cmn.Time[16] = (Time.year/10) + 0x30;
	Cmn.Time[17] = (Time.year%10) + 0x30;
}


void DS3231_While_Function(void)
{
	force_temp_conv();
	Time.DS_Temp = Get_Temp();

	Get_Time();
	Split_Time_Function();

	USB_Tx_while();
	SSD1306_WhileCode();
}

