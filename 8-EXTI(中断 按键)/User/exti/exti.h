#ifndef _EXTI_H
#define _EXTI_H

#include "stm32f10x.h"

#define KEY_GPIO_PIN                  GPIO_Pin_3
#define KEY_GPIO_PORT                 GPIOA
#define KEY_GPIO_CLK                  RCC_APB2Periph_GPIOA


void EXTI_Key(void);

#endif /*_EXTI_H*/

