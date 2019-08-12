#ifndef _ANJIAN_H
#define _ANJIAN_H

#include "stm32f10x.h"

#define ON     0
#define OFF    1

#define ANJIAN_GPIO_PIN          GPIO_Pin_3
#define ANJIAN_GPIO_PORT         GPIOE
#define ANJIAN_GPIO_CLK          RCC_APB2Periph_GPIOE

void anjian (void);
int scan (GPIO_TypeDef *GPIOx,int GPIO_Pin); 

#endif /*_ANJIAN_H*/

