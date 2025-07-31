#ifndef INC_ALL_VARIABLE_H_
#define INC_ALL_VARIABLE_H_

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"




/*******************************************************************************************/
extern CAN_HandleTypeDef hcan;
extern UART_HandleTypeDef huart2;

extern CAN_TxHeaderTypeDef TxHeader;
extern CAN_RxHeaderTypeDef RxHeader;

typedef struct
{
	uint32_t TxMailbox[3];
	uint8_t TxData[8], RxData[8];
	uint8_t Flag, Inc;
}CAN_BUS;

extern CAN_BUS Can;

void CAN_Init_Function();
void CAN_Rx2Tx_Instant();
void CAN_While_Function();
/*******************************************************************************************/


/*******************************************************************************************/
typedef struct
{
	uint8_t Tx_Buf[40], Tx_Len;
	uint8_t Rx_Buf[30], Rx_Len, Rx;
}UniversalBus;

extern UniversalBus UART;

void Uart_Rx2Tx_Instant();
/*******************************************************************************************/


/*******************************************************************************************/
typedef struct
{
	uint32_t Common_Inc;
	uint32_t UART_Inc;
	uint32_t CAN_Inc;
}Systick;

extern Systick Sys;

void Init_Function(void);
void Systick_Function(void);
void While_Function(void);
/*******************************************************************************************/

#endif
