#include "Driver.h"

EEPROM EE;

void EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
	{
		if( (offset+size) <= BYTES_PER_PAGE )
			{
				if(page < TOTAL_PAGE_NUM)
					{
						HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR,  ((page<<BIT_SHIFT)|offset),
								2,  &data[0], size, 1000);
						 HAL_Delay (15); // Write cycle delay (5ms) Must
					}
			}
	}

void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size)
	{
		if( (offset+size) <= BYTES_PER_PAGE )
			{
				if(page < TOTAL_PAGE_NUM)
					{
						HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR,  ((page<<BIT_SHIFT)|offset),
								2, &data[0], size, 1000);
						 HAL_Delay (15);
					}
			}
	}

void EEPROM_FULL_ERASE()
{
	for(int8_t page = 0; page < TOTAL_PAGE_NUM; page++)
		{
			uint8_t data[BYTES_PER_PAGE];
			memset(data, 0x00, BYTES_PER_PAGE);

			HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, (page<<BIT_SHIFT),
					2, data, BYTES_PER_PAGE, 1000);
			 HAL_Delay (15);
		}
	HAL_Delay(10);
}

/****************************************************************************************/

void EE_Write_Relay_Time(uint8_t Relay, uint8_t *Time)
{
	switch (Relay)
	{
		case 1:
		{
			memset(EE.Rly_W1, 0x00, sizeof(EE.Rly_W1));
			memset(EE.Rly_R1, 0x00, sizeof(EE.Rly_R1));
			EE.Rly_W1[5] = ' ';

			for(uint8_t i=0; i<5; i++)
				EE.Rly_W1[i] = 	*(Time+i+11);
			for(uint8_t i=0; i<5; i++)
				EE.Rly_W1[i+6] = 	*(Time+i+21);

			EEPROM_Write (1, 0, EE.Rly_W1, 12);
			EEPROM_Read (1, 0, EE.Rly_R1, 12);
			break;
		}
		case 2:
		{
			memset(EE.Rly_W2, 0x00, sizeof(EE.Rly_W2));
			memset(EE.Rly_R2, 0x00, sizeof(EE.Rly_R2));
			EE.Rly_W2[5] = ' ';

			for(uint8_t i=0; i<5; i++)
				EE.Rly_W2[i] = 	*(Time+i+11);
			for(uint8_t i=0; i<5; i++)
				EE.Rly_W2[i+6] = 	*(Time+i+21);

			EEPROM_Write (2, 0, EE.Rly_W2, 12);
			EEPROM_Read (2, 0, EE.Rly_R2, 12);
			break;
		}
		default:
		{
			break;
		}
	}
}



void EE_Read_Init()
{
	//EEPROM_FULL_ERASE();
	EEPROM_Read (1, 0, EE.Rly_R1, 12);
	EEPROM_Read (2, 0, EE.Rly_R2, 12);
}



void EE_Read_while()
{
	EE.While_Inc +=1;

	if(EE.While_Inc > 600)	//Read Every 600 Seconds, 10 Minutes
		{
			EEPROM_Read (1, 0, EE.Rly_R1, 12);
			EEPROM_Read (2, 0, EE.Rly_R2, 12);
			EE.While_Inc = 0;
		}
}

