#include "adc.h"

int16_t ADCConvertedValue[8];//�����ǂ݂���

void ADC_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	/* Define InitTypeDef ---------------------------------------------------*/
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef       DMA_InitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;

	/* initialize InitTypeDef -----------------------------------------------*/
	ADC_StructInit(&ADC_InitStructure);
	ADC_CommonStructInit(&ADC_CommonInitStructure);
	DMA_StructInit(&DMA_InitStructure);

	/* Supply clock source --------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Set up DMA_function --------------------------------------------------*/
	DMA_DeInit(DMA2_Stream0);
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr 		= (uint32_t)&ADCConvertedValue;
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize 			= 8;
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	/* Set up ADC_function --------------------------------------------------*/
	ADC_DeInit();
	ADC_CommonInitStructure.ADC_Mode 			= ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler 		= ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode 	= ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode 			= ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode 	= ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv 		= 0;
	ADC_InitStructure.ADC_DataAlign 			= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion 		= 8;
	ADC_Init(ADC1, &ADC_InitStructure);

	//ADC1��DMA���g����悤�ɂ���
	ADC_DMACmd(ADC1, ENABLE);

	//ADC1�̃A�i���O���͂��`����
	//ADC_Channel_11��PA1,ADC_Channel_12��PA2�B�}�j���A��(UM1472)�̃s���z�\������Ƃ킩��
	//"ADC123_IN11"�Ƃ����\�L�́AADC1,ADC2,ADC3�Ŏg������͂�channel_11�Ɋ��蓖�Ă���A�Ƃ�������
	//�g���`���l���𑝂₷�ɂ́A�����ɒǋL����B�`���l���w��̎��̃p�����[�^�͕ϊ��V�[�P���X�̏���
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 4, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 5, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 6, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 7, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 7, ADC_SampleTime_480Cycles);
	ADC_VBATCmd(ENABLE);//?��������Ȃ�
	//�ϊ����ʂ�DMA�]������邲�ƂɁAADC�͎��̕ϊ����J�n����悤�ɐݒ�
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	//ADC1���g����悤�ɂ���
	ADC_Cmd(ADC1, ENABLE);
	//�ϊ��X�^�[�g
	ADC_SoftwareStartConv(ADC1);
}

uint16_t GetAdc1Value_xch(uint8_t ch)
{
	return ADCConvertedValue[ch];
}

