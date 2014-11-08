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
/*
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
/*
		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_1;
		GPIO_Init(GPIOE, &GPIO_InitStructure);//PE1

		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_Init(GPIOH, &GPIO_InitStructure);//PH0,1
		*/
	//Setup SystickTimer
	if (SysTick_Config(SystemCoreClock / 1000)){ColorfulRingOfDeath();}

	//Setup USB
	USBD_Init(&USB_OTG_dev,
	            USB_OTG_FS_CORE_ID,
	            &USR_desc,
	            &USBD_CDC_cb,
	            &USR_cb);


	//UB_Fatfs_Init();
	//ADC_Configuration();
	//I2C_Configuration();
	//TIM_encoder_Configuration();

	//USART1_Configuration();
	//USART2_Configuration();
	//USART3_Configuration();

}
int main(void)
{
	char str[50] = {0};
	init();
    while(1)
    {

    	while(ticker > 100){
    		ticker = 0;

    		sprintf(str,"hello world");
    		//transmit_uart3_s(str);
    		VCP_send_str(str);
    	}
    }
}
