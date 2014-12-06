#include "can.h"

void CAN_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	/* Define InitTypeDef ---------------------------------------------------*/
	GPIO_InitTypeDef 		GPIO_InitStructure;
	CAN_InitTypeDef 		CAN_InitStructure;
	CAN_FilterInitTypeDef	CAN_FilterInitStructure;
	NVIC_InitTypeDef 		NVIC_InitStructure;

	/* initialize InitTypeDef -----------------------------------------------*/
	CAN_DeInit(&CAN_InitStructure);

	/* Supply clock source --------------------------------------------------*/
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1, ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
#if 1
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);//Rx
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);//Tx
#else
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);//Rx
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);//Tx
#endif
	/* Set up CAN function -------------------------------------------------*/
	/* �^�C���g���K�ʐM���[�h�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_TTCM = ENABLE;

	/* �����o�X�I�t�Ǘ�(Automatic Bus-Off Management)�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_ABOM 		= DISABLE;

	/* �����ċN�����[�h�̗L�����E��������ݒ肷��  */
	CAN_InitStructure.CAN_AWUM 		= DISABLE;

	/* �����đ��M�֎~��L�����E���������� DISABLE: �����đ��M�֎~�𖳌���(�܂�đ��M�͗L��) ENABLE: �����đ��M�֎~�B����ɑ��M����Ȃ��Ă����M��1�񂾂��s���� */
	CAN_InitStructure.CAN_NART 		= DISABLE;

	/* ��MFIFO���b�N���[�h�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_RFLM 		= DISABLE;

	/* ���MFIFO�̑��M�������w�肷��BDISABLE:���b�Z�[�WID�ő��M���������肳���  ENABLE:�\�t�g�E�F�A�ő��M�v�����������ꂽ���Ԃő��M����� */
	CAN_InitStructure.CAN_TXFP 		= DISABLE;

	/* CAN��Mode��ݒ肷�� */
	CAN_InitStructure.CAN_Mode 		= CAN_Mode_Normal;

	/* �ē����W�����v��(CAN�n�[�h�E�F�A���ē������s���ۂ̃r�b�g��)�����ԒP�ʂ̐��Őݒ肷�� */
	CAN_InitStructure.CAN_SJW 		= CAN_SJW_1tq;

	/* CAN�r�b�g�^�C�~���O���W�X�^(CAN_BTR)��TS1[3:0]��ݒ肷��B */
	CAN_InitStructure.CAN_BS1 		= CAN_BS1_3tq;

	/* CAN�r�b�g�^�C�~���O���W�X�^(CAN_BTR)��TS2[2:0]��ݒ肷�� */
	CAN_InitStructure.CAN_BS2 		= CAN_BS2_4tq;

	/* �{�[���[�g�v���X�P�[���ݒ肷�� APB1=42MHz*/
	CAN_InitStructure.CAN_Prescaler	= 15;

	CAN_Init(CAN1, &CAN_InitStructure);

	/* Set up CAN Filter function -------------------------------------------------*/
	/* �ݒ肷��t�B���^�[�i���o�[ 0�`13*/
	CAN_FilterInitStructure.CAN_FilterNumber			= 0;

	/* �t�B���^�[���[�h�ݒ� */
	CAN_FilterInitStructure.CAN_FilterMode				= CAN_FilterMode_IdList;

	/* �t�B���^�[�X�P�[���ݒ�  16bit or 32bit*/
	CAN_FilterInitStructure.CAN_FilterScale				= CAN_FilterScale_16bit;

	CAN_FilterInitStructure.CAN_FilterIdHigh			= 0x0000;//2

	CAN_FilterInitStructure.CAN_FilterIdLow				= 0x01E0;//0

	CAN_FilterInitStructure.CAN_FilterMaskIdHigh		= 0x0000;//3

	CAN_FilterInitStructure.CAN_FilterMaskIdLow			= 0x0000;//1

	CAN_FilterInitStructure.CAN_FilterFIFOAssignment	= 0;

	CAN_FilterInitStructure.CAN_FilterActivation		= ENABLE;

	CAN_FilterInit(&CAN_FilterInitStructure);

#ifdef USE_INTERRUPT_CAN_RX
	CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);
#endif
/*
#ifdef USE_INTERRUPT_CAN_TX
	CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
#endif
*/
}




