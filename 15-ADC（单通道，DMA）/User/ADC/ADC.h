#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

// ADC 编号选择
// 可以是 ADC1/2，如果使用ADC3，中断相关的要改成ADC3的
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_x                         ADC1
#define    ADC_CLK                       RCC_APB2Periph_ADC1


// ADC GPIO宏定义
// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC
#define    ADC_PIN                       GPIO_Pin_1

// ADC 通道宏定义
#define    ADC_CHANNEL                   ADC_Channel_11

#define    ADC_DMA_CLK           				 RCC_AHBPeriph_DMA1//换成ADC3时这个要改成DMA2
#define    ADC_DMA_CHANNEL               DMA1_Channel1//这里也改，而且Channel改成5

void ADCx_Init(void);


#endif /*ADC_H*/


