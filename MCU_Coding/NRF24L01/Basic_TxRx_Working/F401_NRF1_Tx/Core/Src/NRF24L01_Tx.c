#include "NRF24L01_Tx.h"

extern SPI_HandleTypeDef 	hspi1;
#define NRF24_SPI_TX	 	&hspi1

#define NRF24_CEN_PORT_TX   GPIOA
#define NRF24_CEN_PIN_TX    GPIO_PIN_3

#define NRF24_CSN_PORT_TX   GPIOA
#define NRF24_CSN_PIN_TX    GPIO_PIN_4


void CS_Select_TX (void)
{
	HAL_GPIO_WritePin(NRF24_CSN_PORT_TX, NRF24_CSN_PIN_TX, GPIO_PIN_RESET);
}
void CS_UnSelect_TX (void)
{
	HAL_GPIO_WritePin(NRF24_CSN_PORT_TX, NRF24_CSN_PIN_TX, GPIO_PIN_SET);
}
void CE_Enable_TX (void)
{
	HAL_GPIO_WritePin(NRF24_CEN_PORT_TX, NRF24_CEN_PIN_TX, GPIO_PIN_SET);
}
void CE_Disable_TX (void)
{
	HAL_GPIO_WritePin(NRF24_CEN_PORT_TX, NRF24_CEN_PIN_TX, GPIO_PIN_RESET);
}


void nrf24_WriteReg_TX (uint8_t Reg, uint8_t Data)
{
	uint8_t buf[2];
	buf[0] = Reg|1<<5;
	buf[1] = Data;

	// Pull the CS Pin LOW to select the device
	CS_Select_TX();

	HAL_SPI_Transmit(NRF24_SPI_TX, buf, 2, 1000);

	// Pull the CS HIGH to release the device
	CS_UnSelect_TX();
}
void nrf24_WriteRegMulti_TX (uint8_t Reg, uint8_t *data, int size)
{
	uint8_t buf[2];
	buf[0] = Reg|1<<5;
//	buf[1] = Data;

	// Pull the CS Pin LOW to select the device
	CS_Select_TX();

	HAL_SPI_Transmit(NRF24_SPI_TX, buf, 1, 100);
	HAL_SPI_Transmit(NRF24_SPI_TX, data, size, 1000);

	// Pull the CS HIGH to release the device
	CS_UnSelect_TX();
}


uint8_t nrf24_ReadReg_TX (uint8_t Reg)
{
	uint8_t data=0;

	// Pull the CS Pin LOW to select the device
	CS_Select_TX();

	HAL_SPI_Transmit(NRF24_SPI_TX, &Reg, 1, 100);
	HAL_SPI_Receive(NRF24_SPI_TX, &data, 1, 100);

	// Pull the CS HIGH to release the device
	CS_UnSelect_TX();

	return data;
}
void nrf24_ReadReg_Multi_TX (uint8_t Reg, uint8_t *data, int size)
{
	// Pull the CS Pin LOW to select the device
	CS_Select_TX();

	HAL_SPI_Transmit(NRF24_SPI_TX, &Reg, 1, 100);
	HAL_SPI_Receive(NRF24_SPI_TX, data, size, 1000);

	// Pull the CS HIGH to release the device
	CS_UnSelect_TX();
}


void nrfsendCmd_TX (uint8_t cmd)
{
	// Pull the CS Pin LOW to select the device
	CS_Select_TX();

	HAL_SPI_Transmit(NRF24_SPI_TX, &cmd, 1, 100);

	// Pull the CS HIGH to release the device
	CS_UnSelect_TX();
}



void NRF24_Init_Tx(void)
{
	CE_Disable_TX();						// disable the chip before configuring the device

	nrf24_reset_Tx (0);					// reset everything

	nrf24_WriteReg_TX(CONFIG, 0);  			// will be configured later

	nrf24_WriteReg_TX(EN_AA, 0);  			// No Auto ACK

	nrf24_WriteReg_TX(EN_RXADDR, 0);  		// Not Enabling any data pipe right now

	nrf24_WriteReg_TX(SETUP_AW, 0x03);  	// 5 Bytes for the TX/RX address

	nrf24_WriteReg_TX(SETUP_RETR, 0);  	 	// No retransmission

	nrf24_WriteReg_TX(RF_CH, 0);  			// will be setup during Tx or RX

	nrf24_WriteReg_TX(RF_SETUP, 0x0E);   	// Power= 0db, data rate = 2Mbps

	CE_Enable_TX();							// Enable the chip after configuring the device
}


