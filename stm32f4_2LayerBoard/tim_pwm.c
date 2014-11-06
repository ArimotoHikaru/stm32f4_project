#include "tim_pwm.h"
//初期設定
#define TIM_CNTRCLK1     84000000 //TIM Clock Frequency : 24MHz
#define TIM_CNTRCLK2     84000000
#define TIM_FREQ       	 100000   //PWM Frequency   : 100KHz
//モーター設定
#define BRAKE   999


void TIM_pwm_Configuration(void)
{
	uint16_t TIM_PrescalerValue;
	uint16_t TIM_TimerPeriod;

	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef 			TIM_OCInitStructure;
	TIM_BDTRInitTypeDef 		TIM_BDTRInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_TIM9, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM12, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE,ENABLE);

	//GPIO pin configuration
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_14;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);

	TIM_PrescalerValue=(uint16_t)(SystemCoreClock/TIM_CNTRCLK1)-1;
	TIM_TimerPeriod=(uint16_t)(TIM_CNTRCLK1/TIM_FREQ)-1;

	//Time base configuration
	TIM_TimeBaseStructInit (&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = TIM_TimerPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	//APB1
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
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
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;


	//TIM1_CH1
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Disable);
	//TIM1_CH2
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Disable);
	//TIM1_CH4
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Disable);
	//TIM2_CH2
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Disable);
	//TIM2_CH3
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Disable);
	//TIM3_CH3
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Disable);
	//TIM9_CH1
	TIM_OC1Init(TIM9,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM9,TIM_OCPreload_Disable);
	//TIM9_CH2
	TIM_OC2Init(TIM9,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM9,TIM_OCPreload_Disable);
	//TIM12_CH1
	TIM_OC1Init(TIM12,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM12,TIM_OCPreload_Disable);
	//TIM12_CH2
	TIM_OC2Init(TIM12,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Disable);

	/*TIM1とTIM8はSTM32の中でも高機能タイマに分類され、
	モータ制御用に使用されるBREAK入力機能がついている
	このBREAK機能の中でoutputの有効化という機能があり、デフォルトの設定で
	タイマー出力ごとにoutputが無効に設定されているためPWM信号が止まる。
	そのため、 タイマの更新イベントごとにoutputが自動的に再有効になるように設定する。*/
	TIM_BDTRStructInit(&TIM_BDTRInitStructure);
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_ARRPreloadConfig(TIM9,ENABLE);
	TIM_ARRPreloadConfig(TIM12,ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM9, ENABLE);

	TIM_Cmd(TIM1,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM9,ENABLE);
	TIM_Cmd(TIM12,ENABLE);
}

void Init_Motor(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_StructInit(&GPIO_InitStructure);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOB , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_14;

  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;

  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

  GPIO_Init(GPIOE, &GPIO_InitStructure);

}
/*
void Motor1_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CW | MOTOR1_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CW);
      GPIO_ResetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CCW);
      GPIO_ResetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR1_OUT_PIN, MOTOR1_OUT_CW | MOTOR1_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM4->CCR4 = (int)(duty*665/100);
}
void Motor2_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CW | MOTOR2_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CW);
      GPIO_ResetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CCW);
      GPIO_ResetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR2_OUT_PIN, MOTOR2_OUT_CW | MOTOR2_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM4->CCR3 = (int)(duty*665/100);
}
void Motor3_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CW | MOTOR3_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CW);
      GPIO_ResetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CCW);
      GPIO_ResetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR3_OUT_PIN, MOTOR3_OUT_CW | MOTOR3_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM1->CCR4 = (int)(duty*239/100);
}
void Motor4_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CW | MOTOR4_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CW);
      GPIO_ResetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CCW);
      GPIO_ResetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR4_OUT_PIN, MOTOR4_OUT_CW | MOTOR4_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM1->CCR3 = (int)(duty*239/100);
}
void Motor5_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CW | MOTOR5_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CW);
      GPIO_ResetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CCW);
      GPIO_ResetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR5_OUT_PIN, MOTOR5_OUT_CW | MOTOR5_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM1->CCR2 = (int)(duty*239/100);
}
void Motor6_Out(int duty)
{
  if(duty == 999){
      GPIO_SetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CW | MOTOR6_OUT_CCW);
  }else if(duty>0){
      GPIO_SetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CW);
      GPIO_ResetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CCW);
  }else if(duty<0){
      GPIO_SetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CCW);
      GPIO_ResetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CW);
  }else if(duty==0){
      GPIO_ResetBits(MOTOR6_OUT_PIN, MOTOR6_OUT_CW | MOTOR6_OUT_CCW);
  }
  if(duty < 0){
      duty *= -1;
  }
  if(duty > 100){
      duty = 100;
  }

  TIM1->CCR1 = (int)(duty*239/100);
}


void Motor_Left_Right(int duty_L, int duty_R)
{
  static int    direct_shift_L = 0,
                direct_shift_R = 0,
                duty_L_old = 0,
                duty_R_old = 0;
  if(duty_L_old)

  Motor1_Out(duty_L);
  Motor2_Out(duty_R);



  if(duty_L > 0){
      duty_L_old = 1;
  }else if(duty_L < 0){
      duty_L_old = -1;
  }else if(duty_L == 0){
      duty_L_old = 0;
  }else if(duty_L == 999){
      duty_L_old = 999;
  }

}
*/


