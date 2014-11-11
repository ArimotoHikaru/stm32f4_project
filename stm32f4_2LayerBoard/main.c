#include "main.h"
extern int ticker, downticker;
#define COLOR_SLAVE_ADDRESS 0x2A
#define EXPANDER_SLAVE_ADDRESS 0x77
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

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);//PD3

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStructure);//PE1
	/*
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOH, &GPIO_InitStructure);//PH0,1
	*/
	//Setup SystickTimer
	if (SysTick_Config(SystemCoreClock / 1000)){ColorfulRingOfDeath();}

#ifdef USE_MICROUSB
	USBD_Init(&USB_OTG_dev,
	            USB_OTG_FS_CORE_ID,
	            &USR_desc,
	            &USBD_CDC_cb,
	            &USR_cb);
#endif

#ifdef USE_SDIO
	UB_Fatfs_Init();
#endif

#ifdef USE_ADC
	ADC_Configuration();
#endif

#ifdef USE_I2C
	I2C_Configuration();
#endif

#ifdef USE_SPI
	SPI_Configuration();
#endif

#ifdef USE_ENCODER
	TIM_encoder_Configuration();
#endif

#ifdef USE_USART1
	USART1_Configuration();
#endif

#ifdef USE_USART2
	USART2_Configuration();
#endif

#ifdef USE_USART3
	USART3_Configuration();
#endif

}

int main(void)
{
	char str[50] = {0};
	init();

	TIM1->CCR1 = 839;//PE9
	TIM1->CCR3 = 439;//PE14
	TIM1->CCR4 = 839;//PE13
	TIM2->CCR4 = 839;//PB11
	TIM3->CCR3 = 839;//PB1
	TIM3->CCR4 = 439;//PB0
	TIM12->CCR1 = 839;//PB14

    while(1)
    {
    	TIM1->CCR1 = 839;//PE9
    	TIM1->CCR3 = 839;//PE14
    	TIM1->CCR4 = 839;//PE13
    	TIM2->CCR4 = 839;//PB11
    	TIM3->CCR3 = 839;//PB1
    	TIM3->CCR4 = 839;//PB0
    	TIM12->CCR1 = 839;//PB14

    	while(ticker > 50){
    		ticker = 0;

    		//transmit_uart3_s(str);
    		//VCP_send_str(str);
    	}
    }
}

/*
int main(void)
{
	char str[50] = {0};
	init();

	GPIOD->BSRRL = GPIO_Pin_12;
	sprintf(str,"I2C START \r\n");
	transmit_uart3_s(str);

	I2C_start(I2C1, EXPANDER_SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x80);
	I2C_stop(I2C1);
 	sprintf(str,"EXPANDER ADDRESS TRANSMITTED \r\n");
 	transmit_uart3_s(str);

	I2C_start(I2C1, COLOR_SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x00);
	I2C_write(I2C1, 0x8B);
	GPIOD->BSRRL = GPIO_Pin_13;
	I2C_start(I2C1, COLOR_SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x00);
	I2C_write(I2C1, 0x0B);
	I2C_stop(I2C1);
	sprintf(str,"COLOR ADDRESS TRANSMITTED \r\n");
	transmit_uart3_s(str);

	ticker = 0;
	while(ticker<180);

	GPIOD->BSRRL = GPIO_Pin_14;
	I2C_start(I2C1, COLOR_SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x03);
	I2C_start(I2C1, COLOR_SLAVE_ADDRESS<<1, I2C_Direction_Receiver);

	i2c_data[0] = I2C_read_ack(I2C1);
	i2c_data[1] = I2C_read_ack(I2C1);
	i2c_data[2] = I2C_read_ack(I2C1);
	i2c_data[3] = I2C_read_ack(I2C1);
	i2c_data[4] = I2C_read_ack(I2C1);
	i2c_data[5] = I2C_read_ack(I2C1);
	i2c_data[6] = I2C_read_ack(I2C1);
	i2c_data[7] = I2C_read_nack(I2C1);
	I2C_stop(I2C1);
	GPIOD->BSRRL = GPIO_Pin_15;

    while(1)
    {

    	while(ticker > 180){
    		ticker = 0;

			I2C_start(I2C1, COLOR_SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);
			I2C_write(I2C1, 0x03);
			I2C_start(I2C1, COLOR_SLAVE_ADDRESS<<1, I2C_Direction_Receiver);
			i2c_data[0] = I2C_read_ack(I2C1);
			i2c_data[1] = I2C_read_ack(I2C1);
			i2c_data[2] = I2C_read_ack(I2C1);
			i2c_data[3] = I2C_read_ack(I2C1);
			i2c_data[4] = I2C_read_ack(I2C1);
			i2c_data[5] = I2C_read_ack(I2C1);
			i2c_data[6] = I2C_read_ack(I2C1);
			i2c_data[7] = I2C_read_nack(I2C1);
			I2C_stop(I2C1);
		 	sprintf(str,"Red%d Green%d Blue%d IR%d\r\n",(i2c_data[0]<<8)|i2c_data[1], (i2c_data[2]<<8)|i2c_data[3], (i2c_data[4]<<8)|i2c_data[5], (i2c_data[6]<<8)|i2c_data[7]);
		 	transmit_uart3_s(str);

    	}
    }
}
*/
/*i2cŠm”F‚æ‚¤
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

    	}
    }
}
*/
