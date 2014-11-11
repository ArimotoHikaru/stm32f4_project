#include "i2c.h"

int busycheckflag[3]={1,1,1};
int transmitter[3]={0,0,0};

void I2C_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	/* Define InitTypeDef ---------------------------------------------------*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	I2C_InitTypeDef 	I2C_InitStructure;

	/* initialize InitTypeDef -----------------------------------------------*/
	I2C_StructInit(&I2C_InitStructure);

	/* Supply clock source --------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD , ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
 	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_8 | GPIO_Pin_9;
 	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF;
 	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
 	GPIO_InitStructure.GPIO_OType	= GPIO_OType_OD;
 	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);//PB8 SCL
 	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);//PB9 SDA

	/* Set up I2C_function --------------------------------------------------*/
	I2C_DeInit(I2C1);
 	I2C_InitStructure.I2C_Mode					= I2C_Mode_I2C;
 	I2C_InitStructure.I2C_DutyCycle				= I2C_DutyCycle_16_9;
 	I2C_InitStructure.I2C_Ack					= I2C_Ack_Enable;
 	I2C_InitStructure.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
 	I2C_InitStructure.I2C_ClockSpeed			= 50000;
 	I2C_Init(I2C1, &I2C_InitStructure);
 	I2C_Cmd(I2C1, ENABLE);

#ifdef USE_INTERRUPT_I2C1
 	I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE);
#endif

}

void AWrite_ATP(int slave_add, int cmd)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,slave_add,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C1,cmd);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS);
	I2C_GenerateSTOP(I2C1, ENABLE);
}

char ARead_ATP(int slave_add)
{
  char rdata;

  I2C_Cmd(I2C1,ENABLE);

  I2C_GenerateSTART(I2C1,ENABLE);

  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

  I2C_Send7bitAddress(I2C1,slave_add,I2C_Direction_Receiver);

  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  I2C_AcknowledgeConfig(I2C1,DISABLE);

  I2C_GenerateSTOP(I2C1, ENABLE);

  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));

  rdata = I2C_ReceiveData(I2C1);

  return rdata;
}

void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction)
{

	// wait until I2C1 is not busy anymore
	if(busycheckflag[0]){
	 	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	 	busycheckflag[0] = 0;
	}

	// Send I2C1 START condition
	I2C_GenerateSTART(I2Cx, ENABLE);
	// wait for I2C1 EV5 --> Slave has acknowledged start condition
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	// Send slave Address for write
	I2C_Send7bitAddress(I2Cx, address, direction);

	/* wait for I2C1 EV6, check if
	* either Slave has acknowledged Master transmitter or
	* Master receiver mode, depending on the transmission
	* direction
	*/
	if(direction == I2C_Direction_Transmitter){
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}else if(direction == I2C_Direction_Receiver){
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}

}

/* This function transmits one byte to the slave device
* Parameters:
*		I2Cx --> the I2C peripheral e.g. I2C1
*		data --> the data byte to be transmitted
*/
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data)
{
	I2C_SendData(I2Cx, data);
	// wait for I2C1 EV8_2 --> byte has been transmitted
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}


/* This function reads one byte from the slave device
* and acknowledges the byte (requests another byte)
*/
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx)
{
	// enable acknowledge of recieved data
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	// wait until one byte has been received
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );

	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}


/* This function reads one byte from the slave device
* and doesn't acknowledge the recieved data
*/
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx)
{
	// disabe acknowledge of received data
	// nack also generates stop condition after last byte received
	// see reference manual for more info
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);
	// wait until one byte has been received
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}

/* This funtion issues a stop condition and therefore
* releases the bus
*/
void I2C_stop(I2C_TypeDef* I2Cx)
{
	// Send I2C1 STOP Condition
	I2C_GenerateSTOP(I2Cx, ENABLE);
	busycheckflag[0] = 1;
}








