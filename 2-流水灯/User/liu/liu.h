#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#define LED_GPIO_PIN1         GPIO_Pin_5
#define LED_GPIO_PIN2         GPIO_Pin_1
#define LED_GPIO_PORT1        GPIOB 
#define LED_GPIO_CLK1         RCC_APB2Periph_GPIOB


void led(void);

#endif /*_LED_H*/


