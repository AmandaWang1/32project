#include "stm32f10x.h"
#include "bsp_led.h"
#include "exti.h"


int main (void)
{
	led ();
	
	EXTI_Key();
	
	while(1)
	{
		
	}

}

