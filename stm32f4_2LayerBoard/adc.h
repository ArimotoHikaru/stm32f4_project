
#ifndef ADC_H
#define ADC_H
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_rcc.h"

//ADC‰Šú‰»ŠÖ”
void ADC_Configuration(void);
//’læ“¾ŠÖ”
uint16_t GetAdc1Value_xch(uint8_t ch);

#endif
