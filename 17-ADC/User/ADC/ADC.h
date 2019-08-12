#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/*ADC1����ͨ�������ţ�����*/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC3

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA
#define    ADC_PORT                      GPIOA


// ת��ͨ������
#define    NOFCHANEL										 2

#define    ADC_PIN1                      GPIO_Pin_1
#define    ADC_CHANNEL1                  ADC_Channel_1


#define    ADC_PIN3                      GPIO_Pin_3
#define    ADC_CHANNEL3                  ADC_Channel_3



// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define    ADC_x                         ADC3
#define    ADC_DMA_CHANNEL               DMA2_Channel5
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA2

void ADCx_Init(void);


#endif /*ADC_H*/


