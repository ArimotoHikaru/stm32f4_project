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
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);

	/* Set up CAN function -------------------------------------------------*/
	/* �^�C���g���K�ʐM���[�h�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_TTCM = ENABLE;

	/* I�����o�X�I�t�Ǘ�(Automatic Bus-Off Management)�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_ABOM 		= DISABLE;

	/* �����ċN�����[�h�̗L�����E��������ݒ肷��  */
	CAN_InitStructure.CAN_AWUM 		= DISABLE;

	/* �����đ��M�֎~��L�����E���������� DISABLE: �����đ��M�֎~�𖳌���(�܂�đ��M�͗L��) ENABLE: �����đ��M�֎~�B����ɑ��M����Ȃ��Ă����M��1�񂾂��s���� */
	CAN_InitStructure.CAN_NART 		= DISABLE;

	/* ��MFIFO���b�N���[�h�̗L�����E��������ݒ肷�� */
	CAN_InitStructure.CAN_RFLM 		= DISABLE;

	/* ���MFIFO�̑��M�������w�肷��BDISABLE:���b�Z�[�WID�ő��M���������肳���  ENABLE:�\�t�g�E�F�A�ő��M�v�����������ꂽ���Ԃő��M����� */
	CAN_InitStructure.CAN_TXFP 		= DISABLE;

	/* Initialize the CAN_Mode member */
	CAN_InitStructure.CAN_Mode 		= CAN_Mode_LoopBack;

	/* �ē����W�����v��(CAN�n�[�h�E�F�A���ē������s���ۂ̃r�b�g��)�����ԒP�ʂ̐��Őݒ肷�� */
	CAN_InitStructure.CAN_SJW 		= CAN_SJW_1tq;

	/* CAN�r�b�g�^�C�~���O���W�X�^(CAN_BTR)��TS1[3:0]��ݒ肷��B */
	CAN_InitStructure.CAN_BS1 		= CAN_BS1_8tq;

	/* CAN�r�b�g�^�C�~���O���W�X�^(CAN_BTR)��TS2[2:0]��ݒ肷�� */
	CAN_InitStructure.CAN_BS2 		= CAN_BS2_7tq;

	/* �{�[���[�g�v���X�P�[���ݒ肷�� APB1=42MHz*/
	CAN_InitStructure.CAN_Prescaler	= 5;

	CAN_Init(CAN1, &CAN_InitStructure);

	/* Set up CAN Filter function -------------------------------------------------*/
	CAN_FilterInitStructure.CAN_FilterNumber			= 0;

	CAN_FilterInitStructure.CAN_FilterMode				= CAN_FilterMode_IdMask;

	CAN_FilterInitStructure.CAN_FilterScale				= CAN_FilterScale_32bit;

	CAN_FilterInitStructure.CAN_FilterIdHigh			= 0x0000;

	CAN_FilterInitStructure.CAN_FilterIdLow				= 0x0000;

	CAN_FilterInitStructure.CAN_FilterMaskIdHigh		= 0x0000;

	CAN_FilterInitStructure.CAN_FilterMaskIdLow			= 0x0000;

	CAN_FilterInitStructure.CAN_FilterFIFOAssignment	= 0;

	CAN_FilterInitStructure.CAN_FilterActivation		= DISABLE;

	CAN_FilterInit(&CAN_FilterInitStructure);

	//CAN_ITConfig(CAN_IT_FOV0, ENABLE);

}

void CAN1_TX_IRQHandler(void);
void CAN1_RX0_IRQHandler(void);
void CAN1_RX1_IRQHandler(void);
void CAN1_SCE_IRQHandler(void);
