#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

extern 	ADC_HandleTypeDef 	hadc1;
extern 	DMA_HandleTypeDef 	hdma_adc1;
extern	I2C_HandleTypeDef 	hi2c1;
extern 	IWDG_HandleTypeDef 	hiwdg;
extern 	TIM_HandleTypeDef 	htim2;

#define	ADC_AVG		10
#define	PAGE_1		1
#define	PAGE_2		25
#define	PAGE_3		150

typedef struct
{	
	uint32_t 	Sys_Inc, 	While_Inc,	SysADC_Inc,	SysSSD_Inc;
	uint32_t	Tim2_IT_Inc,	Tim2_Val;
	uint32_t	SSD,	Pg_Numb,	Pg2_Inc;
	uint8_t		Data[20];
} Greenray_SCB_STRUCTURE;
extern Greenray_SCB_STRUCTURE GSCB;

typedef struct
{	
	uint32_t	ADC_Arr[4],	ADC_Arr_Inc,	ADC_Avg_Inc;
	uint32_t	ADC0_Arr[ADC_AVG],	ADC1_Arr[ADC_AVG];	
	uint32_t	ADC2_Arr[ADC_AVG],	ADC3_Arr[ADC_AVG];
	uint32_t	ADC0_Max,	ADC1_Max,	ADC2_Max,	ADC3_Max;
	uint32_t	ADC0_Avg,	ADC1_Avg,	ADC2_Avg,	ADC3_Avg;
} Greenray_ADC_STRUCTURE;
extern Greenray_ADC_STRUCTURE GADC;


typedef struct
{
	uint32_t	ADC0_Max,	ADC1_Max,	ADC2_Max,	ADC3_Max;
	uint32_t	ADC0_Avg,	ADC1_Avg,	ADC2_Avg,	ADC3_Avg;
} Greenray_FINALADC_STRUCTURE;
extern Greenray_FINALADC_STRUCTURE GFADC;


void Init_Code(void);
void While_Code(void);
void Systick_Code(void);

void ADC_Function(void);
void ADC_Ascending(void);
void ADC_Mid_Avg(void);
void ADC_Calc_Old(void);


void SSD1306_Init_Code(void);
void Display_Timing (void);
void Display_Continuous (void);		//Continuous
void Display_OneTime (void);			//One Time





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

