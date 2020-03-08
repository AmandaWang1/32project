#ifndef _LED_H
#define _LED_H          //防止重复编译

#include "stm32f10x.h"

//与硬件相关的定义成宏

#define LED1_GPIO_PIN                  GPIO_Pin_1
#define LED1_GPIO_PORT                 GPIOA
#define LED1_GPIO_CLK                  RCC_APB2Periph_GPIOA

#define LED2_GPIO_PIN                  GPIO_Pin_2
#define LED2_GPIO_PORT                 GPIOA
#define LED2_GPIO_CLK                  RCC_APB2Periph_GPIOA

#define LED3_GPIO_PIN                  GPIO_Pin_3
#define LED3_GPIO_PORT                 GPIOA
#define LED3_GPIO_CLK                  RCC_APB2Periph_GPIOA

#define LED4_GPIO_PIN                  GPIO_Pin_4
#define LED4_GPIO_PORT                 GPIOA
#define LED4_GPIO_CLK                  RCC_APB2Periph_GPIOA

#define LED5_GPIO_PIN                  GPIO_Pin_5
#define LED5_GPIO_PORT                 GPIOA
#define LED5_GPIO_CLK                  RCC_APB2Periph_GPIOA

#define LED6_GPIO_PIN                  GPIO_Pin_6
#define LED6_GPIO_PORT                 GPIOA
#define LED6_GPIO_CLK                  RCC_APB2Periph_GPIOA

#define LED7_GPIO_PIN                  GPIO_Pin_7
#define LED7_GPIO_PORT                 GPIOA
#define LED7_GPIO_CLK                  RCC_APB2Periph_GPIOA

#define LED8_GPIO_PIN                  GPIO_Pin_8
#define LED8_GPIO_PORT                 GPIOA
#define LED8_GPIO_CLK                  RCC_APB2Periph_GPIOA



//#define    ON      1
//#define    OFF     0

//#define   LED(a)  if(a) GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN); else 	GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);

void LED_GPIO_Config (void);

#endif /*_LED_H*/

