#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"

//  Òý½Å¶¨Òå
#define    KEY1_GPIO_CLK       RCC_APB2Periph_GPIOE
#define    KEY1_GPIO_PORT      GPIOE			   
#define    KEY1_GPIO_PIN	   GPIO_Pin_3


void Key_GPIO_Config(void);
int scan (GPIO_TypeDef *GPIOx,int GPIO_Pin);

#endif /* __KEY_H */

