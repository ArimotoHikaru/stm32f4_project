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
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);//Rx
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);//Tx

	/* Set up CAN function -------------------------------------------------*/
	/* タイムトリガ通信モードの有効化・無効化を設定する */
	CAN_InitStructure.CAN_TTCM = ENABLE;

	/* I自動バスオフ管理(Automatic Bus-Off Management)の有効化・無効化を設定する */
	CAN_InitStructure.CAN_ABOM 		= DISABLE;

	/* 自動再起動モードの有効化・無効化を設定する  */
	CAN_InitStructure.CAN_AWUM 		= DISABLE;

	/* 自動再送信禁止を有効化・無効化する DISABLE: 自動再送信禁止を無効化(つまり再送信は有効) ENABLE: 自動再送信禁止。正常に送信されなくても送信は1回だけ行われる */
	CAN_InitStructure.CAN_NART 		= DISABLE;

	/* 受信FIFOロックモードの有効化・無効化を設定する */
	CAN_InitStructure.CAN_RFLM 		= DISABLE;

	/* 送信FIFOの送信順序を指定する。DISABLE:メッセージIDで送信順序が決定される  ENABLE:ソフトウェアで送信要求が発生された順番で送信される */
	CAN_InitStructure.CAN_TXFP 		= DISABLE;

	/* CANのModeを設定する */
	CAN_InitStructure.CAN_Mode 		= CAN_Mode_LoopBack;

	/* 再同期ジャンプ幅(CANハードウェアが再同期を行う際のビット幅)を時間単位の数で設定する */
	CAN_InitStructure.CAN_SJW 		= CAN_SJW_1tq;

	/* CANビットタイミングレジスタ(CAN_BTR)のTS1[3:0]を設定する。 */
	CAN_InitStructure.CAN_BS1 		= CAN_BS1_8tq;

	/* CANビットタイミングレジスタ(CAN_BTR)のTS2[2:0]を設定する */
	CAN_InitStructure.CAN_BS2 		= CAN_BS2_7tq;

	/* ボーレートプリスケーラ設定する APB1=42MHz*/
	CAN_InitStructure.CAN_Prescaler	= 5;

	CAN_Init(CAN1, &CAN_InitStructure);

	/* Set up CAN Filter function -------------------------------------------------*/
	/* 設定するフィルターナンバー 0～13*/
	CAN_FilterInitStructure.CAN_FilterNumber			= 0;

	/* フィルターモード設定 */
	CAN_FilterInitStructure.CAN_FilterMode				= CAN_FilterMode_IdList;

	/* フィルタースケール設定  16bit or 32bit*/
	CAN_FilterInitStructure.CAN_FilterScale				= CAN_FilterScale_16bit;

	CAN_FilterInitStructure.CAN_FilterIdHigh			= 0x01E0;

	CAN_FilterInitStructure.CAN_FilterIdLow				= 0x0000;

	CAN_FilterInitStructure.CAN_FilterMaskIdHigh		= 0x0000;

	CAN_FilterInitStructure.CAN_FilterMaskIdLow			= 0x0000;

	CAN_FilterInitStructure.CAN_FilterFIFOAssignment	= 0;

	CAN_FilterInitStructure.CAN_FilterActivation		= ENABLE;

	CAN_FilterInit(&CAN_FilterInitStructure);

#ifdef USE_INTERRUPT_CAN
	//CAN_ITConfig(CAN1, CAN_IT_TME, ENABLE);
	CAN_ITConfig(CAN1, CAN_IT_FMP0,ENABLE);
#endif

}

void CAN1_TX_IRQHandler(void)
{
	//GPIOD->BSRRL = GPIO_Pin_13;
}


