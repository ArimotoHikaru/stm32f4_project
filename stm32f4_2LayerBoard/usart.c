#include "usart.h"

#define USART1_BAUDRATE 115200
#define USART2_BAUDRATE 115200
#define USART3_BAUDRATE 115200

#define USART1_TxBufferSize  200//リングバッファの要素数
#define USART1_RxBufferSize  200//リングバッファの要素数
#define USART2_TxBufferSize  200//リングバッファの要素数
#define USART2_RxBufferSize  200//リングバッファの要素数
#define USART3_TxBufferSize  200//リングバッファの要素数
#define USART3_RxBufferSize  200//リングバッファの要素数

char USART1_TxBuffer[USART1_TxBufferSize];
char USART1_RxBuffer[USART1_RxBufferSize];
int  USART1_TxPtrNow=0,
     USART1_TxPtrEnd=1;
int  USART1_RxPtrNow=0,
     USART1_RxPtrEnd=1;

char USART2_TxBuffer[USART2_TxBufferSize];
char USART2_RxBuffer[USART2_RxBufferSize];
int  USART2_TxPtrNow=0,
     USART2_TxPtrEnd=1;
int  USART2_RxPtrNow=0,
     USART2_RxPtrEnd=1;

char USART3_TxBuffer[USART3_TxBufferSize];
char USART3_RxBuffer[USART3_RxBufferSize];
int  USART3_TxPtrNow=0,
     USART3_TxPtrEnd=1;
int  USART3_RxPtrNow=0,
     USART3_RxPtrEnd=1;

void USART1_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	/* Define InitTypeDef ---------------------------------------------------*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	/* initialize InitTypeDef -----------------------------------------------*/

	/* Supply clock source --------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin  	= GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART1);//USART1 TX/PA9
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_USART1);//USART1 RX/PA10

	/* Set up USART1_function --------------------------------------------------*/
	USART_InitStructure.USART_BaudRate 				= USART1_BAUDRATE;
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;
	USART_InitStructure.USART_Parity 				= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 					= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel 						= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);


}

void USART2_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	/* Define InitTypeDef ---------------------------------------------------*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	/* initialize InitTypeDef -----------------------------------------------*/

	/* Supply clock source --------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_AHB1Periph_GPIOD, ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin  	= GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);//USART2 TX/PD5
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);//USART2 RX/PD6

	/* Set up USART2_function --------------------------------------------------*/
	USART_InitStructure.USART_BaudRate 				= USART2_BAUDRATE;
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;
	USART_InitStructure.USART_Parity 				= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 					= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel 						= USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);


}

void USART3_Configuration(void)
{
	/* Define variable ------------------------------------------------------*/
	/* Define InitTypeDef ---------------------------------------------------*/
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;
	/* initialize InitTypeDef -----------------------------------------------*/

	/* Supply clock source --------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_AHB1Periph_GPIOD, ENABLE);

	/* Define gpio_config ---------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin  	= GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART3);//USART3 TX/PD5
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART3);//USART3 RX/PD6

	/* Set up USART3_function --------------------------------------------------*/
	USART_InitStructure.USART_BaudRate 				= USART3_BAUDRATE;
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;
	USART_InitStructure.USART_Parity 				= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 					= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel 						= USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);


}

//一文字送信
void transmit_uart1_c(char c)
{

  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);  //送信し終わった割り込みを一時的に禁止
  USART1_TxBuffer[USART1_TxPtrEnd] = c;    //リングバッファに１文字追加
  USART1_TxPtrEnd++;    //書き込みポインタを＋１

  if(USART1_TxPtrEnd > (USART1_TxBufferSize-1)) USART1_TxPtrNow=0; USART1_TxPtrEnd = 1;    //書き込みポインタがオーバーフローしたら０に戻す

  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  // 送信し終わった割り込みを許可

}
//文字列送信
void transmit_uart1_s(char *s)
{

  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);

  while(*s!=0) // until end of string   文字列の末尾までループ
  {
    USART1_TxBuffer[USART1_TxPtrEnd] = *(s++);
    USART1_TxPtrEnd++; //  ポインタ＋１

    if(USART1_TxPtrEnd > (USART1_TxBufferSize-1)) USART1_TxPtrEnd = 0;
  }

  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);   //送信し終わった割り込みを許可
}

