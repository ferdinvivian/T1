#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#include "main.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"

extern I2C_HandleTypeDef hi2c1;
extern IWDG_HandleTypeDef hiwdg;

//SetTime= 07:20:00 Sat 28:06:25 	// Sun Mon Tue Wed Thu Fri Sat
//Relay1= On 18:00 Off 22:00
//Relay2= On 19:00 Off 21:00

/************************************* COMMON ***************************************/
typedef struct
{
	uint32_t Common_Inc, RTC_Inc;
	uint32_t EE_Inc, USB_Inc, SSD_Inc ;
}Systick;

extern Systick Sys;

typedef struct
{
	uint32_t Test_Inc;
	uint8_t Test[30], Time[20];
}Common;

extern Common Cmn;

void Proj_Init_Function(void);
void Proj_While_Function(void);
void Systick_Function(void);
/************************************* COMMON ***************************************/

/************************************* DS3231 ***************************************/
#define DS3231_ADDR 	0xD0

typedef enum
{
	Sunday  = 1,
	Monday,	Tuesday,	Wednesday,
	Thursday,	Friday,	Saturday
}Week;

typedef enum
{
	January  = 1,
	February,	March,	April,	May, June, July,
	August,	September,	October, November, December
}Month;

typedef struct
{
	uint8_t sec, min, hour;
	uint8_t week;
	uint8_t date, month, year;
	uint16_t Get;
	float DS_Temp;
}DS3231;

extern DS3231 Time;

uint8_t decToBcd(int val);
int bcdToDec(uint8_t val);
void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t week, uint8_t date, uint8_t month, uint8_t year);
void Get_Time (void);

float Get_Temp (void);
void force_temp_conv (void);

void Split_Time_Function(void);
void DS3231_While_Function(void);
/************************************* DS3231 ***************************************/

/************************************* EEPROM ***************************************/
#define EEPROM_ADDR 	0xAE
#define TOTAL_PAGE_NUM 	64
#define BYTES_PER_PAGE  32
#define BIT_SHIFT 		8

typedef struct
{
	uint16_t While_Inc;
	uint8_t Rly_W1[12], Rly_W2[12];
	uint8_t Rly_R1[12], Rly_R2[12];
}EEPROM;

extern EEPROM EE;

void EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_FULL_ERASE();

void EE_Write_Relay_Time(uint8_t Relay, uint8_t *Time);
void EE_Read_Init();
void EE_Read_while();
/************************************* EEPROM ***************************************/

/************************************* SSD_DRV **************************************/
#define SSD1306_I2C_ADDR         	0x78
#define SSD1306_WIDTH            	128
#define SSD1306_HEIGHT           	64
#define SSD1306_NORMALDISPLAY  		0xA6
#define SSD1306_INVERTDISPLAY       0xA7

#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define SSD1306_DEACTIVATE_SCROLL                    0x2E // Stop scroll
#define SSD1306_ACTIVATE_SCROLL                      0x2F // Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 // Set scroll range

typedef enum
{
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;

typedef struct
{
	uint16_t Length;      /*!< String length in units of pixels */
	uint16_t Height;      /*!< String height in units of pixels */
} FONTS_SIZE_t;

typedef struct
{
	uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} FontDef_t;

extern FontDef_t Font_7x10;
extern FontDef_t Font_11x18;
extern FontDef_t Font_16x26;

extern const uint16_t Font7x10 [];
extern const uint16_t Font11x18 [];
extern const uint16_t Font16x26 [];

/* Write command */
#define SSD1306_WRITECOMMAND(command)      ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
/* Write data */
#define SSD1306_WRITEDATA(data)            ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))
/* Absolute value */
#define ABS(x)   ((x) > 0 ? (x) : -(x))


void ssd1306_I2C_Init();
void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) ;
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);
char* FONTS_GetStringSize(char* str, FONTS_SIZE_t* SizeStruct, FontDef_t* Font);
void SSD1306_Clear (void);

uint8_t SSD1306_Init(void);
void SSD1306_UpdateScreen(void);
void SSD1306_ToggleInvert(void);
void SSD1306_Fill(SSD1306_COLOR_t Color);
void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
void SSD1306_GotoXY(uint16_t x, uint16_t y);
char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);
char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);
void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);
void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);
void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);
/************************************* SSD_DRV **************************************/

/************************************* SSD_APP **************************************/
typedef struct
{
	uint8_t Inc1 , Inc2;
} SSD1306_Display;

extern SSD1306_Display	SSD_1306;

void SSD1306_Init_Code();
void SSD1306_WhileCode(void);

void SSD1306_ReInitialize();
void SSD1306_All_Information();
void SSD1306_Time_Information();
void SSD1306_Relay1_Information();
void SSD1306_Relay2_Information();
/************************************* SSD_APP **************************************/

/*************************************** USB ****************************************/
typedef struct
{
	uint8_t Tx_While_Inc;
	uint8_t Tx_Buf[60], Tx_Len;
	uint8_t Rx_Buf[45], Rx_Len;
}UniversalSerialBus;

extern UniversalSerialBus UsB;


void USB_Tx_while();
void USB_Rx2Tx_Instant();

uint8_t USB_SetTime();
uint8_t USB_Relay1_SetTime();
uint8_t USB_Relay2_SetTime();
/*************************************** USB ****************************************/

/***************************************RELAY****************************************/
typedef struct
{
	uint8_t While_Inc , Scenario1 , Scenario2;
	uint16_t ON1 , OFF1;
	uint16_t ON2 , OFF2;
}Relay;

extern Relay Rly;

void Relay_While();
void Relay_Time_Calculate();
void Relay_Possible_Scenario();

void Relay_Init_Code();
void Relay1_Control();
void Relay2_Control();
/***************************************RELAY****************************************/
