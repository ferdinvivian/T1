#include "main.h"
#include "stm32f4xx_it.h"

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#define PC13_DELAY 		100
#define DF_VOLUME 		30		//0to30
#define DF_STOP_SEC 	90		
#define STEP_DELAY 		1		//Min 1

extern TIM_HandleTypeDef htim11;
extern UART_HandleTypeDef huart1;


typedef struct
{	
	uint32_t 	Timer_Inc, DF_STOP, DF_REPEAT, Motor_Inc ; 
} GABI_TIMER11_STRUCTURE;
extern GABI_TIMER11_STRUCTURE Tim11;

typedef struct
{	
	uint8_t 	Loop_song, Motor_Step, Song_Play_Status; 
} PROJ_SOURCE_STRUCTURE;
extern PROJ_SOURCE_STRUCTURE prj;

void init_function();
void while_function();
void tim11_function();

void GABI_SONG_PLAY (void);
void STEPPER_MOTOR_ON (void);
void STEPPER_MOTOR_OFF (void);

/*************************************DF PLAYER************************************/
void Send_cmd (uint8_t cmd, uint8_t Parameter1, uint8_t Parameter2);
void DF_PlayFromStart(void);
void DF_Init (uint8_t volume);
void DF_Next (void);
void DF_Pause (void);
void DF_Previous (void);
void DF_Playback (void);

void Check_Key (void);
void DF_Reset (void);
/*************************************DF PLAYER************************************/