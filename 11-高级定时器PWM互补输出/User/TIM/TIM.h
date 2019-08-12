#ifndef _TIM_H
#define _TIM_H

#include "stm32f10x.h"

#define          ADVANCE_TIM                      TIM1
#define          ADVANCE_TIM_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define          ADVANCE_TIM_CLK                  RCC_APB2Periph_TIM1


// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = (ARR+1) * (1/CLK_cnt) = (ARR+1)*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)


//PWM信号的频率 F = TIM_CLK/{(ARR+1)*(PSC+1)}
//实际时自动重装载寄存器ARR的值
#define          ADVANCE_TIM_PERIOD               (50-1)      //周期 
// 预分频器的值，可实现1至65536分频，设定PSC寄存器的值
#define          ADVANCE_TIM_PSC            			(7200-1)      //决定了计数器计一次的时间
//比较输出脉冲宽度，实际比较CCR的值
#define          ADVANCE_TIM_PULSE          			6        //更改此项可更改占空比


#define          ADVANCE_TIM_IRQ        					TIM1_UP_IRQn
#define          ADVANCE_TIM_IRQHandler    				TIM1_UP_IRQHandler

//TIM1 输出比较通道
#define      		 ADVANCE_TIM_CH1_GPIO_CLK          RCC_APB2Periph_GPIOA
#define          ADVANCE_TIM_CH1_PORT        			 GPIOA
#define        	 ADVANCE_TIM_CH1_PIN       				 GPIO_Pin_8

//TIM1 输出比较通道的互补通道CLK     		 
#define          ADVANCE_TIM_CH1N_GPIO_CLK         RCC_APB2Periph_GPIOB
#define					 ADVANCE_TIM_CH1N_PORT        		 GPIOB
#define      		 ADVANCE_TIM_CH1N_PIN      				 GPIO_Pin_13

//TIM1 输出比较通道的刹车通道
#define          ADVANCE_TIM_BKIN_GPIO_CLK         RCC_APB2Periph_GPIOB
#define			     ADVANCE_TIM_BKIN_PORT     				 GPIOB
#define          ADVANCE_TIM_BKIN_PIN      				 GPIO_Pin_12

void TIM_Init(void);

#endif /*_TIM_H*/


