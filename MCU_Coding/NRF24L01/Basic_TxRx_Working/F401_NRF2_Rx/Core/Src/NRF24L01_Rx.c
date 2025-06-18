#include <NRF24L01_Rx.h>

extern SPI_HandleTypeDef 	hspi1;
#define NRF24_SPI_RX	 	&hspi1

#define NRF24_CEN_PORT_RX   GPIOA
#define NRF24_CEN_PIN_RX    GPIO_PIN_3

#define NRF24_CSN_PORT_RX   GPIOA
#define NRF24_CSN_PIN_RX    GPIO_PIN_4


void CS_Select_RX (void)
{
	HAL_GPIO_WritePin(NRF24_CSN_PORT_RX, NRF24_CSN_PIN_RX, GPIO_PIN_RESET);
}
void CS_UnSelect_RX (void)
{
	HAL_GPIO_WritePin(NRF24_CSN_PORT_RX, NRF24_CSN_PIN_RX, GPIO_PIN_SET);
}
void CE_Enable_RX (void)
{
	HAL_GPIO_WritePin(NRF24_CEN_PORT_RX, NRF24_CEN_PIN_RX, GPIO_PIN_SET);
}
void CE_Disable_RX (void)
{
	HAL_GPIO_WritePin(NRF24_CEN_PORT_RX, NRF24_CEN_PIN_RX, GPIO_PIN_RESET);
}

void nrf24_WriteReg_RX (uint8_t Reg, uint8_t Data)
{
	uint8_t buf[2];
	buf[0] = Reg|1<<5;
	buf[1] = Data;

	// Pull the CS Pin LOW to select the device
	CS_Select_RX();

	HAL_SPI_Transmit(NRF24_SPI_RX, buf, 2, 1000);

	// Pull the CS HIGH to release the device
	CS_UnSelect_RX();
}

void nrf24_WriteRegMulti_RX (uint8_t Reg, uint8_t *data, int size)
{
	uint8_t buf[2];
	buf[0] = Reg|1<<5;
//	buf[1] = Data;

	// Pull the CS Pin LOW to select the device
	CS_Select_RX();

	HAL_SPI_Transmit(NRF24_SPI_RX, buf, 1, 100);
	HAL_SPI_Transmit(NRF24_SPI_RX, data, size, 1000);

	// Pull the CS HIGH to release the device
	CS_UnSelect_RX();
}

uint8_t nrf24_ReadReg_RX (uint8_t Reg)
{
	uint8_t data=0;

	// Pull the CS Pin LOW to select the device
	CS_Select_RX();

	HAL_SPI_Transmit(NRF24_SPI_RX, &Reg, 1, 100);
	HAL_SPI_Receive(NRF24_SPI_RX, &data, 1, 100);

	// Pull the CS HIGH to release the device
	CS_UnSelect_RX();

	return data;
}

// send the command to the NRF
void nrfsendCmd_RX (uint8_t cmd)
{
	// Pull the CS Pin LOW to select the device
	CS_Select_RX();

	HAL_SPI_Transmit(NRF24_SPI_RX, &cmd, 1, 100);

	// Pull the CS HIGH to release the device
	CS_UnSelect_RX();
}


void NRF24_RxMode (uint8_t *Address, uint8_t channel)
{
	// disable the chip before configuring the device
	CE_Disable_RX();

	nrf24_reset_Rx (STATUS);

	nrf24_WriteReg_RX(RF_CH, channel);  // select the channel

	// select data pipe 1
	uint8_t en_rxaddr = nrf24_ReadReg_RX(EN_RXADDR);
	en_rxaddr = en_rxaddr | (1<<1);
	nrf24_WriteReg_RX (EN_RXADDR, en_rxaddr);

	nrf24_WriteRegMulti_RX(RX_ADDR_P1, Address, 5);   	// Write the Tx Address
	nrf24_WriteReg_RX(RX_PW_P1, 32);   					// 32 bit payload size for pipe 2

	// power up the device in Rx mode
	uint8_t config = nrf24_ReadReg_RX(CONFIG);
	config = config | (1<<1) | (1<<0) ;
	nrf24_WriteReg_RX (CONFIG, config);

	// Enable the chip after configuring the device
	CE_Enable_RX();
}


