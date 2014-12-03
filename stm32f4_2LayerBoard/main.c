#include <stdio.h>
#include "main.h"

extern int ticker, downticker;

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

	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
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

#ifdef USE_CAN
	CAN_Configuration();
#endif

#ifdef USE_PWM
	TIM_pwm_Configuration();
#endif

#ifdef USE_EXTI
	EXTI_Configuration();
#endif

	NVIC_Configuration();
}

int main(void)
{
	char str[50] = {0};
	CanTxMsg can_tx_flame;
	CanRxMsg can_rx_flame;

	init();

	sprintf(str,"Hello! start CAN communication!\n\r");
	VCP_send_str(str);

	can_tx_flame.StdId 		= 0x001;//ID 11bit 0～0x7FF
	can_tx_flame.ExtId		= 0x0;	//拡張フレームID 28bit 0～0x1FFFFFFF
	can_tx_flame.IDE 		= 0;	//拡張フレームIDを使う場合1
	can_tx_flame.RTR		= 0;	//データフレーム:0 リモートフレーム:1
	can_tx_flame.DLC		= 1;	//送信するデータフィールドのバイト数
	can_tx_flame.Data[0]	= 0xCD;	//送信するデータフィールド

	CAN_Transmit(CAN1, &can_tx_flame);//送信

	GPIOD->BSRRL = GPIO_Pin_13;

	ticker = 0;
	while(ticker<50);

	GPIOD->BSRRL = GPIO_Pin_14;

	CAN_Receive(CAN1, CAN_FIFO0, &can_rx_flame);//受信

	GPIOD->BSRRL = GPIO_Pin_15;

    while(1)
    {

    	while(ticker > 50){
    		ticker = 0;

    		sprintf(str,"0x%X\n\r",can_tx_flame.Data[0]);
    		//transmit_uart3_s(str);
    		VCP_send_str(str);
    	}
    }
}
