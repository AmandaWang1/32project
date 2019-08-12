#include "stm32f10x.h"
#include "bsp_led.h"
#include "TIM.h"
#include "usart.h"


int main (void)
{
	USART_Config();
	TIM_Init();
	while(1)
	{
	}

}

