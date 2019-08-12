#ifndef _LED_H
#define _LED_H    

//µÆ´ú±íSTP


#include "stm32f10x.h"


#define LED_GPIO_PIN                  GPIO_Pin_1
#define LED_GPIO_PORT                 GPIOA
#define LED_GPIO_CLK                  RCC_APB2Periph_GPIOA


#define     LED_G        {LED_GPIO_PORT->ODR ^= GPIO_Pin_1;}


void led (void);

#endif /*_LED_H*/

