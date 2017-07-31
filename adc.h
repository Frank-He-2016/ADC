#include "stm32f10x.h"
#include "stm32f10x_stdafx.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#ifndef _ADC_H_
#define _ADC_H_
#endif
void adc_init(void);
float adc_rec(void);