uint8_t isDataAvailable (int pipenum)
{
	uint8_t status = nrf24_ReadReg_RX(STATUS);

	if ((status&(1<<6))&&(status&(pipenum<<1)))
	{
		nrf24_WriteReg_RX(STATUS, (1<<6));
		return 1;
	}

	return 0;
}


void NRF24_Receive (uint8_t *data)
{
	uint8_t cmdtosend = 0;

	// select the device
	CS_Select_RX();

	// payload command
	cmdtosend = R_RX_PAYLOAD;
	HAL_SPI_Transmit(NRF24_SPI_RX, &cmdtosend, 1, 100);

	// Receive the payload
	HAL_SPI_Receive(NRF24_SPI_RX, data, 32, 1000);

	// Unselect the device
	CS_UnSelect_RX();

	HAL_Delay(1);

	cmdtosend = FLUSH_RX;
	nrfsendCmd_RX(cmdtosend);
}


void NRF24_Init_Rx(void)
{
	CE_Disable_RX();						// disable the chip before configuring the device

	nrf24_reset_Rx (0);					// reset everything

	nrf24_WriteReg_RX(CONFIG, 0);  			// will be configured later

	nrf24_WriteReg_RX(EN_AA, 0);  			// No Auto ACK

	nrf24_WriteReg_RX(EN_RXADDR, 0);  		// Not Enabling any data pipe right now

	nrf24_WriteReg_RX(SETUP_AW, 0x03);  	// 5 Bytes for the TX/RX address

	nrf24_WriteReg_RX(SETUP_RETR, 0);  	 	// No retransmission

	nrf24_WriteReg_RX(RF_CH, 0);  			// will be setup during Tx or RX

	nrf24_WriteReg_RX(RF_SETUP, 0x0E);   	// Power= 0db, data rate = 2Mbps

	CE_Enable_RX();							// Enable the chip after configuring the device
}

void nrf24_reset_Rx(uint8_t REG)
{
	if (REG == STATUS)
	{
		nrf24_WriteReg_RX(STATUS, 0x00);
	}
	else
	{
		nrf24_WriteReg_RX(CONFIG, 0x08);
		nrf24_WriteReg_RX(EN_AA, 0x3F);
		nrf24_WriteReg_RX(EN_RXADDR, 0x03);
		nrf24_WriteReg_RX(SETUP_AW, 0x03);
		nrf24_WriteReg_RX(SETUP_RETR, 0x03);
		nrf24_WriteReg_RX(RF_CH, 0x02);
		nrf24_WriteReg_RX(RF_SETUP, 0x0E);
		nrf24_WriteReg_RX(STATUS, 0x00);
		nrf24_WriteReg_RX(OBSERVE_TX, 0x00);
		nrf24_WriteReg_RX(CD, 0x00);

		uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		nrf24_WriteRegMulti_RX(RX_ADDR_P0, rx_addr_p0_def, 5);
		uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
		nrf24_WriteRegMulti_RX(RX_ADDR_P1, rx_addr_p1_def, 5);

		nrf24_WriteReg_RX(RX_ADDR_P2, 0xC3);
		nrf24_WriteReg_RX(RX_ADDR_P3, 0xC4);
		nrf24_WriteReg_RX(RX_ADDR_P4, 0xC5);
		nrf24_WriteReg_RX(RX_ADDR_P5, 0xC6);

		uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		nrf24_WriteRegMulti_RX(TX_ADDR, tx_addr_def, 5);

		nrf24_WriteReg_RX(RX_PW_P0, 0);
		nrf24_WriteReg_RX(RX_PW_P1, 0);
		nrf24_WriteReg_RX(RX_PW_P2, 0);
		nrf24_WriteReg_RX(RX_PW_P3, 0);
		nrf24_WriteReg_RX(RX_PW_P4, 0);
		nrf24_WriteReg_RX(RX_PW_P5, 0);

		nrf24_WriteReg_RX(FIFO_STATUS, 0x11);
		nrf24_WriteReg_RX(DYNPD, 0);
		nrf24_WriteReg_RX(FEATURE, 0);
	}
}


