#ifndef _CLOCK_H
#define _CLOCK_H

#include "stm32f10x.h"

void HSE_SetSysClk(int RCC_PLLMul_x);
void HSI_SetSysClk( uint32_t RCC_PLLMul_x);

#endif /*_CLOCK_H*/


