#include "All_Variable.h"

Systick Sys;

void Init_Function(void)
{
	HAL_UART_Transmit(&huart2, (const uint8_t *)"CANProj \n\r", 10, 100);
	CAN_Init_Function();
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&UART.Rx, 1);
}

void Systick_Function(void)
{
	Sys.UART_Inc+=1;
	Sys.Common_Inc+=1;
	Sys.CAN_Inc+=1;
}


void While_Function(void)
{
	if(Sys.Common_Inc > 20)
		{
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		  Sys.Common_Inc = 0;
		  CAN_While_Function();
		}
	else
		{
			Uart_Rx2Tx_Instant();
			CAN_Rx2Tx_Instant();
		}
}
