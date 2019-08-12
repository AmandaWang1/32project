#include "stm32f10x.h"
#include "bsp_led.h"
#include "systick.h"

int main (void)
{
	led ();
	
	while(1)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay_ms(500);
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay_ms(500);
	}
}