//一文字送信
void transmit_uart2_c(char c)
{

  USART_ITConfig(USART2, USART_IT_TXE, DISABLE);  //送信し終わった割り込みを一時的に禁止
  USART2_TxBuffer[USART2_TxPtrEnd] = c;    //リングバッファに１文字追加
  USART2_TxPtrEnd++;    //書き込みポインタを＋１

  if(USART2_TxPtrEnd > (USART2_TxBufferSize-1)) USART2_TxPtrNow=0; USART2_TxPtrEnd = 1;    //書き込みポインタがオーバーフローしたら０に戻す

  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);  // 送信し終わった割り込みを許可

}
//文字列送信
void transmit_uart2_s(char *s)
{

  USART_ITConfig(USART2, USART_IT_TXE, DISABLE); 

  while(*s!=0) // until end of string   文字列の末尾までループ
  {
    USART2_TxBuffer[USART2_TxPtrEnd] = *(s++);
    USART2_TxPtrEnd++; //  ポインタ＋１

    if(USART2_TxPtrEnd > (USART2_TxBufferSize-1)) USART2_TxPtrEnd = 0;
  }

  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);   //送信し終わった割り込みを許可
}

//一文字送信
void transmit_uart3_c(char c)
{

  USART_ITConfig(USART3, USART_IT_TXE, DISABLE);  //送信し終わった割り込みを一時的に禁止
  USART3_TxBuffer[USART3_TxPtrEnd] = c;    //リングバッファに１文字追加
  USART3_TxPtrEnd++;    //書き込みポインタを＋１

  if(USART3_TxPtrEnd > (USART3_TxBufferSize-1)) USART3_TxPtrNow=0; USART3_TxPtrEnd = 1;    //書き込みポインタがオーバーフローしたら０に戻す

  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);  // 送信し終わった割り込みを許可

}
//文字列送信
void transmit_uart3_s(char *s)
{

  USART_ITConfig(USART3, USART_IT_TXE, DISABLE); 

  while(*s!=0) // until end of string   文字列の末尾までループ
  {
    USART3_TxBuffer[USART3_TxPtrEnd] = *(s++);
    USART3_TxPtrEnd++; //  ポインタ＋１

    if(USART3_TxPtrEnd > (USART3_TxBufferSize-1)) USART3_TxPtrEnd = 0;
  }

  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);   //送信し終わった割り込みを許可
}

void USART1_IRQHandler(void)
{

	char c;

	//受信割り込み
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
		c = (char)USART_ReceiveData(USART1);
		transmit_uart1_c(c);
	}

	//送信割り込み
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET){  // UART送信フラグチェック
		USART_SendData(USART1, USART1_TxBuffer[USART1_TxPtrNow++]); // １文字送信

		if(USART1_TxPtrNow > (USART1_TxBufferSize-1)) USART1_TxPtrNow=0;;//   ポインタオーバーフローならゼロに戻す

		if(USART1_TxPtrNow == USART1_TxPtrEnd){     //リングバッファが空か？
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE); //送信割り込みをオフ
		}
	}
}

void USART2_IRQHandler(void)
{
  
	char c;
  
	//受信割り込み
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
		c = (char)USART_ReceiveData(USART2);
		transmit_uart2_c(c);
	}
  
	//送信割り込み
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET){  // UART送信フラグチェック
		USART_SendData(USART2, USART2_TxBuffer[USART2_TxPtrNow++]); // １文字送信

		if(USART2_TxPtrNow > (USART2_TxBufferSize-1)) USART2_TxPtrNow=0;;//   ポインタオーバーフローならゼロに戻す

		if(USART2_TxPtrNow == USART2_TxPtrEnd){     //リングバッファが空か？
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE); //送信割り込みをオフ
		}
	}
}

void USART3_IRQHandler(void)
{
	char c;

	//受信割り込み
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
		c = (char)USART_ReceiveData(USART3);
		transmit_uart3_c(c);
	}

	//送信割り込み
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET){  // UART送信フラグチェック
		USART_SendData(USART3, USART3_TxBuffer[USART3_TxPtrNow++]); // １文字送信

		if(USART3_TxPtrNow > (USART3_TxBufferSize-1)) USART3_TxPtrNow = 0;;//   ポインタオーバーフローならゼロに戻す

		if(USART3_TxPtrNow == USART3_TxPtrEnd){     //リングバッファが空か？
			USART_ITConfig(USART3, USART_IT_TXE, DISABLE); //送信割り込みをオフ
		}
	}
}
