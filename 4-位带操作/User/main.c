#include "stm32f10x.h"
#include "led.h"
#include "anjian.h"

#define GPIOA_ODR_Addr         (GPIOA_BASE+0X0C)
#define PAout(n)               *(unsigned int*)((GPIOA_ODR_Addr & 0xF0000000)+0x02000000+((GPIOA_ODR_Addr &0x00FFFFFF)<<5)+(n<<2))
#define GPIOE_IDR_Addr         (GPIOE_BASE+0X08)
#define PEin(n)                *(unsigned int*)((GPIOE_IDR_Addr & 0xF0000000)+0x02000000+((GPIOE_IDR_Addr &0x00FFFFFF)<<5)+(n<<2))

void delay(void)
{
	int i;
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	for(i=0;i<5000;i++);
	
}

int main (void)
{
	led();
	anjian();

#if 0	
	while(1)
	{
		//GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
		PAout(12) = 1;
		delay();
		//GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
		PAout(12) = 0;
		delay();
	}
#else
	
	while(1)
	{
		if( PEin(3) == ON )
			{
				while( PEin(3) == ON );
				LED;
			}
	}
#endif
}

