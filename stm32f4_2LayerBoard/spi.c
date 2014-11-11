#include "spi.h"

#define	SPI1_NSS_Port	GPIOD
#define SPI1_NSS_Pin	GPIO_Pin_7


void SPI_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	/* Define InitTypeDef ---------------------------------------------------*/
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* initialize InitTypeDef -----------------------------------------------*/
	SPI_StructInit(&SPI_InitStructure);

	/* Supply clock source --------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE);

	/* Define gpio_config ---------------------------------------------------*/

	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_SPI1);

	GPIO_InitStructure.GPIO_Pin		= SPI1_NSS_Pin;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_Init(SPI1_NSS_Port, &GPIO_InitStructure);
	SPI1_NSS_Port->ODR = SPI1_NSS_Pin;

	/* Set up SPI function --------------------------------------------------*/
	SPI_I2S_DeInit(SPI1);
	SPI_InitStructure.SPI_Direction			= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode				= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize			= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL				= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA				= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS				= SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit			= SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);

#ifdef USE_INTERRUPT_SPI
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, ENABLE);
#endif
}

/* Private functions */
uint8_t SPI_Send(uint8_t Data)
{
	uint16_t RxData;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);		// wait until transmit complete
	SPI_I2S_SendData(SPI1,Data);										// write data to be transmitted to the SPI data register
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);	// wait until receive complete
	RxData = SPI_I2S_ReceiveData(SPI1);								// return received data from SPI data register
	return (uint8_t)RxData;
}

void SPI_Select()
{
	GPIO_ResetBits(SPI1_NSS_Port,SPI1_NSS_Pin);
}

void SPI_Deselect()
{
	GPIO_SetBits(SPI1_NSS_Port,SPI1_NSS_Pin);
}

