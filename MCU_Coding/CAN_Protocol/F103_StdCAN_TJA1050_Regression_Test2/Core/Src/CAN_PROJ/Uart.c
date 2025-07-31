#include "All_Variable.h"


UniversalBus UART;


void Uart_Rx2Tx_Instant()
{
	if((UART.Rx_Len > 0) && (Sys.UART_Inc > 10))
		{
			memset(UART.Tx_Buf, 0x00, sizeof(UART.Tx_Buf));
			UART.Tx_Len = sprintf((char *)UART.Tx_Buf,"\n\rTx: %s \n\r",UART.Rx_Buf);
			HAL_UART_Transmit(&huart2, (const uint8_t *)UART.Tx_Buf, UART.Tx_Len, (UART.Tx_Len*2));

			uint8_t Loop = UART.Rx_Len/8;
			for(uint8_t inc=0; inc<=Loop; inc++)
			{
				Can.TxData[0] = UART.Rx_Buf[(inc*8)+0];
				Can.TxData[1] = UART.Rx_Buf[(inc*8)+1];
				Can.TxData[2] = UART.Rx_Buf[(inc*8)+2];
				Can.TxData[3] = UART.Rx_Buf[(inc*8)+3];
				Can.TxData[4] = UART.Rx_Buf[(inc*8)+4];
				Can.TxData[5] = UART.Rx_Buf[(inc*8)+5];
				Can.TxData[6] = UART.Rx_Buf[(inc*8)+6];
				Can.TxData[7] = UART.Rx_Buf[(inc*8)+7];

				if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &Can.TxData[0], Can.TxMailbox) != HAL_OK)
				  {
					  Error_Handler();
				  }
			}

			UART.Rx_Len = UART.Tx_Len = 0;
			memset(UART.Rx_Buf, 0x00, sizeof(UART.Rx_Buf));
			memset(UART.Tx_Buf, 0x00, sizeof(UART.Tx_Buf));
		}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
    	UART.Rx_Buf[UART.Rx_Len] = UART.Rx;
    	HAL_UART_Receive_IT(&huart2, (uint8_t *)&UART.Rx, 1);

    	Sys.UART_Inc = 0;
    	UART.Rx_Len+=1;

    	if(UART.Rx_Len > (sizeof(UART.Rx_Buf)-5))
    	{
    		UART.Rx_Len = 0;
    		memset(UART.Rx_Buf, 0x00, sizeof(UART.Rx_Buf));
    	}
    }
}
