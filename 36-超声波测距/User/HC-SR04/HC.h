#ifndef _HC_H
#define _HC_H

#include "stm32f10x.h"

#define ON     1
#define OFF    0

#define HC_TRIG_PIN                  GPIO_Pin_5
#define HC_TRIG_PORT                 GPIOB
#define HC_TRIG_CLK                  RCC_APB2Periph_GPIOB

#define HC_ECHO_PIN                  GPIO_Pin_6
#define HC_ECHO_PORT                 GPIOB
#define HC_ECHO_CLK                  RCC_APB2Periph_GPIOB

void HC_Init (void);
void BASIC_TIM_IRQHandler(void);
uint32_t GetEchoTimer(void);
float Hcsr04GetLength(void);


#endif /*_HC_H*/



