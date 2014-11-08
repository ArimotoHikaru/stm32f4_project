#include "main.h"
extern int ticker, downticker;
#define SLAVE_ADDRESS 0x2A
char i2c_data[8] = {0};
void XXX_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	/* Define InitTypeDef ---------------------------------------------------*/
	/* initialize InitTypeDef -----------------------------------------------*/
	/* Supply clock source --------------------------------------------------*/
	/* Define gpio_config ---------------------------------------------------*/
	/* Set up XXX_function --------------------------------------------------*/
}

void init(void)
{
	SystemInit();

	GPIO_InitTypeDef GPIO_InitStructure;

		RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA |
								RCC_AHB1Periph_GPIOC |
								RCC_AHB1Periph_GPIOD |
								RCC_AHB1Periph_GPIOE |
								RCC_AHB1Periph_GPIOH, ENABLE);

		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//PA15

		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_13 | GPIO_Pin_14;// | GPIO_Pin_15;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//PC13,14,15

		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_Init(GPIOD, &GPIO_InitStructure);//PD3

		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_1;
		GPIO_Init(GPIOE, &GPIO_InitStructure);//PE1
/*
		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_Init(GPIOH, &GPIO_InitStructure);//PH0,1
		*/
	//Setup SystickTimer
	if (SysTick_Config(SystemCoreClock / 1000)){ColorfulRingOfDeath();}
/*
	//Setup USB
	USBD_Init(&USB_OTG_dev,
	            USB_OTG_FS_CORE_ID,
	            &USR_desc,
	            &USBD_CDC_cb,
	            &USR_cb);
*/

	//UB_Fatfs_Init();
	//ADC_Configuration();
	I2C_Configuration();
	//TIM_encoder_Configuration();
	//USART1_Configuration();
	//USART2_Configuration();
	USART3_Configuration();

}
int main(void)
{
	char str[50] = {0};
	init();

	I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x00);
	I2C_write(I2C1, 0x8B);

	I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	GPIOD->BSRRL = GPIO_Pin_13;
	I2C_write(I2C1, 0x00);
	I2C_write(I2C1, 0x0B);
	I2C_stop(I2C1);
	ticker = 0;
	while(ticker<2);
	I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x03);
	I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Receiver);

	i2c_data[0] = I2C_read_ack(I2C1);
	i2c_data[1] = I2C_read_ack(I2C1);
	i2c_data[2] = I2C_read_ack(I2C1);
	i2c_data[3] = I2C_read_ack(I2C1);
	i2c_data[4] = I2C_read_ack(I2C1);
	i2c_data[5] = I2C_read_ack(I2C1);
	i2c_data[6] = I2C_read_ack(I2C1);
	i2c_data[7] = I2C_read_nack(I2C1);
	I2C_stop(I2C1);
	GPIOD->BSRRL = GPIO_Pin_14;

    while(1)
    {

    	while(ticker > 50){
    		ticker = 0;

			I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
			GPIOD->BSRRL = GPIO_Pin_15;
			I2C_write(I2C1, 0x03);
			I2C_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Receiver);
			i2c_data[0] = I2C_read_ack(I2C1);
			i2c_data[1] = I2C_read_ack(I2C1);
			i2c_data[2] = I2C_read_ack(I2C1);
			i2c_data[3] = I2C_read_ack(I2C1);
			i2c_data[4] = I2C_read_ack(I2C1);
			i2c_data[5] = I2C_read_ack(I2C1);
			i2c_data[6] = I2C_read_ack(I2C1);
			i2c_data[7] = I2C_read_nack(I2C1);
			I2C_stop(I2C1);
		 	sprintf(str,"0:%3d 1:%3d 2:%3d 3:%3d 4:%3d 5:%3d 6:%3d 7:%3d \r\n",i2c_data[0], i2c_data[1], i2c_data[2], i2c_data[3], i2c_data[4], i2c_data[5], i2c_data[6], i2c_data[7]);
		 	transmit_uart3_s(str);
/*
    		sprintf(str,"hello world \n\r");
    		transmit_uart3_s(str);
    		//VCP_send_str(str);*/
    	}
    }
}