void NRF24_TxMode (uint8_t *Address, uint8_t channel)
{
	// disable the chip before configuring the device
	CE_Disable_TX();

	nrf24_WriteReg_TX(RF_CH, channel);  			// select the channel
	nrf24_WriteRegMulti_TX(TX_ADDR, Address, 5);  	// Write the TX address

	// power up the device
	uint8_t config = nrf24_ReadReg_TX(CONFIG);
	config = config | (1<<1);   					// write 1 in the PWR_UP bit
	nrf24_WriteReg_TX(CONFIG, config);

	// Enable the chip after configuring the device
	CE_Enable_TX();
}


uint8_t NRF24_Transmit (uint8_t *data)
{
	uint8_t cmdtosend = 0;

	// select the device
	CS_Select_TX();

	// payload command
	cmdtosend = W_TX_PAYLOAD;
	HAL_SPI_Transmit(NRF24_SPI_TX, &cmdtosend, 1, 100);

	// send the payload
	HAL_SPI_Transmit(NRF24_SPI_TX, data, 32, 1000);

	// Unselect the device
	CS_UnSelect_TX();

	HAL_Delay(1);

	uint8_t fifostatus = nrf24_ReadReg_TX(FIFO_STATUS);

	// check the fourth bit of FIFO_STATUS to know if the TX fifo is empty
	if ((fifostatus&(1<<4)) && (!(fifostatus&(1<<3))))
		{
			cmdtosend = FLUSH_TX;
			nrfsendCmd_TX(cmdtosend);

			// reset FIFO_STATUS
			nrf24_reset_Tx (FIFO_STATUS);

			return 1;
		}

	return 0;
}


void nrf24_reset_Tx(uint8_t REG)
{
	if (REG == FIFO_STATUS)
	{
		nrf24_WriteReg_TX(FIFO_STATUS, 0x11);
	}
	else
	{
		nrf24_WriteReg_TX(CONFIG, 0x08);
		nrf24_WriteReg_TX(EN_AA, 0x3F);
		nrf24_WriteReg_TX(EN_RXADDR, 0x03);
		nrf24_WriteReg_TX(SETUP_AW, 0x03);
		nrf24_WriteReg_TX(SETUP_RETR, 0x03);
		nrf24_WriteReg_TX(RF_CH, 0x02);
		nrf24_WriteReg_TX(RF_SETUP, 0x0E);
		nrf24_WriteReg_TX(STATUS, 0x00);
		nrf24_WriteReg_TX(OBSERVE_TX, 0x00);
		nrf24_WriteReg_TX(CD, 0x00);

		uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		nrf24_WriteRegMulti_TX(RX_ADDR_P0, rx_addr_p0_def, 5);

		uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
		nrf24_WriteRegMulti_TX(RX_ADDR_P1, rx_addr_p1_def, 5);
		nrf24_WriteReg_TX(RX_ADDR_P2, 0xC3);
		nrf24_WriteReg_TX(RX_ADDR_P3, 0xC4);
		nrf24_WriteReg_TX(RX_ADDR_P4, 0xC5);
		nrf24_WriteReg_TX(RX_ADDR_P5, 0xC6);

		uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		nrf24_WriteRegMulti_TX(TX_ADDR, tx_addr_def, 5);
		nrf24_WriteReg_TX(RX_PW_P0, 0);
		nrf24_WriteReg_TX(RX_PW_P1, 0);
		nrf24_WriteReg_TX(RX_PW_P2, 0);
		nrf24_WriteReg_TX(RX_PW_P3, 0);
		nrf24_WriteReg_TX(RX_PW_P4, 0);
		nrf24_WriteReg_TX(RX_PW_P5, 0);

		nrf24_WriteReg_TX(FIFO_STATUS, 0x11);
		nrf24_WriteReg_TX(DYNPD, 0);
		nrf24_WriteReg_TX(FEATURE, 0);
	}
}
