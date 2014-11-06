
#ifndef USART_H
#define USART_H
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"

//一文字送信
void transmit_uart1_c(char c);

//文字列送信
void transmit_uart1_s(char *s);

//一文字送信
void transmit_uart2_c(char c);

//文字列送信
void transmit_uart2_s(char *s);

//一文字送信
void transmit_uart3_c(char c);

//文字列送信
void transmit_uart3_s(char *s);

//USART1送受信割り込みハンドラ
void USART1_IRQHandler(void);

//USART2送受信割り込みハンドラ
void USART2_IRQHandler(void);

//USART3送受信割り込みハンドラ
void USART3_IRQHandler(void);

//USART1初期化関数
void USART1_Configuration(void);

//USART2初期化関数
void USART2_Configuration(void);

//USART3初期化関数
void USART3_Configuration(void);

#endif
