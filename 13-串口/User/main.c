#include "stm32f10x.h"
#include "bsp_led.h"
#include "usart.h"


int main (void)
{
	//uint8_t a[10]={1,2,3,4,5,6,7,8,9,0};
	uint8_t ch;
	USART_Config();
	
	//Usart_SendByte(DEBUG_USARTx,'A');
	//Usart_send(DEBUG_USARTx,0xff56)	;
	//Usart_send8(DEBUG_USARTx,a,10);
	Usart_sendstr(DEBUG_USARTx,"你是个傻子\n");	
	//printf("你确实是个傻子\n");
	
	
	while(1)
	{
		led ();
		ch = getchar();
		printf("ch=%c\n",ch);
		
		switch(ch)
		{
			case 'A' :GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
				break;
			case 'B' :GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
				break;
		}
	}
}

