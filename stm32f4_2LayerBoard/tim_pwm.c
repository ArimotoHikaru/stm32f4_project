#include "tim_pwm.h"
//初期設定
#define TIM_CNTRCLK1     84000000 //TIM Clock Frequency : 24MHz
#define TIM_CNTRCLK2     84000000
#define TIM_FREQ       	 100000   //PWM Frequency   : 100KHz


void TIM_pwm_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	uint16_t TIM_PrescalerValue;
	uint16_t TIM_TimerPeriod;

	/* Define InitTypeDef ---------------------------------------------------*/
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef 			TIM_OCInitStructure;
	TIM_BDTRInitTypeDef 		TIM_BDTRInitStructure;

	/* initialize InitTypeDef -----------------------------------------------*/
	/* Supply clock source --------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM12, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE,ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin  	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_11 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  	= GPIO_Pin_4 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);	//TIM3_CH4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);	//TIM3_CH3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_TIM2);	//TIM2_CH4
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);	//TIM12_CH1
	//GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);	//TIM1_CH1N
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);	//TIM1_CH1
	//GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1);	//TIM1_CH3N
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);	//TIM1_CH4
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);	//TIM1_CH3

	/* Set up TIM_pwm function --------------------------------------------------*/
	TIM_PrescalerValue=(uint16_t)(SystemCoreClock/TIM_CNTRCLK1)-1;
	TIM_TimerPeriod=(uint16_t)(TIM_CNTRCLK1/TIM_FREQ)-1;

	//Time base configuration
	TIM_TimeBaseStructInit (&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period 			= TIM_TimerPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler 		= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision 	= 0;
	TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);

	TIM_TimerPeriod=(uint16_t)(TIM_CNTRCLK2/TIM_FREQ)-1;

	//Time base configuration
	TIM_TimeBaseStructure.TIM_Period = TIM_TimerPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler = 1;
	//APB2
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);

	//Output Compare Toggle Mode configuration
	TIM_OCStructInit (&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

	//TIM1_CH1
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Disable);
	//TIM1_CH3
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Disable);
	//TIM1_CH4
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Disable);
	//TIM2_CH4
	TIM_OC4Init(TIM2,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Disable);
	//TIM3_CH3
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Disable);
	//TIM3_CH4
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Disable);
	//TIM12_CH1
	TIM_OC1Init(TIM12,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM12,TIM_OCPreload_Disable);

	/*TIM1とTIM8はSTM32の中でも高機能タイマに分類され、1
	このBREAK機能の中でoutputの有効化という機能があり、デフォルトの設定で
	タイマー出力ごとにoutputが無効に設定されているためPWM信号が止まる。
	そのため、 タイマの更新イベントごとにoutputが自動的に再有効になるように設定する。*/
	TIM_BDTRStructInit(&TIM_BDTRInitStructure);
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_ARRPreloadConfig(TIM12,ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	TIM_Cmd(TIM1,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM12,ENABLE);

	/*main文でduty比を変えたい場合
	  TIMx->CCRy = z;
	  y=チャンネル
	  zはTIM_TimerPeriodで設定した値がカウントされる最上値なのでそれ以下の値を入れる
	  TIM_TimerPeriod=100だとするとz=50を代入すればduty比50%の出力が出る
	*/

}



