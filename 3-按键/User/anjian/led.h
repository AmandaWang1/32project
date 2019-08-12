#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#define LED_G_GPIO_PIN         GPIO_Pin_12
#define LED_G_GPIO_PORT        GPIOA
#define LED_G_GPIO_CLK         RCC_APB2Periph_GPIOA

#define LED                  {LED_G_GPIO_PORT->ODR^=LED_G_GPIO_PIN;}

void led (void);

#endif /*_LED_H*/


