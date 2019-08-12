#include "stm32f10x.h"
#include "led.h"
#include "anjian.h"

int main (void)
{
	led();
	anjian();
	
	while(1)
	{
		if(scan (ANJIAN_GPIO_PORT,ANJIAN_GPIO_PIN) == ON)
			LED;
	}
}

