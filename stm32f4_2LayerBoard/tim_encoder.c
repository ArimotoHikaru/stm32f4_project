#include "tim_encoder.h"

void TIM_encoder_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	uint16_t PrescalerValue = 0;

	/* Define InitTypeDef ---------------------------------------------------*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef 		GPIO_InitStructure;

	/* initialize InitTypeDef -----------------------------------------------*/
	/* Supply clock source --------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
/*
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
*/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);

	/* Set up TIM_encoder function --------------------------------------------------*/
	/* プリスケーラの値の設定 */
	PrescalerValue = (uint16_t) ((SystemCoreClock ) / 84000000) - 1;

	/* メンバの値の設定 */
	TIM_TimeBaseStructure.TIM_Period		= 0xffff-1;
	TIM_TimeBaseStructure.TIM_Prescaler		= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	/* プリスケーラの設定 */
	TIM_PrescalerConfig(TIM4, PrescalerValue, TIM_PSCReloadMode_Immediate);
	TIM_PrescalerConfig(TIM5, PrescalerValue, TIM_PSCReloadMode_Immediate);
	TIM_PrescalerConfig(TIM8, PrescalerValue, TIM_PSCReloadMode_Immediate);

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	/*更新割り込み設定*/
#ifdef USE_INTERRUPT_TIM4
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );
#endif

#ifdef USE_INTERRUPT_TIM5
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE );
#endif

#ifdef USE_INTERRUPT_TIM8_13
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE );
#endif

	/* TIM enable counter */
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
	TIM_Cmd(TIM8, ENABLE);

}
void TIM12_encoder_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	uint16_t PrescalerValue = 0;

	/* Define InitTypeDef ---------------------------------------------------*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef 		GPIO_InitStructure;

	/* initialize InitTypeDef -----------------------------------------------*/
	/* Supply clock source --------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);//TIM12_CH1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);//TIM12_CH2

	/* Set up TIM_encoder function --------------------------------------------------*/
	/* プリスケーラの値の設定 */
	PrescalerValue = (uint16_t) ((SystemCoreClock ) / 84000000) - 1;

	/* メンバの値の設定 */
	TIM_TimeBaseStructure.TIM_Period		= 0xffff-1;
	TIM_TimeBaseStructure.TIM_Prescaler		= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);

	/* プリスケーラの設定 */
	TIM_PrescalerConfig(TIM12, PrescalerValue, TIM_PSCReloadMode_Immediate);
	TIM_EncoderInterfaceConfig(TIM12, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	/*更新割り込み設定*/
#ifdef USE_INTERRUPT_TIM4
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );
#endif

	/* TIM enable counter */
	TIM_Cmd(TIM12, ENABLE);

}
