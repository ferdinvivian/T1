#include "All_Variable.h"

CAN_BUS 			Can;
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;



void CAN_Init_Function()
{
	HAL_CAN_Start(&hcan);
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	TxHeader.DLC = 8;				//CAN_TDT0R->0X40006584 0:4
	TxHeader.ExtId = 0;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = 0x123;
	TxHeader.TransmitGlobalTime = DISABLE;
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, &Can.RxData[0]);

	UART.Tx_Buf[(Can.Flag*8)+0] = Can.RxData[0];
	UART.Tx_Buf[(Can.Flag*8)+1] = Can.RxData[1];
	UART.Tx_Buf[(Can.Flag*8)+2] = Can.RxData[2];
	UART.Tx_Buf[(Can.Flag*8)+3] = Can.RxData[3];
	UART.Tx_Buf[(Can.Flag*8)+4] = Can.RxData[4];
	UART.Tx_Buf[(Can.Flag*8)+5] = Can.RxData[5];
	UART.Tx_Buf[(Can.Flag*8)+6] = Can.RxData[6];
	UART.Tx_Buf[(Can.Flag*8)+7] = Can.RxData[7];

	Can.Flag+=1;
	Sys.CAN_Inc = 0;
}


void CAN_Rx2Tx_Instant()
{
	if((Sys.CAN_Inc > 10) && (Can.Flag > 0))
		{
			UART.Tx_Len = strlen((const char *)UART.Tx_Buf);
			HAL_UART_Transmit(&huart2, (const uint8_t *)UART.Tx_Buf, UART.Tx_Len, (UART.Tx_Len*2));

			Can.Flag = UART.Tx_Len = 0;
			memset(Can.RxData, 0x00, sizeof(Can.RxData));
			memset(UART.Tx_Buf, 0x00, sizeof(UART.Tx_Buf));
		}
}



void CAN_While_Function()
{
	Can.Inc+=1;
	uint8_t Temp = (Can.Inc/10);

	Can.TxData[0] = 'T';
	Can.TxData[1] = 'x';
	Can.TxData[2] = ':';
	Can.TxData[3] = ((Can.Inc/100) + (0x30));
	Can.TxData[4] = ((Temp%10) + (0x30));
	Can.TxData[5] = ((Can.Inc%10) + (0x30));
	Can.TxData[6] = '\n';
	Can.TxData[7] = '\r';

	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &Can.TxData[0], Can.TxMailbox) != HAL_OK)
	  {
		  Error_Handler();
	  }
}
