#include "stm32f10x.h"
#include "bsp_led.h"
#include "base.h"

uint16_t time = 0;


int main (void)
{
	led ();
	
	BASIC_TIM_Init();
	
	while(1)
	{
		if( time == 500 )
		{
			time = 0;
			GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		}
		else
		{
			GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		}
	}
}

