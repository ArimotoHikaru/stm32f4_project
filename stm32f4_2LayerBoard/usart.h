
#ifndef USART_H
#define USART_H
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"

//�ꕶ�����M
void transmit_uart1_c(char c);

//�����񑗐M
void transmit_uart1_s(char *s);

//�ꕶ�����M
void transmit_uart2_c(char c);

//�����񑗐M
void transmit_uart2_s(char *s);

//�ꕶ�����M
void transmit_uart3_c(char c);

//�����񑗐M
void transmit_uart3_s(char *s);

//USART1����M���荞�݃n���h��
void USART1_IRQHandler(void);

//USART2����M���荞�݃n���h��
void USART2_IRQHandler(void);

//USART3����M���荞�݃n���h��
void USART3_IRQHandler(void);

//USART1�������֐�
void USART1_Configuration(void);

//USART2�������֐�
void USART2_Configuration(void);

//USART3�������֐�
void USART3_Configuration(void);

#endif
